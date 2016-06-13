
SRC = src
INC = src
BLD = bld

CFLG = -Wall
CINC = -I${INC}
COPT = ${CFLG} ${CINC}
CC   = g++ ${COPT}

OBJ = ${BLD}/Vector.o ${BLD}/Ray.o ${BLD}/Camera.o
OBJ += ${BLD}/RNG.o ${BLD}/Window.o
OBJ += ${BLD}/World.o

BDY = ${BLD}/BasicBody.o ${BLD}/Sphere.o ${BLD}/Plane.o
BDY += ${BLD}/CheckeredPlane.o ${BLD}/Cylinder.o

SKY = ${BLD}/BasicSky.o

LGT = ${BLD}/BasicLight.o

HDR = ${INC}/raytracer.h




all: ${OBJ} ${BDY} ${SKY} ${LGT}





# ----- Objects -----

${BLD}/Vector.o: ${SRC}/Vector.cpp ${HDR}
	${CC} -o $@ -c $<

${BLD}/Ray.o: ${SRC}/Ray.cpp ${HDR}
	${CC} -o $@ -c $<

${BLD}/RNG.o: ${SRC}/RNG.cpp ${HDR}
	${CC} -o $@ -c $<

${BLD}/Window.o: ${SRC}/Window.cpp ${HDR}
	${CC} -o $@ -c $<

${BLD}/Camera.o: ${SRC}/Camera.cpp ${HDR}
	${CC} -o $@ -c $<

${BLD}/World.o: ${SRC}/World.cpp ${HDR}
	${CC} -o $@ -c $<





# ----- Bodies -----

BDYHDR = ${HDR} ${INC}/bodies.h

${BLD}/BasicBody.o: ${SRC}/BasicBody.cpp ${BDYHDR}
	${CC} -o $@ -c $<

${BLD}/Sphere.o: ${SRC}/Sphere.cpp ${BDYHDR}
	${CC} -o $@ -c $<

${BLD}/Plane.o: ${SRC}/Plane.cpp ${BDYHDR}
	${CC} -o $@ -c $<

${BLD}/CheckeredPlane.o: ${SRC}/CheckeredPlane.cpp ${BDYHDR}
	${CC} -o $@ -c $<

${BLD}/Cylinder.o: ${SRC}/Cylinder.cpp ${BDYHDR}
	${CC} -o $@ -c $<





# ----- Skies -----

SKYHDR = ${HDR} ${INC}/skies.h

${BLD}/BasicSky.o: ${SRC}/BasicSky.cpp ${SKYHDR}
	${CC} -o $@ -c $<





# ----- Lights -----

LGTHDR = ${HDR} ${INC}/lights.h

${BLD}/BasicLight.o: ${SRC}/BasicLight.cpp ${LGTHDR}
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
	rm -f ${BDY}
	rm -f ${SKY}
	rm -f ${LGT}
	rm -f ${TOBJ}

clobber:
	rm -f ${EXE}
	rm -f ${OBJ}
	rm -f ${TEXE}
	rm -f ${TOBJ}

