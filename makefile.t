.PHONY:all clean

all:${ALL}
clean:
	rm -rf ${CLEAN}

reset:
	${MAKE} clean && reset && ${MAKE}

%.a:
	${AR} -r $@ $^

%.o:%.cu
	${NVCC} $^ -o $@
