#ifndef META3_TRIE_H
#define META3_TRIE_H
#include <iostream>
#include<string>
#include <bits/basic_string.h>

using namespace std;

#define CHAR_SIZE 128

class Trie
{
public:
    bool isLeaf;
    Trie* character[CHAR_SIZE];

    Trie()
    {
        this->isLeaf = false;

        for (int i = 0; i < CHAR_SIZE; i++)
            this->character[i] = nullptr;
    }

    void insert(string);
    bool search(string);
};

#endif //META3_TRIE_H
