include ../../makefile.v

LDLIBS = -lGL -lGLU -lglfw3 -lX11 -lXrandr -lXi -lXxf86vm -lrt -lstdc++ -lpthread -lstdc++
ALL += test Window.a
CLEAN=${ALL} *.o

include ../../makefile.t

test:Window.a demo.o Camera.o Joystick.o
