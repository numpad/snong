CC=g++ -std=c++14
CFLAGS=-c -Wall -pedantic
LDFLAGS=-lm -lsfml-graphics -lsfml-window -lsfml-system
SOURCES=main.cpp Background.cpp Ball.cpp Random.cpp
OBJECTS=$(SOURCES:%.cpp=%.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm *.o