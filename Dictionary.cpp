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
    bool result = find(word,0,size());  
    return result;
}
bool Dictionary::find(std::string word,int start,int end)
{
    if (end >= start){
        int mid = (start + (end - start)) / 2;
        if (word == dictionary.at(mid)){
            return true;
        }  
        else if (word > dictionary.at(mid)){
            find(word,mid + 1,end);
        }
        else if (word < dictionary.at(mid)){
            find(word,start,mid - 1);
        }
    }
    return false;
}