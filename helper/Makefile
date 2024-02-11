CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=printer.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=printer

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(EXECUTABLE) *.o
