#apt install libomp-dev

APP = ./shapes

CXX = g++

ifdef DEBUG
CXXFLAGS = -Wall -g -ggdb
else
CXXFLAGS = -fopenmp -Wall -O3 -DMULTI_PROC=1
LDLIBS = -lgomp
endif

SRC := $(shell find . -maxdepth 1 -name "*.hpp")

all: ${APP}

${APP}: main.cpp ${SRC}
	${CXX} ${CXXFLAGS} ${LDFLAGS} -o ${APP} main.cpp ${LDLIBS}
	chmod +x ${APP}

clean:
	rm -f ${APP}
