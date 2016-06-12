CFLG = -Wall
CINC = -Isrc
COPT = ${CFLG} ${CINC}
CC   = g++ ${COPT}

SRC = src
BLD = bld

HDR = ${SRC}/raytracer.h
OBJ = ${BLD}/Vector.o ${BLD}/Ray.o ${BLD}/BasicBody.o
OBJ += ${BLD}/Sphere.o ${BLD}/Plane.o ${BLD}/CheckeredPlane.o
OBJ += ${BLD}/RNG.o ${BLD}/Cylinder.o ${BLD}/Window.o
OBJ += ${BLD}/Camera.o ${BLD}/BasicLight.o


all: ${OBJ}

${BLD}/Vector.o: ${SRC}/Vector.cpp ${HDR}
	${CC} -o $@ -c $<

${BLD}/Ray.o: ${SRC}/Ray.cpp ${HDR}
	${CC} -o $@ -c $<

${BLD}/BasicBody.o: ${SRC}/BasicBody.cpp ${HDR}
	${CC} -o $@ -c $<

${BLD}/Sphere.o: ${SRC}/Sphere.cpp ${HDR}
	${CC} -o $@ -c $<

${BLD}/Plane.o: ${SRC}/Plane.cpp ${HDR}
	${CC} -o $@ -c $<

${BLD}/CheckeredPlane.o: ${SRC}/CheckeredPlane.cpp ${HDR}
	${CC} -o $@ -c $<

${BLD}/RNG.o: ${SRC}/RNG.cpp ${HDR}
	${CC} -o $@ -c $<

${BLD}/Cylinder.o: ${SRC}/Cylinder.cpp ${HDR}
	${CC} -o $@ -c $<

${BLD}/Window.o: ${SRC}/Window.cpp ${HDR}
	${CC} -o $@ -c $<

${BLD}/Camera.o: ${SRC}/Camera.cpp ${HDR}
	${CC} -o $@ -c $<

${BLD}/BasicLight.o: ${SRC}/BasicLight.cpp ${HDR}
	${CC} -o $@ -c $<






# ----- Tests -----

TST  = test
TEXE = ${BLD}/test_RNG
TOBJ = ${BLD}/test_RNG.o

test: ${TEXE}

${BLD}/test_RNG: ${BLD}/test_RNG.o ${BLD}/RNG.o
	g++ -o $@ $^
	./$@

${BLD}/test_RNG.o: ${TST}/test_RNG.cpp ${HDR}
	${CC} -o $@ -c $<





# ----- Clean -----

clean:
	rm -f ${OBJ}
	rm -f ${TOBJ}

clobber:
	rm -f ${EXE}
	rm -f ${OBJ}
	rm -f ${TEXE}
	rm -f ${TOBJ}

