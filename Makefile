INCLUDE := ./include
SRC := ./src
BIN := ./bin
FLAGS := -Wall

all: $(BIN) $(BIN)/main

$(BIN):
	if [ ! -d $(BIN) ]; then mkdir $(BIN); fi

$(BIN)/main: $(BIN)/fraction.o $(INCLUDE)/matrix.hpp main.cpp
	$(CXX) -I. $(BIN)/fraction.o main.cpp -o $(BIN)/main $(FLAGS)

$(BIN)/fraction.o: $(INCLUDE)/fraction.hpp $(SRC)/fraction.cpp
	$(CXX) -c -I. $(SRC)/fraction.cpp -o $(BIN)/fraction.o $(FLAGS)

clean:
	rm $(BIN)/*
	rmdir $(BIN)