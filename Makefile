all:
	sh final_run.sh

compile:
	g++ -o main main.cpp

genatt:
	python tracegen.py

simulate:
	./main attacker_trace.txt victim_trace.txt

clean:
	rm main
