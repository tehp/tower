OBJS = main.cpp terrain.cpp

OBJ_NAME = tower

all : $(OBJS)
	g++ $(OBJS) -w -lSDL2 -o $(OBJ_NAME) -std=c++20

test : all
	./tower