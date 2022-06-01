#include "PlayerHand.h"
#include "Extras.h"
#include "TileBag.h"
#include <vector>
#include <algorithm>
#include <string>

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"

PlayerHand::PlayerHand(){
    hand = new LinkedList();
}
PlayerHand::PlayerHand(std::string player_name,TileBag* bag, Board* board)
{
    hand = new LinkedList();
    this->player_name = player_name;
    this->bag = bag;
    this->board = board;
    this->score = 0;
    fill_hand();
}
PlayerHand::PlayerHand(std::string player_name, TileBag* bag, Board* board, LinkedList* hand, int score):
    player_name(player_name),
    score(score),
    bag(bag),
    board(board),
    hand(hand)
    {}
PlayerHand::PlayerHand(PlayerHand& origin):
    player_name(origin.player_name),
    score(origin.score),
    bag(origin.bag), 
    board(origin.board),
    hand(origin.hand)
    {
        delete &origin;
    }
PlayerHand::~PlayerHand()
{
    delete hand;
} 
int PlayerHand::size()
{
    return hand->size();
}
void PlayerHand::fill_hand()
{
    // Adds tiles to hand until either hand is full or tileBag is empty
    while (hand->size() < 7 && bag->size() > 0)
    {
        hand->addBack(bag->getTile());
    }
   
}
void PlayerHand::player_turn()
{
   
    // Initialise vector to store user input
    std::vector<std::string> userInput(4);
  

    // Method call to get user input
    get_user_input(userInput); 
    // gets the action from vector
    std::string action = userInput[0];
    // place tile on board
    if (action == "place")
    {
        place(userInput); 
    }
    // skips players turn
    else if(action == "pass"){}
    // replace tile in players hand
    else if(action == "replace")
    {
        std::cout << userInput[0] << " " << userInput[1]<<std::endl;
        Letter letter = userInput[1][0];
        replace(letter);
    }
    // save game
    else if(action == "save")
    {
        std::cout << userInput[0] << " " << userInput[1]<<std::endl;
        save = true;
        filename = userInput[1];
    }
    else if (action == "help"){
    help(0);
    player_turn();
   
    }
    else if (action == "hand"){
        print_hand();
        player_turn();
    }
    // EOF key entered.
    else if (std::cin.eof()){
        quit = true;
    }
   
    // Incorrect user input
    else
    {
        std::cout<<"Incorrect Input" << std::endl;
        player_turn();
    }

}
void PlayerHand::place(std::vector<std::string> &user_input){

    std::vector<std::tuple<Tile*,int,int>> pile;
   
    int counter = 0; 
    // iterate until either player selects done or has placed entire hand
    while (user_input[1] != "done" && counter < 7 && hand->size() > 0)
    {
        // checks input is valid
        bool valid = std::find(valid_input.begin(), valid_input.end(), user_input[1]) != valid_input.end();
        // invalid input
        if (user_input[0] == "help"){
            help(1);
            get_user_input(user_input);
        }
        else if(user_input[0] == "hand"){
            print_hand();
            get_user_input(user_input);

        }
        if (user_input[0] != "place" || !valid){
            std::cout << user_input[0] << " " << user_input[1] << " " << user_input[2] << " " << user_input[3] <<std::endl;
            std::cout<<"Incorrect Input! Try Again!" << std::endl;
            get_user_input(user_input);
        
        }
    
        // valid input 
        if (valid && user_input[0] == "place" && user_input[1] != "done")
        {
            std::cout << user_input[0] << " " << user_input[1] << " " << user_input[2] << " " << user_input[3] <<std::endl;
            Letter letter = user_input[1][0];
            
            try{
                // gets row the user wants to place tile at
                
                int row = board->get_row_int(char(user_input[3].at(0)));
                // gets col the user wants to place tile at
                int col = stoi(user_input[3].substr(1,2));
                
                // throws error if row is entered incorrect
                if (row == -1){
                    throw -1;
                }
                // throws error if col is entered incorrect
                else if (col > 14 || col < 0){
                    throw - 1;
                }
                // throws error if tile already placed
                else if (!board->check_empty(row,col)){
                    throw board->get(row,col)->letter;
                }
                // EOF key was entered
                else if(std::cin.eof())
                {
                   quit = true;
                   return;
                }
                else{
                    // gets selected tile from hand
                    Tile* chosen_tile = hand->find(letter);
                    
                    // throws error if tile not in hand.
                    if (chosen_tile == nullptr){
                        throw chosen_tile;
                    }
                    
                    
                    pile.push_back(std::make_tuple(chosen_tile,row,col));
                    
                
                    
                    if (counter < 6){
                        get_user_input(user_input); 
                    }            
                    counter++;
                }    
          }catch(Tile* tile){
            std::cout<<"Tile not in Hand! Try Again!"<<std::endl;
            get_user_input(user_input); 
          }catch(char position){
            std::cout<< "Tile Already in that Position! Try Again!"<<std::endl;
         
            get_user_input(user_input); 
          }catch(...){
            std::cout<<"Incorrect Input! Try Again!" << std::endl;
            get_user_input(user_input);
          }
        }
    }
    if (user_input[1] == "done"){
        std::cout << user_input[0] << " " << user_input[1]<<std::endl;
    }
    if(board->word_checker(pile)){
        for (int i = 0; i < pile.size();i++){
            int row = std::get<1>(pile[i]);
            int col = std::get<2>(pile[i]);
            Tile* tile = std::get<0>(pile[i]);
            tile->player = player_name;
            place_tile(tile,row,col);
        }
    }
    else{
        std::cout << "Invalid Words" << std::endl;
         for (int i = 0; i < pile.size();i++){
            Tile* tile = std::get<0>(pile[i]);
            hand->addBack(tile);
        }
        get_user_input(user_input);
        place(user_input);
    }

    fill_hand();
    
    // BINGO OPERATION!!!
    if (counter == 7){
        score+=50;
        std::cout<< GRN << "BINGO!"<< NC <<std::endl;
    }
}
void PlayerHand::place_tile(Tile* chosen_tile, int row, int col)
{
    score += chosen_tile->value;
    chosen_tile->player = player_name;
    board->place(chosen_tile,row,col);
  
}
void PlayerHand::replace(Letter letter)
{
    // gets new tile from TileBage
    Tile* new_tile = bag->getTile();
    // adds the new tile to player hand and returns the tile
    // player wants to remove
    Tile* chosen_tile = hand->replace(letter,new_tile);
    if (chosen_tile != nullptr){
        // adds removed tile back into tileBag
        bag->returnTile(chosen_tile);
    }
    else{
        std::cout<<"Tile not in Hand!"<<std::endl;
        player_turn();
    }
}

