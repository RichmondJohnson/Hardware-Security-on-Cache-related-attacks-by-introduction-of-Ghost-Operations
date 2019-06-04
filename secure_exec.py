import os
import sys
import DummyCmdAdder
import ObjDumpAnalyzer

victim_trace_file = "victim_trace.txt"

def print_usage():
	print ("Invalid Command Line Options")
	print ("Usage : secure_exec.py $filename.c -secexec=ON/OFF")
	exit(-1)

def file_opener(file_name):
	try:
		file_var = open(file_name, "r")	
		file_var.close()
	except:
		print("File Open Error")
		print_usage()


def getsecureexec(options):
	ON_str = "ON"
	OFF_str = "OFF"
	try:
		secure_status = options.split("-secexec=")[1]
		if secure_status.find(ON_str) != -1 :
			return 1
		elif secure_status.find(OFF_str) != -1 :
			return 0
		else :
			print("Cmd Options Error")
			print_usage()		
		
	except:
		print("Cmd Options Error")
		print_usage()


def convertctoll(filename):
	out_filename = os.path.basename(file_name)
	out_dirname = os.path.dirname(file_name)
	out_filename = out_filename.split(".")[0] + ".ll"
	if out_dirname == "" :
		out_name = out_dirname + "./" + out_filename
	else:
		out_name = out_dirname + "/./" + out_filename
	cmd_string = "clang -emit-llvm -S -c " + str(filename) + " -o " + out_name
	os.system(cmd_string)
	return out_name


def convertlltos(filename):
	out_filename = os.path.basename(file_name)
	out_dirname = os.path.dirname(file_name)
	out_filename = out_filename.split(".")[0] + ".s"
	if out_dirname == "" :
		out_name = out_dirname + "./" + out_filename
	else:
		out_name = out_dirname + "/./" + out_filename
	cmd_string = "llc " + str(filename)
	os.system(cmd_string)
	return out_name


def convertstoexe(filename):
	out_filename = os.path.basename(file_name)
	out_dirname = os.path.dirname(file_name)
	out_filename = out_filename.split(".")[0]
	if out_dirname == "" :
		out_name = out_dirname + "./" + out_filename
	else:
		out_name = out_dirname + "/./" + out_filename
	cmd_string = "gcc -o " + out_name + " " + filename + " -Wl,-Ttext=0x40000000"
	os.system(cmd_string)
	return out_name


def getobjdump(filename):
	out_filename = os.path.basename(file_name)
	out_dirname = os.path.dirname(file_name)
	out_filename = out_filename.split(".")[0] + "-objdump.txt"
	if out_dirname == "" :
		out_name = out_dirname + "./" + out_filename
	else:
		out_name = out_dirname + "/./" + out_filename
	cmd_string = "objdump -D " + filename + " > " + out_name
	os.system(cmd_string)
	return out_name



if(len(sys.argv) != 3):
	print_usage()
file_name = sys.argv[1]
secureexecflag = 0
secureexecflag = getsecureexec(sys.argv[2])
file_name = os.path.normpath(file_name)  
file_opener(file_name)
ll_name = convertctoll(file_name)
s_name = convertlltos(ll_name)
if secureexecflag == 1:
	modified_s_name = DummyCmdAdder.run_dummycmdadder(s_name)
else :
	modified_s_name = s_name
exec_name = convertstoexe(modified_s_name)
objdump_name = getobjdump(exec_name)
ObjDumpAnalyzer.run_objdumpanalyzer(objdump_name, victim_trace_file)

#final step -> transferring to profiling tool
run_cmd = "make"
os.system(run_cmd)
