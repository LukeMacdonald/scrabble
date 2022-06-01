#ifndef ASSIGN2_PLAYERHAND_H
#define ASSIGN2_PLAYERHAND_H

#include "Extras.h"
#include "TileBag.h"
#include "Board.h"
#include "Dictionary.h"

class PlayerHand {
public:
   PlayerHand();
   PlayerHand(std::string player_name, TileBag* bag,Board* board);
   PlayerHand(std::string, TileBag*, Board*, LinkedList*, int);
   PlayerHand(PlayerHand&);
   ~PlayerHand();
  
   int size();

   void player_turn();
 
   // Functions for Actions
   void place(std::vector<std::string> &commands);
   void place_tile(Tile* chosen_tile, int row, int col);
   void replace(Letter);
   void pass();
   void help(int setting);

   // Fill Players Hand
   void fill_hand();
   void print_hand();
 
   void get_user_input(std::vector<std::string> &commands);
   void set_player_name(std::string name);
   void set_score(int score);
   void set_bag(TileBag* bag);
   void set_board(Board* board);
   int get_score();
   int get_hand_size();
   std::string get_filename();
   std::string get_player_name();
  
   bool save_game();
   bool quit_game();;
   void save_details(std::ofstream& output_file);
   void load_details(std::ifstream& input_file);

private:
   std::string player_name;
   std::string filename = "";
   int score;
   TileBag* bag;
   Board* board;
   LinkedList* hand;

   bool save = false;
   bool quit = false;
 
   std::array<std::string,27> valid_input = {"A","B","C","D","E","F","G","H","I","J","K","L",
                                            "M","N","O","P","Q","R","S","T","U","V","W","X",
                                            "Y","Z","done"};

};
#endif // ASSIGN2_PLAYERHAND_H