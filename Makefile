
SRC = source
INC = include
BLD = build

PNG = -lpng

CFLG = -Wall -ggdb
CINC = -I${INC}
COPT = ${CFLG} ${CINC}
CC   = g++ ${COPT}

HDR = ${INC}/raytracer.h
OBJ = ${BLD}/Vector.o ${BLD}/Ray.o ${BLD}/Camera.o
OBJ += ${BLD}/RNG.o ${BLD}/Window.o ${BLD}/Image.o
OBJ += ${BLD}/World.o ${BLD}/Tracer.o

BSRC = ${SRC}/bodies
BBLD = ${BLD}/bodies
BHDR = ${INC}/bodies.h
BOBJ = ${BBLD}/BasicBody.o ${BBLD}/Sphere.o ${BBLD}/Plane.o
BOBJ += ${BBLD}/CheckeredPlane.o ${BBLD}/Cylinder.o ${BBLD}/Glass.o

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

${BLD}/Tracer.o: ${SRC}/Tracer.cpp ${HDR}
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

${BBLD}/Glass.o: ${BSRC}/Glass.cpp ${BHDR} ${HDR}
	${CC} -o $@ -c $<





# ----- Skies -----

${SBLD}/BasicSky.o: ${SSRC}/BasicSky.cpp ${SHDR} ${HDR}
	${CC} -o $@ -c $<





# ----- Lights -----

${LBLD}/BasicLight.o: ${LSRC}/BasicLight.cpp ${LHDR} ${HDR}
	${CC} -o $@ -c $<





# ----- Tests -----

TSRC = test
TBLD = ${BLD}/tests

TEXE = ${TBLD}/test_RNG ${TBLD}/test_Vector ${TBLD}/test_Ray
TEXE += ${TBLD}/test_render ${TBLD}/test_Image ${TBLD}/test_refraction
TEXE += ${TBLD}/test_glass

TOBJ = ${TBLD}/test_RNG.o ${TBLD}/test_Vector.o ${TBLD}/test_refraction.o
TOBJ += ${TBLD}/test_Ray.o ${TBLD}/test_render.o ${TBLD}/test_Image.o
TOBJ += ${TBLD}/test_glass.o

test: ${TBLD} ${TEXE}

${TBLD}:
	mkdir -p $@

${TBLD}/test_RNG: ${TBLD}/test_RNG.o ${BLD}/RNG.o
	g++ -o $@ $^
	./$@

${TBLD}/test_RNG.o: ${TSRC}/test_RNG.cpp ${HDR}
	${CC} -o $@ -c $<

${TBLD}/test_Vector: ${TBLD}/test_Vector.o ${BLD}/Vector.o ${BLD}/RNG.o
	${CC} -o $@ $^
	./$@

${TBLD}/test_Vector.o: ${TSRC}/test_Vector.cpp ${HDR}
	${CC} -o $@ -c $<

${TBLD}/test_Ray: ${TBLD}/test_Ray.o ${BLD}/Vector.o ${BLD}/Ray.o ${BLD}/RNG.o
	${CC} -o $@ $^
	./$@

${TBLD}/test_Ray.o: ${TSRC}/test_Ray.cpp ${HDR}
	${CC} -o $@ -c $<

${TBLD}/test_render: ${TBLD}/test_render.o ${OBJ} ${BOBJ} ${LOBJ} ${SOBJ} 
	${CC} -o $@ ${PNG} $^

${TBLD}/test_render.o: ${TSRC}/test_render.cpp ${HDR} ${BHDR}
	${CC} -o $@ -c $<

${TBLD}/test_Image: ${TBLD}/test_Image.o ${BLD}/Vector.o ${BLD}/Image.o ${BLD}/RNG.o
	${CC} -o $@ ${PNG} $^

${TBLD}/test_Image.o: ${TSRC}/test_Image.cpp ${HDR}
	${CC} -o $@ -c $<

${TBLD}/test_refraction: ${TBLD}/test_refraction.o ${OBJ} ${BOBJ} ${LOBJ} ${SOBJ} 
	${CC} -o $@ ${PNG} $^

${TBLD}/test_refraction.o: ${TSRC}/test_refraction.cpp ${HDR} ${BHDR}
	${CC} -o $@ -c $<

${TBLD}/test_glass: ${TBLD}/test_glass.o ${OBJ} ${BOBJ} ${LOBJ} ${SOBJ} 
	${CC} -o $@ ${PNG} $^

${TBLD}/test_glass.o: ${TSRC}/test_glass.cpp ${HDR} ${BHDR}
	${CC} -o $@ -c $<





# ----- Clean -----

clean:
	rm -f ${OBJ}
	rm -f ${BOBJ}
	rm -f ${SOBJ}
	rm -f ${LOBJ}
	rm -f ${TOBJ}

clobber:
	rm -f ${EXE}
	rm -f ${OBJ}
	rm -f ${BOBJ}
	rm -f ${SOBJ}
	rm -f ${LOBJ}
	rm -f ${TEXE}
	rm -f ${TOBJ}

