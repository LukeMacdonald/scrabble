#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H
#include "Node.h"

class LinkedList {
public:

   LinkedList();
   // Clean-up the list
   ~LinkedList();

   // returns size of list
   int size();
   // removes everything in list
   void clear();
   // returns node at index i
   Node* get(int i);
   // creates new node at end of list
   void addBack(Tile* tile);
   // deletes the first node in list
   void removeFront();
   // 
   Tile* returnFront();
   // find node that contains the tile with the letter
   // specified in parameter and return the tile
   Tile* find(char letter);
   // find node that contains the tile with the letter
   // specified in parameter and replace the tile with
   // the new tile and return the old tile
   Tile* replace(char letter,Tile* new_tile);
   
private:
   // first node in LinkedList
   Node* head;
   // last node in LinkedList
   Node* tail;
   // number of nodes in LinkedList
   int length;
};
#endif // ASSIGN2_LINKEDLIST_H