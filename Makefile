CC=g++
SRCPATH=./
OBJPATH=./

bdd: parser.o gerentebdd.o mainTesteBdds.o
	$(CC) parser.o gerentebdd.o mainTesteBdds.o -o bdd 

parser.o: parser.cpp
	$(CC) -c parser.cpp -o parser.o

gerentebdd.o: gerentebdd.cpp
	$(CC) -c gerentebdd.cpp -o gerentebdd.o

mainTesteBdds.o: mainTesteBdds.cpp
	$(CC) -c mainTesteBdds.cpp -o mainTesteBdds.o

clean:
	rm -f *.o bdd
