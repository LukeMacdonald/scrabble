#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node {
public:
   // Constructor
   Node(Tile* tile, Node* next,Node* prev);
   // Copy Constructor
   Node(Node& other);

   // reference to tile
   Tile*    tile;
   // reference needed to point to next node in LinkedList
   Node*    next;
   // reference needed to point to previous node in LinkedList
   Node*    prev;
   
   
};

#endif // ASSIGN2_NODE_H
