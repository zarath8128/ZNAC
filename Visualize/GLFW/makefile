include ../../makefile.v

LDLIBS += -lGL -lGLU -lglfw3 -lX11 -lXrandr -lXi -lXxf86vm -lrt -lpthread -lstdc++ ../PNG/PNGWriter.o -lpng ../OpenGL/Version.o ../OpenGL/Error.o
ALL += test libWindow.a
CLEAN=${ALL} *.o *.a

include ../../makefile.t

test:libWindow.a
libWindow.a:Window.o Window.h
