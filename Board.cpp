#include "Board.h"
#include "BoardC.h"
Board::Board(){
   
   player1 = "";
   player2 = "";
   
   Tile* temp = new Tile();
   
   board = std::vector<std::vector<Tile*> >(BOARD_WIDTH, std::vector<Tile*>(BOARD_HEIGHT, temp));
   
   for(int i = 0; i < BOARD_HEIGHT; i++){
      for(int j = 0; j < BOARD_WIDTH; j++){
         board[i][j] = new Tile();
      }
   }
   delete temp;
}
Board::~Board(){

   for(int i = 0; i < BOARD_HEIGHT; i++){
      for(int j = 0; j < BOARD_WIDTH; j++){
         delete board[i][j];
      }
   }
   delete dictionary;
}
void Board::print(){
   int row = int('A');
   std::cout<< "  ";
   for (int i = 0; i <  BOARD_WIDTH;i++){
      if (i < 10)
      {
         std::cout<< "  "<< i<< " ";
      }
      else
      {
        std::cout<< "  "<< i;
      }
   }
   std::cout<<std::endl;
   std::cout<< "  ";
   for (int i = 0; i < 15;i++){
      std::cout<<"----";
   }
   std::cout<<"-"<<std::endl;
   for(int i = 0; i < BOARD_HEIGHT; i++){
      std::cout << char(row + i) << " | ";
      for(int j = 0; j < BOARD_WIDTH; j++){
         if (board[i][j]->player == player1){ 
            std::string s(1, board[i][j]->letter);
            color("green",s,false);
            std::cout << " | ";
          }
         else if (board[i][j]->player == player2){
            std::string s(1, board[i][j]->letter);
            color("red",s,false);
            std::cout << " | ";
         }
         else{
            std::cout <<  board[i][j]->letter << " | ";
         }

   
      }
      std::cout<<std::endl;
   }
   std::cout<< "  ";
   for (int i = 0; i < 15;i++){
      std::cout<<"----";
   }
   std::cout<<"-"<<std::endl;
}
bool Board::check_empty(int row,int col){
   bool isEmpty;
   if (board[row][col]->letter == ' '){
      isEmpty = true;
   }
   else{
      isEmpty = false;
   }
   return isEmpty;
}

void Board::place(Tile*tile, int row,int col){
   board[row][col] = tile;
}


bool Board::word_checker(std::vector<std::tuple<Tile*,int,int>> &pile){
   std::string word;
   // Sets the desired tiles temporarily
   for (int i = 0; i < pile.size();i++){
      int row = std::get<1>(pile.at(i));
      int col = std::get<2>(pile.at(i));
      Letter letter = std::get<0>(pile.at(i))->letter;
      board[row][col]->letter = letter;
   }
   // Iterates over all rows checking if all words are valid
   for (int i = 0; i < BOARD_HEIGHT;i++){
      word = "";
      for (int j = 0; j < BOARD_WIDTH;j++){
         // Checks tile position is empty
         if (check_empty(i,j)){
            // If empty and word and is not blank then check to see if word is in
            // dictionary
            if (word != ""){
               // function to reverse string as the reverse string is also valid as
               // a word
               std::string r = reverse(word);
               // Checks if the word and reverse of the word are valid
               if (!dictionary->search(word) && !dictionary->search(r)){
                  for (int i = 0; i < pile.size();i++){
                     int row = std::get<1>(pile.at(i));
                     int col = std::get<2>(pile.at(i));
                     board[row][col]->letter = ' ';
                  }
                  return false;
               }
               // Sets word back to blank after the empty tile was encounterd
               word = "";
            }
         }
         else{
            // If tile wasnt empty add letter of tile to word
            word += board[i][j]->letter;
         }
      }
   }
   // Repeat previous steps but for each column.
   for (int j = 0; j < BOARD_WIDTH;j++){
      word = "";
      for (int i = 0; i < BOARD_HEIGHT;i++){
         if (check_empty(i,j)){
            if (word != ""){
               std::string r = reverse(word);
               if (!dictionary->search(word) && !dictionary->search(r)){
                  for (int i = 0; i < pile.size();i++){
                     int row = std::get<1>(pile.at(i));
                     int col = std::get<2>(pile.at(i));
                     board[row][col]->letter = ' ';
                  }
                  return false;
               }
               word = "";
            }
         }
         else{
            word += board[i][j]->letter;
         }
      }
   }
   return true;
}


Tile* Board::get(int row,int col){
   return board[row][col];
}

void Board::save_details(std::ofstream& output_file){
   for(int i = 0; i < BOARD_HEIGHT; i++){
      for(int j = 0; j < BOARD_WIDTH; j++){
         if (board[i][j]->letter != ' '){
            // Stores the tiles placed on board to file.
            output_file << board[i][j]->letter << '@' <<get_row_char(i) << j << " ";
         }
      }
   }
   output_file << std::endl;
}

void Board::load_details(std::ifstream& input_file){
   std::string t;
   getline(input_file, t);
   std::istringstream ss(t);
   
   while (std::getline(ss, t, ' '))
   {
      Letter letter = t[0];
      Letter row = t[2];
      std::string col = t.substr(3,4);
      board[get_row_int(row)][stoi(col)] = new Tile(letter, 0);
   }
   ss.clear();
}

void Board::set_player1(std::string player1){
    this->player1 = player1;
}
void Board::set_player2(std::string player2){
    this->player2 = player2;
}
void Board::set_dictionary(Dictionary* dictionary){
    this->dictionary = dictionary;
}
Dictionary* Board::get_dictionary(){
   return dictionary;
}

Letter Board::get_row_char(int row){

    // Turns the entered char value representing a row
    // into and integer which
    Letter letter;
    if (row ==A){letter = 'A';}
    else if(row == B){letter = 'B';}
    else if(row == C){letter = 'C';}
    else if(row == D){letter = 'D';}
    else if(row == E){letter = 'E';}
    else if(row == F){letter = 'F';}
    else if(row == G){letter = 'G';}
    else if(row == H){letter = 'H';}
    else if(row == I){letter = 'I';}
    else if(row == J){letter = 'J';}
    else if(row == K){letter = 'K';}
    else if(row == L){letter = 'L';}
    else if(row == M){letter = 'M';}
    else if(row == N){letter = 'N';}
    else if(row == O){letter = 'O';}
    else{letter = ' ';}
    return letter;

}
int Board::get_row_int(Letter letter)
{
    int row = 0;
    if (letter == 'A'){row = A;}
    else if(letter =='B'){row = B;}
    else if(letter == 'C'){row = C;}
    else if(letter == 'D'){row = D;}
    else if(letter == 'E'){row = E;}
    else if(letter == 'F'){row = F;}
    else if(letter == 'G'){row = G;}
    else if(letter == 'H'){row = H;}
    else if(letter == 'I'){row = I;}
    else if(letter == 'J'){row = J;}
    else if(letter == 'K'){row = K;}
    else if(letter == 'L'){row = L;}
    else if(letter == 'M'){row = M;}
    else if(letter == 'N'){row = N;}
    else if(letter == 'O'){row = O;}
    else{row = -1;}
    return row;
}
std::string Board::reverse(std::string str)
{
   std::string reverse = "";
   for (int i = str.length() - 1; i >= 0; i--){
      reverse +=  str[i];
   }
   return reverse;
}