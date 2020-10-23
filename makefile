run:
	g++ *.cpp -std=c++2a -o a.out
	./a.out -v -e -t -sP2 ${a} ../rfile > log.txt
clean:
	rm *.out