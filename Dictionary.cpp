#include "Dictionary.h"

Dictionary::Dictionary(){
    
}
Dictionary::Dictionary(std::string filename){
    length = 0;
    fill(filename);
}
Dictionary::~Dictionary(){}

void Dictionary::fill(std::string filename){
    // Loads all the words saved in file into set
    std::ifstream input_file;
    input_file.open(filename + ".txt");
    std::string word;
    while (std::getline(input_file, word))
    {
        for (auto & c: word) c = toupper(c);
        dictionary.insert(word);
        length++;
    }
    input_file.close();

}
int Dictionary::size(){
    // returns length of dictionary
    return length;
}

bool Dictionary::search(std::string word){
    // Checks to see if word in parameter is in the set dictionary
    bool result;
    if(dictionary.count(word)) {
        result = true;
    } else {
        result = false;
    }
    return result;
}