main : main.cpp
	g++ -o main  -O2 -std=c++11 main.cpp -fopenmp

tobin : tobin.cpp
	g++ -o tobin -O2 -std=c++11 tobin.cpp 

totxt : totxt.cpp
	g++ -o totxt -O2 -std=c++11 totxt.cpp 	

test: tobin totxt main
	#./tobin test.txt input.bin
	./main 1 25
	./totxt input.bin input.txt
	./totxt output.bin output.txt
	make clean

clean:
	rm -f totxt tobin main *.bin newtest.txt *-*-*