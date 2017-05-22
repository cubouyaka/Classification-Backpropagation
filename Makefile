SOURCES = main.cpp network.cpp network.h neuron.h
CC = g++
FLAGS = -Wall
EXEC = main

all: $(EXEC)

$(EXEC): $(SOURCES)
	$(CC) $(SOURCES) -o $(EXEC) $(FLAGS)

clean:
	rm $(EXEC)
	rm *~
