
SRC = source
INC = include
BLD = build

PNG = -lxspng

CFLG = -Wall -ggdb -Llib
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
BOBJ += ${BBLD}/CheckeredPlane.o ${BBLD}/Cylinder.o ${BBLD}/Builder.o

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

${BBLD}/Builder.o: ${BSRC}/Builder.cpp ${BHDR} ${HDR}
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

TEXE  = ${TBLD}/rng ${TBLD}/vector ${TBLD}/ray
TEXE += ${TBLD}/render ${TBLD}/image ${TBLD}/refraction
TEXE += ${TBLD}/blur ${TBLD}/cylinder
TEXE += ${TBLD}/glass_cylinder ${TBLD}/glass

TOBJ  = ${TBLD}/test_RNG.o ${TBLD}/test_Vector.o ${TBLD}/test_refraction.o
TOBJ += ${TBLD}/test_Ray.o ${TBLD}/test_render.o ${TBLD}/test_Image.o
TOBJ += ${TBLD}/test_blur.o ${TBLD}/test_Cylinder.o ${TBLD}/test_glass.o
TOBJ += ${TBLD}/test_blur.o ${TBLD}/test_GlassCylinder.o

test: ${TBLD} ${TEXE}

${TBLD}:
	mkdir -p $@

${TBLD}/rng: ${TBLD}/test_RNG.o ${BLD}/RNG.o
	g++ -o $@ $^
	./$@

${TBLD}/test_RNG.o: ${TSRC}/test_RNG.cpp ${HDR}
	${CC} -o $@ -c $<

${TBLD}/vector: ${TBLD}/test_Vector.o ${BLD}/Vector.o ${BLD}/RNG.o
	${CC} -o $@ $^
	./$@

${TBLD}/test_Vector.o: ${TSRC}/test_Vector.cpp ${HDR}
	${CC} -o $@ -c $<

${TBLD}/ray: ${TBLD}/test_Ray.o ${BLD}/Vector.o ${BLD}/Ray.o ${BLD}/RNG.o
	${CC} -o $@ $^
	./$@

${TBLD}/test_Ray.o: ${TSRC}/test_Ray.cpp ${HDR}
	${CC} -o $@ -c $<

${TBLD}/render: ${TBLD}/test_render.o ${OBJ} ${BOBJ} ${LOBJ} ${SOBJ} 
	${CC} -o $@ $^ ${PNG}

${TBLD}/test_render.o: ${TSRC}/test_render.cpp ${HDR} ${BHDR}
	${CC} -o $@ -c $<

${TBLD}/image: ${TBLD}/test_Image.o ${BLD}/Vector.o ${BLD}/Image.o ${BLD}/RNG.o
	${CC} -o $@ $^ ${PNG}

${TBLD}/test_Image.o: ${TSRC}/test_Image.cpp ${HDR}
	${CC} -o $@ -c $<

${TBLD}/refraction: ${TBLD}/test_refraction.o ${OBJ} ${BOBJ} ${LOBJ} ${SOBJ} 
	${CC} -o $@ $^ ${PNG}

${TBLD}/test_refraction.o: ${TSRC}/test_refraction.cpp ${HDR} ${BHDR}
	${CC} -o $@ -c $<

${TBLD}/blur: ${TBLD}/test_blur.o ${OBJ} ${BOBJ} ${LOBJ} ${SOBJ} 
	${CC} -o $@ $^ ${PNG}

${TBLD}/test_blur.o: ${TSRC}/test_blur.cpp ${HDR} ${BHDR}
	${CC} -o $@ -c $<

${TBLD}/cylinder: ${TBLD}/test_Cylinder.o ${OBJ} ${BOBJ} ${LOBJ} ${SOBJ} 
	${CC} -o $@ $^ ${PNG}

${TBLD}/test_Cylinder.o: ${TSRC}/test_Cylinder.cpp ${HDR} ${BHDR}
	${CC} -o $@ -c $<

${TBLD}/glass: ${TBLD}/test_glass.o ${OBJ} ${BOBJ} ${LOBJ} ${SOBJ}
	${CC} -o $@ $^ ${PNG}

${TBLD}/test_glass.o: ${TSRC}/test_glass.cpp ${HDR} ${BHDR}
	${CC} -o $@ -c $<

${TBLD}/glass_cylinder: ${TBLD}/test_GlassCylinder.o ${OBJ} ${BOBJ} ${LOBJ} ${SOBJ}
	${CC} -o $@ $^ ${PNG}

${TBLD}/test_GlassCylinder.o: ${TSRC}/test_GlassCylinder.cpp ${HDR} ${BHDR}
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

