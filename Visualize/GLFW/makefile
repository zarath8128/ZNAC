include ../../makefile.v

LDLIBS += -lGL -lGLU -lglfw3 -lX11 -lXrandr -lXi -lXxf86vm -lrt -lpthread -lstdc++ ../libpng/PNGWriter.o -lpng
ALL += test libWindow.a
CLEAN=${ALL} *.o *.a

include ../../makefile.t

test:libWindow.a demo.o Camera.o Joystick.o
libWindow.a:Window.o
