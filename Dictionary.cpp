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
        for (auto & c: word) c = toupper(c);
        //std::transform(word.begin(), word.end(), word.begin(), toupper);
        dictionary.insert(word);
        length++;
    }
    input_file.close();

}
int Dictionary::size(){
    return length;
}

bool Dictionary::search(std::string word){
    bool result;
    if(dictionary.count(word)) {
        result = true;
    } else {
        result = false;
    }
    return result;
}