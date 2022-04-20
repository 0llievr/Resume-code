info:
	@echo "The test directory holds 10 main-functions, each comprising a test: run01, run02, ..., run10"
	@echo "An 11th main-function all_main.cpp (run_all), combines all 10 tests.\n"
	@echo "misc_src contains the main-function from the project writeup, and a simple main-function to exercise"
	@echo "the functions of the stamp library (set_die, eject_plate, et cetera).\n"
	@echo "This Makefile assumes files stampbuf.{h,cpp} and stampstream.{h,cpp} exist."
	@echo "make run_all"
	@echo "make run01"
	@echo "etc.\n"
	@echo "The tests directory contains files with expected output. Use diff (or vimdiff) to compare output."
	@echo "One technique for a build/test cycle:"
	@echo "make run01 && ./run01 | diff -s tests/01.out - #the hyphen in diff compares 01.out to the pipe's output"




run_all: tests/all_main.cpp stampstream.h stampstream.o stampbuf.o stamp.o
	g++ -I. -std=c++17 -o run_all tests/all_main.cpp stampbuf.o stampstream.o stamp.o

run01: tests/01_main.cpp stampstream.h stampstream.o stampbuf.o stamp.o 
	g++ -I. -std=c++17 -o run01 tests/01_main.cpp stampbuf.o stampstream.o stamp.o

run02: tests/02_main.cpp stampstream.h stampstream.o stampbuf.o stamp.o
	g++ -I. -std=c++17 -o run02 tests/02_main.cpp stampbuf.o stampstream.o stamp.o

run03: tests/03_main.cpp stampstream.h stampstream.o stampbuf.o stamp.o
	g++ -I. -std=c++17 -o run03 tests/03_main.cpp stampbuf.o stampstream.o stamp.o

run04: tests/04_main.cpp stampstream.h stampstream.o stampbuf.o stamp.o
	g++ -I. -std=c++17 -o run04 tests/04_main.cpp stampbuf.o stampstream.o stamp.o

run05: tests/05_main.cpp stampstream.h stampstream.o stampbuf.o stamp.o
	g++ -I. -std=c++17 -o run05 tests/05_main.cpp stampbuf.o stampstream.o stamp.o

run06: tests/06_main.cpp stampstream.h stampstream.o stampbuf.o stamp.o
	g++ -I. -std=c++17 -o run06 tests/06_main.cpp stampbuf.o stampstream.o stamp.o

run07: tests/07_main.cpp stampstream.h stampstream.o stampbuf.o stamp.o
	g++ -I. -std=c++17 -o run07 tests/07_main.cpp stampbuf.o stampstream.o stamp.o

run08: tests/08_main.cpp stampstream.h stampstream.o stampbuf.o stamp.o
	g++ -I. -std=c++17 -o run08 tests/08_main.cpp stampbuf.o stampstream.o stamp.o

run09: tests/09_main.cpp stampstream.h stampstream.o stampbuf.o stamp.o
	g++ -I. -std=c++17 -o run09 tests/09_main.cpp stampbuf.o stampstream.o stamp.o

run10: tests/10_main.cpp stampstream.h stampstream.o stampbuf.o stamp.o
	g++ -I. -std=c++17 -o run10 tests/10_main.cpp stampbuf.o stampstream.o stamp.o

stampstream.o: stampstream.cpp stampstream.h stampbuf.h
	g++ -I. -std=c++17 -c stampstream.cpp

stampbuf.o: stampbuf.cpp stampbuf.h
	g++ -I. -std=c++17 -c stampbuf.cpp

stamp.o: stamp.cpp stamp.h
	g++ -I. -std=c++17 -c stamp.cpp

clean:
	rm -f *.o a.out run0{01..09} run10 run_all
