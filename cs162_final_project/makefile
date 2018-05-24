###############################################################################
## Author: Ngan Tran
## Date: 3/10/17
## Description: Makefile for the final project. Includes c++ flags, variables
## 	for the file types, and build instructions to compile the Alien game.
##	Also contains the instructions to clean the target program. 
##############################################################################

CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

OBJS = main.o Alien.o Barn.o Boat.o Game.o Garden.o House.o Lake.o
OBJS += Road.o Space.o Treehouse.o utilities.o

SRCS = main.cpp Alien.cpp Barn.cpp Boat.cpp Game.cpp Garden.cpp 
SRCS += House.cpp Lake.cpp Road.cpp Space.cpp Treehouse.cpp utilities.cpp

HEADERS = Alien.hpp Barn.hpp Boat.hpp Game.hpp Garden.hpp House.hpp 
HEADERS += Lake.hpp Road.hpp Space.hpp Treehouse.hpp utilities.hpp

Final: ${OBJS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} -o alien

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm -f ${OBJS} alien 


