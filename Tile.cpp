#include "Tile.h"

// Empty... for now?

Tile::Tile():letter(' '),value(0){}

Tile::Tile(Letter l, Value v){
    letter = l;
    value = v;
}
Tile::Tile(Tile &other)
   :letter(other.letter)
   ,value(other.value){}


    