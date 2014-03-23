include ../makefile.v

LDLIBS=-lGL -lglfw3 -lXi -lXxf86vm -lrt -lX11 -lpthread -lXrandr

ALL=test
CLEAN=${ALL}

include ../makefile.t

test:Screen.o Screen.h GLFW/Window.o GLUtility.o
