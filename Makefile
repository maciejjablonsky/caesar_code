SRC=src
BUILD=build

all: clean pre-build cli.o cypher.o libcypher.a  main.o main-build

pre-build:
	mkdir -p build

main-build:
	gcc -g -Wall -o cypher $(BUILD)/main.o $(BUILD)/cli.o $(BUILD)/libcypher.a 

main.o: 
	gcc -g -o $(BUILD)/main.o -c $(SRC)/main.c  
	
cypher.o: 
	gcc -g  -o $(BUILD)/cypher.o  -c $(SRC)/cypher.c 

libcypher.a: 
	ar r $(BUILD)/libcypher.a $(BUILD)/cypher.o

cli.o:
	gcc -g -c $(SRC)/cli.c -o $(BUILD)/cli.o

clean:
	rm -r $(BUILD)
