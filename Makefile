SRC = ./src
OBJ = ./obj
BIN = ./bin
INCLUDE = ./include
DEMO = ./demo
FLAG = -O3

all: libLogica mydemos

libLogica: \
	$(OBJ)/arvore.o \
	$(OBJ)/heap_sort.o \
	$(OBJ)/lsep_formulas.o

mydemos: clean_demo \
	$(BIN)/main

$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	gcc $(FLAG) -c $< -I $(INCLUDE) -o $@

$(BIN)/%: $(DEMO)/%.c
	gcc $(FLAG) $< $(OBJ)/*.o -I $(INCLUDE) -lm -Wall -o $@

run:
	$(BIN)/main

clear:
	rm -rf $(BIN)/* $(OBJ)/*

clean_demo:
		rm -rf $(BIN)/*
