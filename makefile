CFLG = -Wall
CINC = -Isrc
COPT = ${CFLG} ${CINC}
CC   = g++ ${COPT}

SRC = src
BLD = bld

HDR = ${SRC}/raytracer.h
OBJ = ${BLD}/Vector.o ${BLD}/Ray.o ${BLD}/BasicBody.o

all: ${OBJ}

clean:
	rm -f ${OBJ}


${BLD}/Vector.o: ${SRC}/Vector.cpp ${HDR}
	${CC} -o $@ -c $<

${BLD}/Ray.o: ${SRC}/Ray.cpp ${HDR}
	${CC} -o $@ -c $<

${BLD}/BasicBody.o: ${SRC}/BasicBody.cpp ${HDR}
	${CC} -o $@ -c $<



