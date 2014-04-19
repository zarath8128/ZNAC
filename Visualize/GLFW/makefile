include ../../makefile.v

LDLIBS += -lGL -lGLU -lglfw3 -lX11 -lXrandr -lXi -lXxf86vm -lrt -lpthread -lstdc++ ../PNG/PNGWriter.o -lpng ../OpenGL/Version.o ../OpenGL/Error.o -lftgl
ALL += test libWindow.a
CLEAN=${ALL} *.o *.a

include ../../makefile.t

test:libWindow.a Capture.o 
libWindow.a:Window.o Window.h Joystick.o Joystick.h Camera.o Camera.h
