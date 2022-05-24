.default: all

all: scrabble

clean:
	rm -rf scrabble *.o *.dSYM

scrabble: LinkedList.o Node.o PlayerHand.o Tile.o TileBag.o scrabble.o Board.o Dictionary.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^