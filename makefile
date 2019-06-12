CXX = g++
CXXFLAGS = -std=c++11 -g
OBJS = air.o game.o menu.o space.o itemSpace.o keySpace.o emptySpace.o actionSpace.o leakSpace.o lockedSpace.o item.o firstAid.o plug.o junk.o key.o player.o
SRCS = air.cpp game.cpp menu.cpp space.cpp itemSpace.cpp keySpace.cpp emptySpace.cpp actionSpace.cpp leakSpace.cpp lockedSpace.cpp item.cpp firstAid.cpp plug.cpp junk.cpp key.cpp player.cpp
HEADERS = menu.hpp game.hpp space.hpp itemSpace.hpp keySpace.hpp emptySpace.hpp actionSpace.hpp leakSpace.hpp lockedSpace.hpp item.hpp firstAid.hpp plug.hpp junk.hpp key.hpp player.hpp spaceType.hpp itemType.hpp chances.hpp

air:${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o air

${OBJS}: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} -c ${@:.o=.cpp}

clean:
	rm *.o air

zip:
	zip -D FinalProject_Lin_Jay.zip *.cpp *.hpp *.pdf *.txt makefile

val:
	valgrind --leak-check=full ./air