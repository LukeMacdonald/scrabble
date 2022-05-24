#ifndef TILEBAG
#define TILEBAG

#include "LinkedList.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


class TileBag
{
private:
    LinkedList* tiles;
public:
    TileBag();
    TileBag(std::string);
    TileBag(LinkedList*);
    ~TileBag();
    void populateList(std::string);
    Tile* getTile();
    void returnTile(Tile*);
    Tile* get(int i);
    int size();
    void save_details(std::ofstream& output_file);
    void load_details(std::ifstream& input_file);
};

#endif // TILEBAG