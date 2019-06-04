import sys
import os
import random

runmax = 0

def print_usage():
	print ("Invalid Command Line Options")
	print ("Usage : DummyCmdAdder.py $filename.s")
	exit(-1)

def update_runmax(str_a):
	global runmax
	find_string2 = "-"	
	find_string3 = "(%ebp)"
	temp = int(str_a.split(find_string3)[0].split(find_string2)[1])
	if temp >= runmax:
		runmax = temp
	# print (runmax)

def file_opener(file_name):
	try:
		file_var = open(file_name, "r")	
		file_var.close()
	except:
		print("File Open Error")
		print_usage()

def out_file_opener(file_name):
	try:
		file_var = open(file_name, "w+")
		file_var.close()
	except:
		print("File Open Error")
		print_usage()

def output_file_opener(file_name):
	out_filename = os.path.basename(file_name)
	out_dirname = os.path.dirname(file_name)
	out_filename = out_filename.split(".")[0] + "_modified.s"
	if out_dirname == "" :
		out_name = out_dirname + "./" + out_filename
	else:
		out_name = out_dirname + "/./" + out_filename
	return out_name
	

def get_runmax(file_name):
	file_var = open(file_name, "r")
	toggle_flag = 0
	find_string = "movl\t$"
	find_string2 = "-"	
	find_string3 = "(%ebp)"
	find_string4 = "movss\t"
	
	for file_line in file_var.readlines():
		if file_line.find(find_string) != -1 : 
			split_str = file_line.split(",")[1]
			if split_str.find(find_string2) != -1 and split_str.find(find_string3) != -1: 			
				# print (file_line)
				update_runmax(split_str)
		elif file_line.find(find_string4) != -1 : 
			split_str = file_line.split(",")[0]
			if split_str.find(find_string2) != -1 and split_str.find(find_string3) != -1: 			
				# print (file_line)
				update_runmax(split_str)


def output_writer(in_name, out_name):
	global runmax
	in_file_var = open(in_name, "r")
	out_file_var = open(out_name, "w+")
	toggle_flag = 0
	find_string = "movl\t$"
	find_string2 = "-"	
	find_string3 = "(%ebp)"
	find_string4 = "movss\t"
	numLow = 0
	numHigh = 10000
	
	for file_line in in_file_var.readlines():
		out_file_var.write(file_line)
		if file_line.find(find_string) != -1 : 
			split_str = file_line.split(",")[1]
			if split_str.find(find_string2) != -1 and split_str.find(find_string3) != -1: 	
				write_val = random.randint(numLow, numHigh)		
				write_str = "\n\tmovl\t$" + str(write_val) + ", -" + str(runmax) + find_string3 + "\n" 
				out_file_var.write(write_str)
				runmax = runmax + 4
				
		elif file_line.find(find_string4) != -1 : 
			split_str = file_line.split(",")[0]
			if split_str.find(find_string2) != -1 and split_str.find(find_string3) != -1:
				write_val = random.randint(numLow, numHigh)		
				write_str = "\n\tmovl\t$" + str(write_val) + ", -" + str(runmax) + find_string3 + "\n" 
				out_file_var.write(write_str)
				runmax = runmax + 4 			
				

def run_dummycmdadder(input_args):
	global runmax
	file_name = input_args
	file_name = os.path.normpath(file_name)  
	file_opener(file_name)
	get_runmax(file_name)
	runmax = runmax + 4
	out_name = output_file_opener(file_name)
	out_file_opener(out_name)
	output_writer(file_name, out_name)
	return out_name
	# print ("End of Program...")
