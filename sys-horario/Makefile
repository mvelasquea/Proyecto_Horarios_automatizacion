CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = bin/planificador

all: $(TARGET)

$(TARGET): $(OBJ) main.cpp
	mkdir -p bin
	$(CXX) $(CXXFLAGS) main.cpp $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

test: tests/test_grafo.cpp
	$(CXX) $(CXXFLAGS) tests/test_grafo.cpp src/GrafoHorario.cpp src/Curso.cpp -o bin/test_grafo && ./bin/test_grafo

clean:
	rm -rf bin *.o src/*.o
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
BIN = bin/planificador

all: $(BIN)

$(BIN): main.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ main.cpp $(OBJ)

run: all
	./$(BIN)

clean:
	rm -rf src/*.o $(BIN)
