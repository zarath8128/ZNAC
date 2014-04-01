FLAGS += -Wextra -Wall -O2 ${INCLUDEDIR}
CFLAGS += -std=c99 ${FLAGS}
CXXFLAGS += -std=c++0x ${FLAGS}
LDLIBS ?= 
INCLUDEDIR ?= 

ALL ?= 
CLEAN ?= 

