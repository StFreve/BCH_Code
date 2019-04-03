CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=Source.cpp BinPolynom.cpp BCH.cpp Polynom.cpp Utilities.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=bch

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

test:
	./$(EXECUTABLE)
