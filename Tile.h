#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H
#include <iostream>

// Define a Letter type
typedef char Letter;

// Define a Value type
typedef int Value;

class Tile {
public:
   Letter letter;
   Value  value;
   std::string player;

   Tile();
   Tile(Letter, Value);
   Tile(Tile &other);
};

#endif // ASSIGN2_TILE_H
