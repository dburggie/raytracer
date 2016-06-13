
SRC = source
INC = include
BLD = build

CFLG = -Wall
CINC = -I${INC}
COPT = ${CFLG} ${CINC}
CC   = g++ ${COPT}

HDR = ${INC}/raytracer.h
OBJ = ${BLD}/Vector.o ${BLD}/Ray.o ${BLD}/Camera.o
OBJ += ${BLD}/RNG.o ${BLD}/Window.o ${BLD}/Image.o
OBJ += ${BLD}/World.o

BSRC = ${SRC}/bodies
BBLD = ${BLD}/bodies
BHDR = ${INC}/bodies.h
BOBJ = ${BBLD}/BasicBody.o ${BBLD}/Sphere.o ${BBLD}/Plane.o
BOBJ += ${BBLD}/CheckeredPlane.o ${BBLD}/Cylinder.o

SSRC = ${SRC}/skies
SBLD = ${BLD}/skies
SHDR = ${INC}/skies.h
SOBJ = ${SBLD}/BasicSky.o

LSRC = ${SRC}/lights
LBLD = ${BLD}/lights
LHDR = ${INC}/lights.h
LOBJ = ${LBLD}/BasicLight.o

DIRS = ${BLD} ${BBLD} ${SBLD} ${LBLD} ${TBLD}





all: ${DIRS} ${OBJ} ${BOBJ} ${SOBJ} ${LOBJ}





# ----- Build Directories -----

${BLD}:
	mkdir -p $@

${BBLD}:
	mkdir -p $@

${SBLD}:
	mkdir -p $@

${LBLD}:
	mkdir -p $@





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

${BLD}/Image.o: ${SRC}/Image.cpp ${HDR}
	${CC} -o $@ -c $<





# ----- Bodies -----

${BBLD}/BasicBody.o: ${BSRC}/BasicBody.cpp ${BHDR} ${HDR}
	${CC} -o $@ -c $<

${BBLD}/Sphere.o: ${BSRC}/Sphere.cpp ${BHDR} ${HDR}
	${CC} -o $@ -c $<

${BBLD}/Plane.o: ${BSRC}/Plane.cpp ${BHDR} ${HDR}
	${CC} -o $@ -c $<

${BBLD}/CheckeredPlane.o: ${BSRC}/CheckeredPlane.cpp ${BHDR} ${HDR}
	${CC} -o $@ -c $<

${BBLD}/Cylinder.o: ${BSRC}/Cylinder.cpp ${BHDR} ${HDR}
	${CC} -o $@ -c $<





# ----- Skies -----

${SBLD}/BasicSky.o: ${SSRC}/BasicSky.cpp ${SHDR} ${HDR}
	${CC} -o $@ -c $<





# ----- Lights -----

${LBLD}/BasicLight.o: ${LSRC}/BasicLight.cpp ${LHDR} ${HDR}
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
	rm -f ${BOBJ}
	rm -f ${SOBJ}
	rm -f ${LOBJ}
	rm -f ${TEXE}
	rm -f ${TOBJ}

