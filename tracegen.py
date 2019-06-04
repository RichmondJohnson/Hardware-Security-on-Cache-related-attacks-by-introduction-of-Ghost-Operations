import os,sys,re

file = open("cache.h","r")

for line in file:
	m=re.search("define\s+L1_blocksize\s+(\d+)",line)
	n=re.search("define\s+L2_size\s+(\d+)",line)

	if m:
		blocksize=int(m.group(1))
	if n:
		l2_size=int(n.group(1))

total_blocks=l2_size/blocksize

file.close()

addr = "40000400"
trace_file = open("attacker_trace.txt","w")
#for i in range(0,int(sys.argv[1])):
for i in range(0,total_blocks):
	trace_file.write("r"+" "+str(addr)+"\n")
	temp = int(addr,16)
	temp = temp+32
	temp2 = hex(temp)
	addr = temp2[2:]

trace_file.close()
