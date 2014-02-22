.PHONY:all clean

all:${ALL}
clean:
	rm -rf ${CLEAN}

%.a:%.o
	${AR} -r $@ $^
