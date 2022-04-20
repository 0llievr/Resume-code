INCLUDE_DIRS = -I/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/include/
LIB_DIRS = -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib/debug -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib
#LIB_DIRS = -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib/release -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib
CC = mpicc
CXX = mpicxx

CDEFS=
CFLAGS= -g -Wall $(INCLUDE_DIRS) $(CDEFS)
LIBS=

PRODUCT= LRS_Double LRS_Float TS_Double TS_Float

HFILES= 
CFILES= LRS_Double.c LRS_Float.c TS_Double.c TS_Float.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~
	-rm -f ${PRODUCT} ${DERIVED} ${GARBAGE}

LRS_Double: LRS_Double.o
	mpicc -g -Wall -o LRS_Double LRS_Double.c -lm

LRS_Float: LRS_Float.o
	mpicc -g -Wall -o LRS_Float LRS_Float.c -lm

TS_Double: TS_Double.o
	mpicc -g -Wall -o TS_Double TS_Double.c -lm

TS_Float: TS_Float.o
	mpicc -g -Wall -o TS_Float TS_Float.c -lm