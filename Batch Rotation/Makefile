PRODUCT = rotate_linear rotate_parallel

all:${PRODUCT}

clean:
	-rm -f *.o cards_3x4_ppm_rotate/*.ppm
	-rm -f ${PRODUCT} 

rotate_linear: rotate_linear.o
	g++ -g -Wall -std=c++11 rotate_linear.cpp -o rotate_linear

rotate_parallel: rotate_parallel.o
	g++ -g -Wall rotate_parallel.cpp -lpthread -o rotate_parallel
