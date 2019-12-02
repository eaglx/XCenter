PROJECTNAME = dev-center
CC = g++
CFLAGS = -Wall -Wextra -std=c++11 -lX11 -lXtst -g # -g for debug
PRSOURCES = main.cpp Mouse.cpp
PROBJECTS = $(PRSOURCES:.cpp=.o)
PREXEC = $(PROJECTNAME).exe

.PHONY: all project

all: project
project: $(PREXEC)

$(PREXEC): $(PROBJECTS)
	$(CC) $(PROBJECTS) -o $(PREXEC) $(CFLAGS)

# telling make how to turn file.cpp into file.o for an arbitary file
.cpp.o:
	$(CC) -c $^ -o $@ $(CFLAGS)

clean:
	rm ./*.o
	rm ./*.exe

run:
	./$(PREXEC)