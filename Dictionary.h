#ifndef ASSIGN2_DICTIONARY_H
#define ASSIGN2_DICTIONARY_H
#include <iostream>
#include <vector>
#include <fstream>
#include <set>
class Dictionary {
    public:
        Dictionary();
        Dictionary(std::string filename);
        ~Dictionary();
        // Fill dictionary will words from file
        void fill(std::string filename);
        // Get size of dictionary
        int size();
        // Search for word in dictionary
        bool search(std::string);
        
    private:
        std::set<std::string> dictionary;
        int length;
};
#endif // ASSIGN2_DICTIONARY_H