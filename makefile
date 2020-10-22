run:
	g++ *.cpp -std=c++2a -o a.out
	./a.out -v -e -t -sS ${a} ../rfile
clean:
	rm *.out