void PlayerHand::help(int setting){
    std::cout<<"HELP:"<<std::endl;
    std::cout<<"Avaiable Commands:"<<std::endl;
    std::cout << "- Place Tile(s) on Board: place \"Tile\" at \"Grid Position\"" << std::endl;
    std::cout << "- Show Player hand: hand " <<std::endl;
    if (setting == 0){
        std::cout << "- Save Game: save \"name\"" << std::endl;
        std::cout << "- Skip Player Turn): pass" << std::endl;
        std::cout << "- Replace Tile in Hand: replace \"Tile\"" <<std::endl;
    }
    else if (setting == 1){
        std::cout << "- Finish Placing Tiles: place done " <<std::endl;
    }
}

void PlayerHand::print_hand()
{
    for(int i = 0; i < size();i++)
    {
        Tile* tile = hand->get(i)->tile;
        std::cout<<tile->letter <<"-"<<tile->value;
        if (i < size() - 1)
        {
            std::cout<<", ";
        }
    }
    std::cout<<std::endl;
}

// Getters and Setters
void PlayerHand::set_player_name(std::string name){
    this->player_name = name;
}
void PlayerHand::set_score(int score){
    this->score = score;
}
void PlayerHand::set_bag(TileBag* bag){
    this->bag = bag;
}
void PlayerHand::set_board(Board* board){
    this->board = board;
}

int PlayerHand::get_score() {
    return score;
}

int PlayerHand::get_hand_size(){
    return hand->size();
}
std::string PlayerHand::get_player_name()
{
    return player_name;
}

std::string PlayerHand::get_filename(){
    return filename;
}

void PlayerHand::get_user_input(std::vector<std::string> &commands)
{
    std::string command,token;
    
    std::cout<<"> ";
    
    // read input from console
    getline(std::cin, command);
    std::stringstream stream(command);
    int counter = 0;
    // splits entered input and stores each word in vector
    while (getline(stream, token, ' '))
    {
        commands[counter] = token;
        counter++;
    }
    
}

// Save and Load Functions
bool PlayerHand::save_game()
{
    return save;
}
bool PlayerHand::quit_game(){
    return quit;
}
void PlayerHand::save_details(std::ofstream& output_file){
    output_file << player_name << std::endl;

    for(int i = 0; i < hand->size();i++)
    {
        output_file << hand->get(i)->tile->letter << "-" << hand->get(i)->tile->value;
        if (i < hand->size() - 1)
        {
            output_file << ", ";
        }
    }
    output_file << std::endl;
    output_file << score << std::endl;
}
void PlayerHand::load_details(std::ifstream& input_file){
    getline(input_file, player_name);
    std::string tiles;
    getline(input_file, tiles);
    std::istringstream ss(tiles);
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
        hand->addBack(new Tile(letter, num));
    }
    ss.clear();
    std::string s;
    getline(input_file, s);
    score = stoi(s);
}
