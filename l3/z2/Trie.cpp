#include "Trie.h"
#include <iostream>
#include<string>
using namespace std;

void Trie::insert(std::string key){
    Trie* curr = this;

    for(int i=0;i<key.size();i++){
        if(key[i] >= 65 && key[i] <= 90)
            key[i] += 32;
    }

    for (int i = 0; i < key.length(); i++)
    {
        if (curr->character[key[i]] == nullptr)
            curr->character[key[i]] = new Trie();

        curr = curr->character[key[i]];
    }
    curr->isLeaf = true;
}

bool Trie::search(std::string key){

    int i;

    for(i=0;i<key.size();i++){
        if(key[i] >= 65 && key[i] <= 90)
            key[i] += 32;
    }

    if (this == nullptr)
        return false;

    Trie* curr = this;
    for (i = 0; i < key.length(); i++){
        curr = curr->character[key[i]];

        if (curr == nullptr)
            return false;
    }
    return curr->isLeaf;
}