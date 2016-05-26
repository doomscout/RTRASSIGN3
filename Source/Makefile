# Linux (default)
TARGET = ../Bin/Assignment3
CC = g++
DEBUG = -g
LDFLAGS = -lm -lGL -lGLU -lSDL2 -lglut
OPT = -O3
CPPFLAGS = -Wall -Wextra -pedantic -std=c++11 $(OPT) $(DEBUG) -lGLEW
SRC = Main.cpp Point2f.cpp Ball.cpp Arena.cpp Collisions.cpp Peg.cpp
OBJ := $(SRC:.cpp=.o)
#executable
all : $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

-include depend

depend :
	$(CC) $(CPPFLAGS) -MM $(SRC) > depend

.PHONY : clean

clean :
	-rm -f depend
	-rm -f $(TARGET) $(OBJ)
	-rm -f *~ 
