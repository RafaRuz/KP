SRC = src
INC = include
OBJ = obj
BIN = bin

CXX = g++
CXXFLAGS =  -Wall -Wextra -pedantic -std=c++03 -g  -I$(INC)

all: $(BIN)/blind_search

# ************ Compilación de módulos ************

$(OBJ)/blind_search.o : $(SRC)/blind_search.cpp $(INC)/blind_search.h
	$(CXX) -c $(CXXFLAGS) $(SRC)/blind_search.cpp -o $(OBJ)/blind_search.o
$(BIN)/blind_search : $(OBJ)/blind_search.o
	$(CXX) -o $(BIN)/blind_search $(OBJ)/blind_search.o


# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/*
