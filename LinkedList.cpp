#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() {
   head = nullptr;
   length = 0;
}
LinkedList::~LinkedList(){
    clear();
} 

int LinkedList::size()
{
    return length;
}
void LinkedList::clear(){
    while(head != nullptr){
        removeFront();
    }
    length = 0;
}
Node* LinkedList::get(int i){
    
    Node* node = nullptr;
    // checks that specified index i is within the 
    // size range of list
    if(i >= 0 && i < length){
        int counter = 0;
        Node* current = head;
        // iterate until counter equals index
        while(counter < i){
            ++counter;
            current = current->next;
        }
        node = current;
    }
    return node;
}

void LinkedList::addBack(Tile* data){  
    // if list is empty set new tile has head node 
    if(head == nullptr){
        head =  new Node(data,nullptr,nullptr);
        tail = head;
    }else{
        // adds new node containing tile to end of list
        tail->next = new Node(data,nullptr,tail);
        // sets tail to newly added node
        tail = tail->next;
    }
    length++;
}
void LinkedList::removeFront(){
    if(head != nullptr){
        // get first node in list
        Node* toDelete = head;
        // sets head node to the next node in list
        head = head->next;
        // deallocates tile
        delete toDelete->tile;
        // deallocates node
        delete toDelete;
    }
    length--;
}

Tile* LinkedList::returnFront(){
    if(head != nullptr){
        Node* node = head;
        head = head->next;
        length--;
        Tile* tile =node->tile;
        delete node;
        return tile;
    }else{
        return nullptr;
    }
}
Tile* LinkedList::replace(char letter,Tile* new_tile){
    Tile* replace = nullptr;
    // if head contains the tile with the letter
    // return the tile and set head to next node
    if(head->tile->letter == letter){
        replace = head->tile;
        head->tile = new_tile;
    }
    else{
        // Sets node to begin iterating over list
        Node* current = head;
        // Iterate over list until either letter is found or iterated over
        // all items in list
        while(current->tile->letter != letter && current->next != nullptr){
            current = current->next;
            // checks the node's tile contains the letter searching for
            if(current->tile->letter == letter){
                // gets tile from current node
                replace = current->tile;
                // sets current node tile to new tile 
                current->tile = new_tile;
            }
        }
    }
    // return tile
    return replace;   
    
}
Tile* LinkedList::find(char letter){   
    Tile* toReturn = nullptr;
    // if head contains the tile with the letter
    // return the tile and set head to next node
    if(head->tile->letter == letter){
        toReturn = head->tile;
        head = head->next;
    } 
    else{
        Node* current = head;
        // Iterate over list until either letter is found or iterated over
        // all items in list
        while(current->next != nullptr && current->tile->letter != letter){
            current = current->next;
        }
        // checks the node's tile contains the letter searching for
        if (current->tile->letter == letter)
        {
            // removes node from list
            current->prev->next = current->next;
            if (current->next != nullptr){
                current->next->prev = current->prev;
            }
            if (current == tail){
                tail = current->prev;
            }
            toReturn = current->tile;
        }
    }
    // decrements size of list
    length--;
    return toReturn;
}