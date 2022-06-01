#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include "Tile.h"
#include "Extras.h"
#include "Dictionary.h"


class Board {
public:
   Board();
   
   ~Board();
   
   void print();
   
   bool check_empty(int row, int col);
   
   void place(Tile* tile, int row, int col);

   Tile* get(int row,int col);
   
   void save_details(std::ofstream& output_file);
   
   void load_details(std::ifstream& input_file);
   
   Letter get_row_char(int row);
   
   int get_row_int(Letter letter);
   
   void set_player1(std::string player1);
   
   void set_player2(std::string player2);
   
   void set_dictionary(Dictionary* dictionary);
   
   bool word_checker(std::vector<std::tuple<Tile*,int,int>> &pile);

   std::string reverse(std::string str);
 
   
private:
   
   std::vector<std::vector<Tile*>> board;
   
   Dictionary* dictionary;
   
   std::string player1;
   
   std::string player2;
};
#endif // ASSIGN2_BOARD_H