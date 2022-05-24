#include "Extras.h"
#include "TileBag.h"
#include "Board.h"
#include "Dictionary.h"
#include "PlayerHand.h"

#define EXIT_SUCCESS    0


// function to print game menu
void menu();
// print game credits
void credits();
// function to load game from file
void load();
// function to start new game
void new_game();

// function called when game is over
void game_over(PlayerHand* p1,PlayerHand* p2);
// function to get players turn
void player_turn(PlayerHand* p1, PlayerHand* p2, TileBag* bag,Board* board);
// function to save game to file
void save(PlayerHand* p1, PlayerHand* p2,TileBag* bag, Board* board);

int main(void) {
   
   menu();
   int option = 0;
   std::cin >> option;

   while(!std::cin.eof() && option != 4){
      if(option == 1){
         new_game();
      } else if(option == 2){
         load();
      } else if(option == 3){
         credits();
      } else {

      }
      if (!std::cin.eof()){
         menu();
         std::cin >> option;
      }
   }
  
   std::cout << "Goodbye" << std::endl;
   

   return EXIT_SUCCESS;
}

void menu(){
   std::cout << "Menu" << std::endl;
   std::cout << "----" << std::endl;
   std::cout << "1. New game" << std::endl;
   std::cout << "2. Load game" << std::endl;
   std::cout << "3. Credits (Show student information)" << std::endl;
   std::cout << "4. Quit" << std::endl;
   std::cout << ">";
}

void credits(){
   std::cout << "------------------------" << std::endl;
   std::cout << "Name: Luke Macdonald" << std::endl;
   std::cout << "Student ID: s3888490" << std::endl;
   std::cout << "Email: s3888490@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;
 
}


bool checkFile(const std::string &str) {
   FILE *file;
   return (file = fopen(str.c_str(), "r")) ? fclose(file), true : false;
}

void new_game(){
   Tile* temp = new Tile();
   // declares Board
   Board* board = new Board();
   // initialises TileBag
   TileBag* tileBag = new TileBag("ScrabbleTiles");
   Dictionary* dicationary = new Dictionary("wordlist");
   // initialises board
   board->print();
   // gets first players name
   std::string playerOne, playerTwo;
   std::cout << "Enter Player One Name: ";
   std::cin >> playerOne;
   std::cout<<playerOne <<std::endl;
   // gets second player name
   std::cout << "Enter Player Two Name: ";
   std::cin >> playerTwo;
   std::cout<<playerTwo << std::endl;
  
   // declares and initialises the two players
   PlayerHand* player1 = new PlayerHand(playerOne,tileBag,board);
   board->set_player1(player1->get_player_name());
   PlayerHand* player2 = new PlayerHand(playerTwo,tileBag,board);
   board->set_player2(player2->get_player_name());
   
   player1->set_dictionary(dicationary);
   player2->set_dictionary(dicationary);
  
   // flush buffer
   std::cin.ignore(INT_MAX, '\n');
   // deallocate temporay tile
   delete temp;
   // calls function to start players turn
   player_turn(player1,player2,tileBag,board);
}
void player_turn(PlayerHand* player1, PlayerHand* player2, TileBag* bag,Board* board){ 
   // Print details of game (player's name, scores, current players hand and board)
   std::cout<<player1->get_player_name()<< ", it's your turn"<<std::endl;
   std::cout<<"Score for "<<player1->get_player_name() << ": "<< player1->get_score()<<std::endl;
   std::cout<<"Score for "<<player2->get_player_name() << ": "<< player2->get_score()<<std::endl;
   board->print();
   std::cout<<"Your Hand is"<<std::endl;
   player1->print_hand();
   player1->player_turn();
   // Checks if player has no more tiles left and tilebag is empty
   if (player1->get_hand_size() == 0 && bag->size() == 0){
         // dellocate memory
         delete bag;
         delete board;
         // call game over function
         game_over(player1,player2);
      }
   // Checks if current player wants to quit game
   else if(player1->quit_game()){
      delete bag;
      delete board;
      delete player1;
      delete player2;
   }
   // Checks if current player wants to save game
   else if (player1->save_game()){
      // calls function to save current game state to file 
      save(player1,player2,bag,board);
   }
   else{
      // function recurseively calls between player turns
      player_turn(player2,player1,bag,board);
   }
}
void game_over(PlayerHand* player1,PlayerHand* player2){
   // print out details of game
   int score1 = player1->get_score();
   int score2=  player2->get_score();
   std::cout << "Game Over!"<<std::endl;
   std::cout<< "Score for " <<player1->get_player_name() << ": " << score1 <<std::endl;;
   std::cout<< "Score for " <<player2->get_player_name() << ": " << score2 <<std::endl;;
   if (score1 > score2){
      std::cout << "Player " << player1->get_player_name() << " won!"<< std::endl;
   }
   else if (score2 > score1){
      std::cout << "Player " << player2->get_player_name() << " won!"<< std::endl;
   }
   else{
      std::cout << "Its a draw!"<<std::endl;
   }
   // deallocate memory
   delete player1;
   delete player2;
}
void save(PlayerHand* p1, PlayerHand* p2, TileBag* bag, Board* board){
   
   std::string file_name = p1->get_filename();
   std::ofstream output_file(file_name + ".txt");
   
   p1->save_details(output_file);
   p2->save_details(output_file);
   board->save_details(output_file);
   bag->save_details(output_file);
   
   
   delete p1;
   delete p2;
   delete bag;
   delete board;
}
void load(){

   PlayerHand* p1 = new PlayerHand();
   PlayerHand* p2 = new PlayerHand();
   Board* board = new Board();
   TileBag* bag = new TileBag();

   // get name of saved game file
   std::string fileName;
   std::cout<<"Enter Game Name:" <<std::endl;
   std::cin.ignore();
   
   getline(std::cin,fileName);
   // checks game exists
   while (checkFile(fileName + ".txt") == false) {
      std::cout << "Game Doesn't Exist" << std::endl;
      std::cout<<"Enter Game Name:" << std::endl;
      getline(std::cin,fileName);
   }

   std::ifstream input_file;
   input_file.open(fileName + ".txt");

   p1->load_details(input_file);
   p2->load_details(input_file);
   board->load_details(input_file);
   p1->set_board(board);
   p2->set_board(board);
   board->set_player1(p1->get_player_name());
   board->set_player2(p2->get_player_name());
   bag->load_details(input_file);
   p1->set_bag(bag);
   p2->set_bag(bag);
   for (int i = 0; i < bag->size();i++){
      std::cout<< bag->get(i)->letter;
   }
   player_turn(p1,p2,bag,board);
}