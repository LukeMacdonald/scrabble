#ifndef ASSIGN2_DICTIONARY_H
#define ASSIGN2_DICTIONARY_H
#include <iostream>
#include <vector>
#include <fstream>
class Dictionary {
    public:
        Dictionary();
        Dictionary(std::string filename);
        ~Dictionary();
        
        void fill(std::string filename);
        int size();
        
        bool search(std::string);
        bool find(std::string,int start,int end);
    
    private:
        std::vector<std::string> dictionary;
        int length;
};
#endif // ASSIGN2_DICTIONARY_H