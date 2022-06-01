#include <iomanip>
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
// function to save scores to high scores file
void save_scores(std::string p1_name, std::string p2_name,int p1_score,int p2_score);
// bool operator function that compares two tuples by their second elements
bool sortbysec(const std::tuple<std::string, int>& a, const std::tuple<std::string, int>& b);
// function to print high scores of all players
void high_scores();

int main(void) {
   
   menu();
   int option = 0;
   std::cin >> option;

   while(!std::cin.eof() && option != 5){
      if(option == 1){
         new_game();
      } else if(option == 2){
         load();
      } else if(option == 3){
         credits();
      }else if(option == 4){
         high_scores();
      } else {}
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
   std::cout << "4. High Scores" <<std::endl;
   std::cout << "5. Quit" << std::endl;
   std::cout << "> ";
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
   // declares Board
   Board* board = new Board();
   // initialises TileBag
   TileBag* tileBag = new TileBag("configs/ScrabbleTiles");
   Dictionary* dicationary = new Dictionary("configs/wordlist");
   board->set_dictionary(dicationary);
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

   // flush buffer
   std::cin.ignore(INT_MAX, '\n');
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

   std::ifstream input_file;
   std::ofstream output_file;
   
   // Creates vector of all saved game file names
   std::string file_name = p1->get_filename();
   input_file.open("saved_games/game_files.txt");
   std::string game;
   int counter = 1;
   std::vector<std::string>games;
   while(getline(input_file,game)){
      games.push_back(game);
      counter++;
   }
   input_file.close();

   std::string response;
   bool name_change = false;
   // Checks if filename is already in use
   while (std::find(games.begin(), games.end(), file_name) != games.end() && !name_change)
   {
      std::string response;
      std::cout <<"Game File Already Exists!\nWould you like to overwrite it? (y/n):" <<std::endl;
      std::cin >> response;
      if (response == "n" || response  == "N" || response  == "No" || response  == "no"){
         std::cout << "Enter Game Save Name:"<<std::endl;;
         std::cin >> file_name;
      }
      else if(response == "y" || response  == "yes" || response  == "Yes" || response  == "Y"){
         name_change = true;
      }
 
   }
   // If the file_name isnt already used than add the file_name to games_file.txt
   if (std::find(games.begin(), games.end(), file_name) == games.end()){
      output_file.open("saved_games/game_files.txt",std::ofstream::app);
      output_file << '\n' << file_name;
      output_file.close();
   }
   // Saves details of game to the file
   output_file.open("saved_games/"+ file_name + ".txt");
   
   save_scores(p1->get_player_name(),p2->get_player_name(),p1->get_score(),p2->get_score());
   p1->save_details(output_file);
   p2->save_details(output_file);
   board->save_details(output_file);
   bag->save_details(output_file);

   output_file.close();
   std::cout<<"Game Saved!" <<std::endl;
   
   // Deallocates memory
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
   Dictionary* dicationary = new Dictionary("configs/wordlist");
   
   // Displays all saved games avaiable
   std::ifstream input_file;
   std::string player;
   std::cout << "\nSaved Games:" << std::endl;
   std::cout <<"------------"<< std::endl;
   input_file.open("saved_games/game_files.txt");
   std::string game;
   int counter = 1;
   
   while(getline(input_file,game)){
      std::cout << counter << "." << game <<std::endl;
      counter++;
   }
   input_file.close();

   // get name of saved game file
   std::string fileName;
   std::cout<<"\nEnter Game Name:" <<std::endl;
   std::cin.ignore();
   
   getline(std::cin,fileName);
   // checks game exists
   while (checkFile("saved_games/" + fileName + ".txt") == false) {
      std::cout << "Game Doesn't Exist" << std::endl;
      std::cout<<"Enter Game Name:" << std::endl;
      getline(std::cin,fileName);
   }
   input_file.open("saved_games/" + fileName + ".txt");
   // Loads all the details of saved game and starts the game
   p1->load_details(input_file);
   p2->load_details(input_file);
   board->load_details(input_file);
   p1->set_board(board);
   p2->set_board(board);
   board->set_player1(p1->get_player_name());
   board->set_player2(p2->get_player_name());
   board->set_dictionary(dicationary);
   bag->load_details(input_file);
   p1->set_bag(bag);
   p2->set_bag(bag);
   input_file.close();
   player_turn(p1,p2,bag,board);
}

void high_scores(){
   std::ifstream input_file;
   std::string player;
   std::cout << "HIGH SCORES:" << std::endl;
   input_file.open("high_scores.txt");
   int score;
   std::cout << "Player : Score" <<std::endl;
   std::cout <<"-----------------"<< std::endl;
   int counter = 0;

   while(!input_file.eof()){
      counter++;
      input_file >> player;
      input_file >> score;
      if (counter == 1 && player != ""){
          std::cout << GRN << player<<" : " << score << " (1st)" <<  NC  << std::endl;
      }
      else if (counter == 2){
          std::cout << RED <<player <<" : " << score << " (2nd)" <<NC << std::endl;
      }
      else if (counter == 3){
          std::cout << YEL << player<<" : " << score<<" (3rd)" << NC << std::endl;
      }
      else if (counter > 3){
          std::cout <<player<<" : " << score<< std::endl;
      }
   }

   input_file.close();

}
void save_scores(std::string p1_name, std::string p2_name,int p1_score,int p2_score){
   std::ifstream input_file;
   std::string player;
   input_file.open("configs/high_scores.txt");
   int score;
   bool p1Found = false;
   bool p2Found = false; 
   
   std::vector<std::tuple<std::string,int>> all_scores;

   while(input_file.good()){
      input_file >> player;
      input_file >> score;
      if (player == p1_name){
         p1Found = true;
         if (score < p1_score){
            score = p1_score;
         }
      }
      else if (player == p2_name){
         p2Found = true;
         if (score < p2_score){
            score = p2_score;
         }
      }
      if (player != ""){
         all_scores.push_back(std::make_tuple(player,score));
      }
   }
   if (!p1Found){
      all_scores.push_back(std::make_tuple(p1_name,p1_score));
   }
   if (!p2Found){
       all_scores.push_back(std::make_tuple(p2_name,p2_score));
   }
   sort(all_scores.begin(), all_scores.end(), sortbysec);

   std::ofstream output_file("configs/high_scores.txt");
   for (int i = 0; i < all_scores.size();i++){
      output_file << std::get<0>(all_scores[i]) << " "<< std::get<1>(all_scores[i]);
      if (i < all_scores.size() - 1){
         output_file << std::endl;
      }
   }
   output_file.close();
}
bool sortbysec(const std::tuple<std::string, int>& a, 
               const std::tuple<std::string, int>& b)
{
    return (std::get<1>(a) > std::get<1>(b));
}