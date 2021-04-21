OBJS = main.cpp

OBJ_NAME = tower

all : $(OBJS)
	g++ $(OBJS) -w -lSDL2 -o $(OBJ_NAME)

test : all
	./tower