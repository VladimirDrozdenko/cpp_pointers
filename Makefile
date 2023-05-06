CXX=g++
OBJECTS=main.o
BIN=pointers_play
CXXFLAGS=-std=c++17 -Wall 

all: $(BIN)

$(BIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(OBJECTS)

clean:
	rm -r $(OBJECTS) $(BIN) *.dSYM
