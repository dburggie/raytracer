CFLG = -Wall
CINC = -Isrc
COPT = ${CFLG} ${CINC}
CC   = gcc ${COPT}

SRC = src
BLD = bld

HDR = ${SRC}/raytracer.h
OBJ = 

${BLD}/Vector.o: ${SRC}/Vector.cpp ${HDR}
	${CC} -c $< -o $@


