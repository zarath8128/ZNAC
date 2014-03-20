include ../makefile.v

LDLIBS+=-lglfw3 -lGL -lX11 -lXxf86vm -lXrandr -lXi -lpthread -lrt
VPATH+=:../Visualize/GLFW
ALL=test rndVertexer
CLEAN=${ALL}

include ../makefile.t

test:Graph.h -lWindow
