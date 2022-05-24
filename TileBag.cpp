#include "TileBag.h"
#include <vector>
#include <random>
#include <time.h>

TileBag::TileBag() {

    tiles = new LinkedList();

}


TileBag::TileBag(std::string fileName) {

    tiles = new LinkedList();
    populateList(fileName);

}

TileBag::TileBag(LinkedList* tiles):
    tiles(tiles)
    {}


TileBag::~TileBag() {

    tiles->clear();
    delete tiles;
}


void TileBag::populateList(std::string fileName) {

    std::ifstream file;
    file.open(fileName + ".txt");
    std::cout << "opened file" << std::endl;
    
    std::string line;
    std::vector<Tile*> tile_vector;


    while (getline(file, line)){

        std::stringstream tile(line);
        Letter letter;
        Value num;
    
        tile >> letter;
        tile >> num;
        tile_vector.push_back(new Tile(letter,num));

    }
    file.close();
    int counter = tile_vector.size();
    for (int i = 0; i < counter;i++){
        // randomly generates index value to select
        int min = 0;
        int max = tile_vector.size() - 1;
        //std::random_device engine;
        std::random_device engine;
        std::uniform_int_distribution<int> uniform_dist(min, max);
        int value = uniform_dist(engine);
        // adds tile pointer to linked list using randomly 
        // generated index
        tiles->addBack(tile_vector[value]);
        // Uses random index to erase tile from vector 
        // so it cant be selected again
        tile_vector.erase(tile_vector.begin() + value);
    }
}
Tile* TileBag::getTile() {
    Tile* tile = tiles->returnFront();
    return tile; 
}

void TileBag::returnTile(Tile* tile){
    tiles->addBack(tile);
}
int TileBag::size(){
    return tiles->size();
}

Tile* TileBag::get(int i) {
    return tiles->get(i)->tile;
}

void TileBag::save_details(std::ofstream& output_file){
 

    for(int i = 0; i < tiles->size();i++)
    {
        std::cout << tiles->get(i)->tile->letter << "-" << tiles->get(i)->tile->value;
        output_file << tiles->get(i)->tile->letter << "-" << tiles->get(i)->tile->value;
        if (i < tiles->size() - 1)
        {
            output_file << ", ";
        }
    }
    output_file << std::endl;
}

void TileBag::load_details(std::ifstream& input_file){
    
    std::string tile;
    getline(input_file, tile);
    std::istringstream ss(tile);
    std::string t;
    
    while (std::getline(ss, t, ','))
    {
        std::stringstream str(t);
        Letter letter;
        Value num;
        Letter split;
        str >> letter;
        str >> split;
        str >> num;
        tiles->addBack(new Tile(letter, num));
    }
    ss.clear();
}


