import sys
import os
import random

def print_usage():
	print ("Invalid Command Line Options")
	print ("Usage : ObjDumpAnalyzer.py $filename-objdump.txt $outputfilename.txt")
	exit(-1)

def file_opener(file_name):
	try:
		file_var = open(file_name, "r")	
		file_var.close()
	except:
		print("File Open Error")
		print_usage()


def output_writer(in_name, out_name):
	in_file_var = open(in_name, "r")
	out_file_var = open(out_name, "w+")
	find_string = "movl   $"
	find_string2 = "-"	
	find_string3 = "(%ebp)"
	find_string4 = "movss  "
	
	for file_line in in_file_var.readlines():
		if file_line.find(find_string) != -1 : 
			split_str = file_line.split(",")[1]
			if split_str.find(find_string2) != -1 and split_str.find(find_string3) != -1: 	
				write_val = file_line.split(":")[0]		
				write_str = "r " + str(write_val) + "\n"
				out_file_var.write(write_str)
				
		elif file_line.find(find_string4) != -1 : 
			split_str = file_line.split(",")[0]
			if split_str.find(find_string2) != -1 and split_str.find(find_string3) != -1:
				write_val = file_line.split(":")[0]		
				write_str = "w " + str(write_val) + "\n"
				out_file_var.write(write_str)			
				

def run_objdumpanalyzer(input_args, outputfilename):
	file_name = input_args
	file_name = os.path.normpath(file_name)  
	file_opener(file_name)
	output_writer(file_name, outputfilename)

# run_objdumpanalyzer("access-objdump.txt", "victim_trace.txt")
# run_objdumpanalyzer("circles-objdump.txt", "victim_trace.txt")
