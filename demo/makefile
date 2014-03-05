include ../makefile.v

ALL+=demo demoWindow.o
CLEAN+=${ALL}

LDLIBS=../Visualize/GLFW/Camera.o ../Visualize/GLFW/Joystick.o -lglfw3 -lGL -lGLU -lX11 -lXxf86vm -lXrandr -lrt -lstdc++ -lpthread ../Visualize/GLFW/Window.a -lXi 
include ../makefile.t

demo:demoWindow.o demoWindow.h
