CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp config-tool.cpp input.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=config-tool

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(EXECUTABLE) *.o
