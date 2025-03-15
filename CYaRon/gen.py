from cyaron import *
from random import *
for i in range(1,11):
	io = IO(file_prefix="./CYaRon/matrix", data_id=i)
	n = randint(1,1000)
	m = randint(1,1000)
	io.input_writeln(n,m)
	for i in range(0,n):
		for j in range(0,m):
			op = randint(0,10)
			if (op == 0):
				io.input_write(1,separator='')
			else:
				io.input_write(0,separator='')
		io.input_writeln()
	io.output_gen("D:\\Users\\Administrator\\Documents\\Program-Files\\CYaRon\\std.exe")