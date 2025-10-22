#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

struct DataPoint {
    std::string date;
    double value;
};

// 解析日期字符串为tm结构
std::tm parseDateTime(const std::string& dateStr) {
    std::tm tm = {};
    std::istringstream ss(dateStr);
    char slash1, slash2, colon, space;
    int year, month, day, hour, minute;
    
    ss >> year >> slash1 >> month >> slash2 >> day >> space >> hour >> colon >> minute;
    tm.tm_year = year + 100;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    tm.tm_sec = 0;
    
    return tm;
}

// 将tm结构格式化为日期字符串
std::string formatDateTime(const std::tm& tm) {
    std::ostringstream ss;
    ss << std::setfill('0') << std::setw(2) << (tm.tm_year - 100) << "/"
       << std::setfill('0') << std::setw(2) << (tm.tm_mon + 1) << "/"
       << std::setfill('0') << std::setw(2) << tm.tm_mday << " "
       << std::setfill('0') << std::setw(2) << tm.tm_hour << ":"
       << std::setfill('0') << std::setw(2) << tm.tm_min;
    return ss.str();
}

// 计算两个时间点之间的时间差（分钟）
double calculateTimeDifference(const std::tm& tm1, const std::tm& tm2) {
    std::time_t time1 = std::mktime(const_cast<std::tm*>(&tm1));
    std::time_t time2 = std::mktime(const_cast<std::tm*>(&tm2));
    return std::difftime(time2, time1) / 60.0;
}

// 在时间点上添加分钟数
std::tm addMinutes(const std::tm& tm, double minutes) {
    std::time_t time = std::mktime(const_cast<std::tm*>(&tm));
    time += static_cast<std::time_t>(minutes * 60);
    return *std::localtime(&time);
}

// 读取CSV文件
std::vector<DataPoint> readCSV(const std::string& filename) {
    std::vector<DataPoint> data;
    std::ifstream file(filename);
    std::string line;
    
    while (std::getline(file, line)) {
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos) {
            DataPoint point;
            point.date = line.substr(0, commaPos);
            point.value = std::stod(line.substr(commaPos + 1));
            data.push_back(point);
        }
    }
    
    file.close();
    return data;
}

// 写入CSV文件
void writeCSV(const std::string& filename, const std::vector<DataPoint>& data) {
    std::ofstream file(filename);
    for (const auto& point : data) {
        file << point.date << "," << point.value << std::endl;
    }
    file.close();
}

int main() {
    // 读取数据
    std::vector<DataPoint> data = readCSV("data.csv");
    
    // 解析日期时间
    std::vector<std::tm> dateTimes;
    for (const auto& point : data) {
        dateTimes.push_back(parseDateTime(point.date));
    }
    
    // 计算时间间隔（使用第一个间隔）
    double timeInterval = calculateTimeDifference(dateTimes[0], dateTimes[1]);
    
    // 获取预测数量
    int predictCount;
    std::cout << "请输入要预测的单位时间数量: ";
    std::cin >> predictCount;
    
    // 计算趋势（使用线性回归）
    double sumX = 0.0, sumY = 0.0, sumXY = 0.0, sumX2 = 0.0;
    int n = data.size();
    
    for (int i = 0; i < n; ++i) {
        double x = static_cast<double>(i);
        double y = data[i].value;
        sumX += x;
        sumY += y;
        sumXY += x * y;
        sumX2 += x * x;
    }
    
    double slope = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    double intercept = (sumY - slope * sumX) / n;
    
    // 生成预测数据
    std::vector<DataPoint> predictions;
    std::tm lastTime = dateTimes.back();
    
    for (int i = 1; i <= predictCount; ++i) {
        DataPoint prediction;
        
        // 计算预测时间
        std::tm predTime = addMinutes(lastTime, timeInterval * i);
        prediction.date = formatDateTime(predTime);
        
        // 计算预测值
        double x = n + i - 1;
        prediction.value = slope * x + intercept;
        
        predictions.push_back(prediction);
    }
    
    // 写入结果
    writeCSV("out.csv", predictions);
    std::cout << "预测结果已写入 out.csv" << std::endl;
    
    return 0;
}