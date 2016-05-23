CFLG = -Wall
CINC = -Isrc
COPT = ${CFLG} ${CINC}
CC   = gcc ${COPT}

SRC = src
BLD = bld

HDR = ${SRC}/raytracer.h
OBJ = ${BLD}/Vector.o ${BLD}/Ray.o

all: ${OBJ}

clean:
	rm -f ${OBJ}


${BLD}/Vector.o: ${SRC}/Vector.cpp ${HDR}
	${CC} -o $@ -c $<

${BLD}/Ray.o: ${SRC}/Ray.cpp ${HDR}
	${CC} -o $@ -c $<

