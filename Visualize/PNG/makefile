include ../../makefile.v

LDLIBS += -lpng -lGL -lGLU
ALL=test GLCapture.o
CLEAN=${ALL} *.o

include ../../makefile.t

test:PNGWriter.o PNGWriter.h GLCapture.o
