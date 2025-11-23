import tkinter as tk
from tkinter import ttk
import psutil
import GPUtil
import threading
import time
import os
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
import matplotlib.animation as animation
from collections import deque
import matplotlib.font_manager as fm

class SystemMonitor:
    def __init__(self, root):
        self.root = root
        self.root.title("系统资源监控器")
        self.root.geometry("1000x700")
        self.root.resizable(True, True)
        
        # 设置中文字体
        self.set_chinese_font()
        
        # 设置主题样式
        self.style = ttk.Style()
        self.style.theme_use('clam')
        
        # 创建标签页
        self.notebook = ttk.Notebook(root)
        self.notebook.pack(fill='both', expand=True, padx=10, pady=10)
        
        # 数据存储（使用deque保持固定长度的历史数据）
        self.history_length = 60  # 保留最近60个数据点
        self.cpu_history = deque([0] * self.history_length, maxlen=self.history_length)
        self.memory_history = deque([0] * self.history_length, maxlen=self.history_length)
        self.gpu_history = deque([0] * self.history_length, maxlen=self.history_length)
        
        # 存储磁盘读写历史数据（按磁盘分开）
        self.disk_read_histories = {}
        self.disk_write_histories = {}
        
        # 存储网络历史数据（按接口分开）
        self.network_upload_histories = {}
        self.network_download_histories = {}
        
        # 初始化磁盘和网络统计
        self.old_disk_io = psutil.disk_io_counters(perdisk=True)
        self.old_network_stats = psutil.net_io_counters(pernic=True)
        
        # 初始化磁盘和网络历史数据
        self.init_disk_histories()
        self.init_network_histories()
        
        # 创建各个监控页面
        self.create_summary_tab()
        self.create_disk_tab()
        self.create_network_tab()
        
        # 启动监控线程
        self.monitoring = True
        self.monitor_thread = threading.Thread(target=self.update_monitor)
        self.monitor_thread.daemon = True
        self.monitor_thread.start()
        
        # 启动图表动画
        self.ani = animation.FuncAnimation(
            self.summary_fig, 
            self.update_summary_charts, 
            interval=1000,
            save_count=self.history_length,
            cache_frame_data=False
        )
        
    def init_disk_histories(self):
        """初始化磁盘历史数据"""
        disk_io = psutil.disk_io_counters(perdisk=True)
        for disk in disk_io.keys():
            self.disk_read_histories[disk] = deque([0] * self.history_length, maxlen=self.history_length)
            self.disk_write_histories[disk] = deque([0] * self.history_length, maxlen=self.history_length)
    
    def init_network_histories(self):
        """初始化网络历史数据"""
        network_io = psutil.net_io_counters(pernic=True)
        for interface in network_io.keys():
            self.network_upload_histories[interface] = deque([0] * self.history_length, maxlen=self.history_length)
            self.network_download_histories[interface] = deque([0] * self.history_length, maxlen=self.history_length)
        
    def set_chinese_font(self):
        """设置中文字体"""
        # 尝试使用系统中可用的中文字体
        chinese_fonts = ['Microsoft YaHei', 'SimHei', 'KaiTi', 'SimSun', 'Arial Unicode MS']
        
        # 检查系统中可用的中文字体
        available_fonts = []
        for font in chinese_fonts:
            try:
                # 尝试创建字体对象，如果成功则字体可用
                test_font = tk.font.Font(family=font, size=10)
                available_fonts.append(font)
            except:
                pass
        
        # 设置默认字体
        if available_fonts:
            default_font = available_fonts[0]
            self.default_font = (default_font, 10)
            # 设置Tkinter默认字体
            self.root.option_add("*Font", self.default_font)
            
            # 设置Matplotlib中文字体
            plt.rcParams['font.sans-serif'] = available_fonts + ['DejaVu Sans']
            plt.rcParams['axes.unicode_minus'] = False  # 解决负号显示问题
        else:
            # 如果没有找到中文字体，使用默认字体
            self.default_font = ('TkDefaultFont', 10)
            print("警告: 未找到中文字体，中文显示可能不正常")
        
    def create_summary_tab(self):
        self.summary_frame = ttk.Frame(self.notebook)
        self.notebook.add(self.summary_frame, text="概览")
        
        # 创建概览图表
        self.summary_fig = Figure(figsize=(10, 8), dpi=100)
        self.summary_canvas = FigureCanvasTkAgg(self.summary_fig, self.summary_frame)
        self.summary_canvas.get_tk_widget().pack(fill='both', expand=True, padx=10, pady=10)
        
        # 创建子图 - 只有CPU、内存和GPU
        self.cpu_ax = self.summary_fig.add_subplot(2, 2, 1)
        self.memory_ax = self.summary_fig.add_subplot(2, 2, 2)
        self.gpu_ax = self.summary_fig.add_subplot(2, 1, 2)  # GPU独占第二行
        
        # 初始化图表
        self.init_summary_charts()
        
    def init_summary_charts(self):
        # CPU图表
        self.cpu_ax.set_title('CPU使用率')
        self.cpu_ax.set_ylim(0, 100)
        self.cpu_ax.set_xlim(0, self.history_length)
        self.cpu_line, = self.cpu_ax.plot(range(self.history_length), self.cpu_history, 'r-')
        self.cpu_ax.grid(True, alpha=0.3)
        
        # 添加CPU使用率文本
        self.cpu_text = self.cpu_ax.text(0.02, 0.95, '', transform=self.cpu_ax.transAxes, fontsize=12, 
                                        bbox=dict(boxstyle="round,pad=0.3", facecolor="white", alpha=0.8))
        
        # 内存图表
        self.memory_ax.set_title('内存使用率')
        self.memory_ax.set_ylim(0, 100)
        self.memory_ax.set_xlim(0, self.history_length)
        self.memory_line, = self.memory_ax.plot(range(self.history_length), self.memory_history, 'b-')
        self.memory_ax.grid(True, alpha=0.3)
        
        # 添加内存使用率文本
        self.memory_text = self.memory_ax.text(0.02, 0.95, '', transform=self.memory_ax.transAxes, fontsize=12,
                                              bbox=dict(boxstyle="round,pad=0.3", facecolor="white", alpha=0.8))
        
        # GPU图表
        self.gpu_ax.set_title('GPU使用率')
        self.gpu_ax.set_ylim(0, 100)
        self.gpu_ax.set_xlim(0, self.history_length)
        self.gpu_line, = self.gpu_ax.plot(range(self.history_length), self.gpu_history, 'g-')
        self.gpu_ax.grid(True, alpha=0.3)
        
        # 添加GPU使用率文本
        self.gpu_text = self.gpu_ax.text(0.02, 0.95, '', transform=self.gpu_ax.transAxes, fontsize=12,
                                        bbox=dict(boxstyle="round,pad=0.3", facecolor="white", alpha=0.8))
        
        # 调整布局
        self.summary_fig.tight_layout()
        
    def update_summary_charts(self, frame=None):
        # 更新CPU图表
        self.cpu_line.set_ydata(self.cpu_history)
        self.cpu_text.set_text(f'当前: {self.cpu_history[-1]:.1f}%')
        
        # 更新内存图表
        self.memory_line.set_ydata(self.memory_history)
        self.memory_text.set_text(f'当前: {self.memory_history[-1]:.1f}%')
        
        # 更新GPU图表
        self.gpu_line.set_ydata(self.gpu_history)
        self.gpu_text.set_text(f'当前: {self.gpu_history[-1]:.1f}%')
        
        # 刷新画布
        self.summary_canvas.draw_idle()
        
        return []
        
    def create_disk_tab(self):
        self.disk_frame = ttk.Frame(self.notebook)
        self.notebook.add(self.disk_frame, text="磁盘")
        
        # 创建磁盘读写速度图表
        disk_chart_frame = ttk.Frame(self.disk_frame)
        disk_chart_frame.pack(fill='both', expand=True, padx=10, pady=10)
        
        # 创建磁盘读写速度图表
        self.disk_fig = Figure(figsize=(10, 8), dpi=100)
        self.disk_canvas = FigureCanvasTkAgg(self.disk_fig, disk_chart_frame)
        self.disk_canvas.get_tk_widget().pack(fill='both', expand=True)
        
        # 获取磁盘数量
        disk_io = psutil.disk_io_counters(perdisk=True)
        disk_count = len(disk_io)
        
        # 根据磁盘数量创建子图
        if disk_count <= 2:
            rows, cols = 2, 1
        elif disk_count <= 4:
            rows, cols = 2, 2
        else:
            rows, cols = (disk_count + 1) // 2, 2  # 确保有足够的子图位置
        
        self.disk_axes = {}
        self.disk_read_lines = {}
        self.disk_write_lines = {}
        self.disk_read_texts = {}
        self.disk_write_texts = {}
        
        # 确保有足够的子图位置
        if rows * cols < disk_count:
            rows += 1
        
        for i, disk in enumerate(disk_io.keys()):
            if i >= rows * cols:
                break  # 防止超出子图数量
                
            row = i // cols
            col = i % cols
            pos = row * cols + col + 1
            
            ax = self.disk_fig.add_subplot(rows, cols, pos)
            ax.set_title(f'{disk} 读写速度')
            ax.set_ylabel('速度 (MB/s)')
            ax.set_xlabel('时间 (秒)')
            ax.set_ylim(0, 100)  # 固定量程为0-100MB/s
            ax.set_xlim(0, self.history_length)
            
            read_line, = ax.plot(range(self.history_length), self.disk_read_histories[disk], 'r-', linewidth=1.5, label='读取')
            write_line, = ax.plot(range(self.history_length), self.disk_write_histories[disk], 'b-', linewidth=1.5, label='写入')
            ax.legend()
            ax.grid(True, alpha=0.3)
            
            # 添加磁盘读写速度文本
            read_text = ax.text(0.02, 0.95, '', transform=ax.transAxes, fontsize=10, color='red',
                               bbox=dict(boxstyle="round,pad=0.2", facecolor="white", alpha=0.8))
            write_text = ax.text(0.02, 0.85, '', transform=ax.transAxes, fontsize=10, color='blue',
                                bbox=dict(boxstyle="round,pad=0.2", facecolor="white", alpha=0.8))
            
            self.disk_axes[disk] = ax
            self.disk_read_lines[disk] = read_line
            self.disk_write_lines[disk] = write_line
            self.disk_read_texts[disk] = read_text
            self.disk_write_texts[disk] = write_text
        
        # 调整布局
        self.disk_fig.tight_layout()
        
        # 启动磁盘图表动画
        self.disk_ani = animation.FuncAnimation(
            self.disk_fig, 
            self.update_disk_chart, 
            interval=1000,
            save_count=self.history_length,
            cache_frame_data=False
        )
        
    def update_disk_chart(self, frame=None):
        # 获取当前磁盘IO统计
        new_disk_io = psutil.disk_io_counters(perdisk=True)
        
        for disk in new_disk_io.keys():
            if disk not in self.old_disk_io:
                continue
                
            # 计算磁盘读写速度
            time_diff = 1  # 1秒间隔
            disk_read_speed = (new_disk_io[disk].read_bytes - self.old_disk_io[disk].read_bytes) / time_diff / 1024 / 1024  # 转换为MB/s
            disk_write_speed = (new_disk_io[disk].write_bytes - self.old_disk_io[disk].write_bytes) / time_diff / 1024 / 1024  # 转换为MB/s
            
            # 更新历史数据
            self.disk_read_histories[disk].append(disk_read_speed)
            self.disk_write_histories[disk].append(disk_write_speed)
            
            # 更新图表
            if disk in self.disk_read_lines:
                self.disk_read_lines[disk].set_ydata(self.disk_read_histories[disk])
                self.disk_write_lines[disk].set_ydata(self.disk_write_histories[disk])
                
                # 更新文本
                self.disk_read_texts[disk].set_text(f'读取: {disk_read_speed:.2f} MB/s')
                self.disk_write_texts[disk].set_text(f'写入: {disk_write_speed:.2f} MB/s')
                
                # 不再动态调整Y轴范围，保持固定0-100MB/s
        
        # 更新磁盘统计
        self.old_disk_io = new_disk_io
        
        self.disk_canvas.draw_idle()
        return []
        
    def create_network_tab(self):
        self.network_frame = ttk.Frame(self.notebook)
        self.notebook.add(self.network_frame, text="网络")
        
        # 创建网络速度图表
        network_chart_frame = ttk.Frame(self.network_frame)
        network_chart_frame.pack(fill='both', expand=True, padx=10, pady=10)
        
        # 创建网络速度图表
        self.network_fig = Figure(figsize=(10, 8), dpi=100)
        self.network_canvas = FigureCanvasTkAgg(self.network_fig, network_chart_frame)
        self.network_canvas.get_tk_widget().pack(fill='both', expand=True)
        
        # 获取网络接口数量
        network_io = psutil.net_io_counters(pernic=True)
        interface_count = len(network_io)
        
        # 根据接口数量创建子图
        if interface_count <= 2:
            rows, cols = 2, 1
        elif interface_count <= 4:
            rows, cols = 2, 2
        else:
            rows, cols = (interface_count + 1) // 2, 2  # 确保有足够的子图位置
        
        self.network_axes = {}
        self.network_upload_lines = {}
        self.network_download_lines = {}
        self.network_upload_texts = {}
        self.network_download_texts = {}
        
        # 确保有足够的子图位置
        if rows * cols < interface_count:
            rows += 1
        
        for i, interface in enumerate(network_io.keys()):
            if i >= rows * cols:
                break  # 防止超出子图数量
                
            row = i // cols
            col = i % cols
            pos = row * cols + col + 1
            
            ax = self.network_fig.add_subplot(rows, cols, pos)
            ax.set_title(f'{interface} 网络速度')
            ax.set_ylabel('速度 (MB/s)')
            ax.set_xlabel('时间 (秒)')
            ax.set_ylim(0, 100)  # 固定量程为0-100MB/s
            ax.set_xlim(0, self.history_length)
            
            upload_line, = ax.plot(range(self.history_length), self.network_upload_histories[interface], 'r-', linewidth=1.5, label='上传')
            download_line, = ax.plot(range(self.history_length), self.network_download_histories[interface], 'b-', linewidth=1.5, label='下载')
            ax.legend()
            ax.grid(True, alpha=0.3)
            
            # 添加网络速度文本
            upload_text = ax.text(0.02, 0.95, '', transform=ax.transAxes, fontsize=10, color='red',
                                 bbox=dict(boxstyle="round,pad=0.2", facecolor="white", alpha=0.8))
            download_text = ax.text(0.02, 0.85, '', transform=ax.transAxes, fontsize=10, color='blue',
                                   bbox=dict(boxstyle="round,pad=0.2", facecolor="white", alpha=0.8))
            
            self.network_axes[interface] = ax
            self.network_upload_lines[interface] = upload_line
            self.network_download_lines[interface] = download_line
            self.network_upload_texts[interface] = upload_text
            self.network_download_texts[interface] = download_text
        
        # 调整布局
        self.network_fig.tight_layout()
        
        # 启动网络图表动画
        self.network_ani = animation.FuncAnimation(
            self.network_fig, 
            self.update_network_chart, 
            interval=1000,
            save_count=self.history_length,
            cache_frame_data=False
        )
        
    def update_network_chart(self, frame=None):
        # 获取当前网络统计
        new_network_stats = psutil.net_io_counters(pernic=True)
        
        for interface in new_network_stats.keys():
            if interface not in self.old_network_stats:
                continue
                
            # 计算网络速度
            time_diff = 1  # 1秒间隔
            upload_speed = (new_network_stats[interface].bytes_sent - self.old_network_stats[interface].bytes_sent) / time_diff / 1024 / 1024  # 转换为MB/s
            download_speed = (new_network_stats[interface].bytes_recv - self.old_network_stats[interface].bytes_recv) / time_diff / 1024 / 1024  # 转换为MB/s
            
            # 更新历史数据
            self.network_upload_histories[interface].append(upload_speed)
            self.network_download_histories[interface].append(download_speed)
            
            # 更新图表
            if interface in self.network_upload_lines:
                self.network_upload_lines[interface].set_ydata(self.network_upload_histories[interface])
                self.network_download_lines[interface].set_ydata(self.network_download_histories[interface])
                
                # 更新文本
                self.network_upload_texts[interface].set_text(f'上传: {upload_speed:.2f} MB/s')
                self.network_download_texts[interface].set_text(f'下载: {download_speed:.2f} MB/s')
                
                # 不再动态调整Y轴范围，保持固定0-100MB/s
        
        # 更新网络统计
        self.old_network_stats = new_network_stats
        
        self.network_canvas.draw_idle()
        return []
        
    def update_monitor(self):
        # 初始化磁盘和网络统计
        self.old_disk_io = psutil.disk_io_counters(perdisk=True)
        self.old_network_stats = psutil.net_io_counters(pernic=True)
        time.sleep(1)  # 等待1秒获取初始数据
        
        while self.monitoring:
            try:
                # 更新CPU信息
                cpu_percent = psutil.cpu_percent(interval=0.5)
                self.cpu_history.append(cpu_percent)
                
                # 更新内存信息
                memory = psutil.virtual_memory()
                memory_percent = memory.percent
                self.memory_history.append(memory_percent)
                
                # 更新GPU信息
                try:
                    gpus = GPUtil.getGPUs()
                    if gpus:
                        gpu = gpus[0]  # 获取第一个GPU
                        gpu_percent = gpu.load * 100
                        self.gpu_history.append(gpu_percent)
                    else:
                        self.gpu_history.append(0)
                except Exception as e:
                    self.gpu_history.append(0)
                
            except Exception as e:
                print(f"监控更新错误: {e}")
                
            time.sleep(1)  # 每1秒更新一次

def main():
    root = tk.Tk()
    app = SystemMonitor(root)
    root.mainloop()

if __name__ == "__main__":
    main()