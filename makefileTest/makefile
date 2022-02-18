CC = g++
CFLAG = -g
PROJECTPATH = $(shell ls)
PROJECT = test

build:all
	echo "Hello world!"

all:
	echo "Compile this project!"
	$(info $(PROJECTPATH))
	$(CC) -o $(PROJECT) main.cpp $(CFLAG)
	echo "hello world!"

.PHONY:clean
clean:
	echo "Clean executive program file!"
	rm -rf $(PROJECT)

