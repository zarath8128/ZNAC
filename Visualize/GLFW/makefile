include ../../makefile.v

LD=${CXX} -E
LDLIBS += -lglfw3 -lGL -lGLU -lXrandr -lXi -lrt -lstdc++ -lXxf86vm
ALL += test Window.a
CLEAN=${ALL} *.o

include ../../makefile.t

test:Window.a demo.o Camera.o Joystick.o
