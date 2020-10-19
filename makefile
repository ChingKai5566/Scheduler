run:
	g++ sched.cpp -std=c++2a -o a.out
	./a.out -v -e ${a} ../rfile
clean:
	rm *.out