from cyaron import *
for i in range(1,15):
	io = IO(file_prefix="D:/Documents/Program-files/CYaRon/tetris",data_id=i)
	n = randint(1,100)
	m = randint(1,7)
	lst = [0] * n
	lst[0] = randint(0,100)
	for j in range(1,n):
		ch = randint(1,7)
		ch2 = randint(0,1)
		if ch == 1 and j < n - 2:
			lst[j + 2] = lst[j + 1] = lst[j] = lst[j - 1]
			j += 2
		elif ch == 2 and j < n - 1 and 0 < lst[j - 1] < 100:
			if ch2:
				lst[j] = lst[j - 1] + 1
			else:
				lst[j + 1] = lst[j] = lst[j - 1] - 1
				j += 1
		elif ch == 3 and j < n - 1 and 0 < lst[j - 1] < 100:
			if ch2:
				lst[j] = lst[j - 1] - 1
			else:
				lst[j] = lst[j - 1]
				lst[j + 1] = lst[j] + 1
				j += 1
		elif ch == 4 and j < n - 1 and 0 < lst[j - 1]:
			if ch2:
				lst[j + 1] = lst[j] = lst[j - 1]
				j += 1
			else:
				lst[j + 1] = lst[j - 1]
				lst[j] = lst[j - 1] - 1
				j += 1
		elif ch == 5 and 1 < lst[j - 1]:
			lst[j] = lst[j - 1] - 2
		elif ch == 6 and lst[j - 1] < 99:
			lst[j] = lst[j - 1] + 2
		else:
			lst[j] = randint(0,100)
	io.input_writeln(n,m)
	io.input_writeln(lst)
	io.output_gen("D:/Documents/Program-files/CYaRon/std.exe")