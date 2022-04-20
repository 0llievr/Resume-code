CDEFS=
OMP_CFLAGS= -O0 -fopenmp $(INCLUDE_DIRS) $(CDEFS)
CFLAGS= -g -Wall $(INCLUDE_DIRS) $(CDEFS)
LIBS=

PRODUCT= newton_rap falsi falsi_multi falsi_multi_omp

HFILES= 
CFILES= newton_rap.c falsi.c falsi_multi.c falsi_multi_omp.c
all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~
	-rm -f ${PRODUCT} ${DERIVED} ${GARBAGE}


newton_rap: newton_rap.c
	gcc -g -Wall newton_rap.c -o newton_rap -lm

falsi: falsi.c
	gcc -g -Wall falsi.c -o falsi -lm

falsi_multi: falsi_multi.c
	gcc -g -Wall falsi_multi.c -o falsi_multi -lm

falsi_multi_omp: falsi_multi_omp.c
	gcc -fopenmp -o falsi_multi_omp falsi_multi_omp.c -lm