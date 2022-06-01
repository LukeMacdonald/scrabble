#include "Dictionary.h"

Dictionary::Dictionary(){
    
}
Dictionary::Dictionary(std::string filename){
    length = 0;
    fill(filename);
}
Dictionary::~Dictionary(){}

void Dictionary::fill(std::string filename){
    
    std::ifstream input_file;
    input_file.open(filename + ".txt");
    std::string word;
    while (std::getline(input_file, word))
    {
        std::transform(word.begin(), word.end(), word.begin(), toupper);
        dictionary.push_back(word);
        length++;
    }
    input_file.close();

}
int Dictionary::size(){
    return length;
}

bool Dictionary::search(std::string word){
    bool result;
    if(std::find(dictionary.begin(), dictionary.end(), word) != dictionary.end()) {
        result = true;
    
    } else {
        result = false;
    }
    return result;
}