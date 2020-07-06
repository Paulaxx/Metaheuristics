#include <iostream>
#include<string>
#include<ctime>
#include <random>
#include<algorithm>
#include <iterator>
#include <map>
#include <fstream>
#include "Trie.h"

using namespace std;

int n;
map<char, int>letters;
Trie* head;
vector<char> letters2;

int goal(string word){

    int i, sum=0, find;
    map<char,int>::iterator it;

    for(i=0;i<word.size();i++){
        sum += letters.find(word[i])->second;
    }
    find = head->search(word);
    if(find != 1)
        return -1; //nie ma takiego slowa

    return sum;
}

int goal2(string word){

    int i, sum=0, find;
    map<char,int>::iterator it;

    for(i=0;i<word.size();i++){
        sum += letters.find(word[i])->second;
    }

    return sum;
}

bool possible(string child){

    int i;
    vector<char>word1;
    vector<char>::iterator it;

    word1 = letters2;

    for(i=0;i<child.size();i++){
        it = find(word1.begin(), word1.end(), child[i]);
        if(it != word1.end())
            word1.erase(it);
        else
            return false;
    }

    return true;
}

vector<string> cross(string parent1, string parent2){

    int i, size1, size2, pivot1, pivot2, x=0;
    string temp, temp2, child1, child2;
    vector<char>word1, word2;
    vector<string>childs;
    word1 = word2 = letters2;
    vector<char>::iterator it;


    for(i=0;i<parent1.size();i++){
        it = find(word1.begin(), word1.end(), parent1[i]);
        if(it != word1.end())
            word1.erase(it);
    }
    for(i=0;i<parent2.size();i++){
        it = find(word2.begin(), word2.end(), parent2[i]);
        if(it != word2.end())
            word2.erase(it);
    }

    size1 = parent1.size();
    size2 = parent2.size();

    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, size1-1);
    std::random_device rd2;
    std::uniform_int_distribution<int> dist2(0, size2-1);

    pivot1 = dist(rd);
    pivot2 = dist2(rd2);

    temp = parent1.substr(pivot1, parent1.size());
    temp2 = parent2.substr(pivot2, parent2.size());

    child1 = temp + temp2;
    child2 = temp2 + temp;
    if(possible(child1))
        childs.push_back(child1);
    if(possible(child2))
        childs.push_back(child2);

    return childs;
}

void mutate(string &parent){

    int p, s, p2, i;
    char letter;
    vector<char>word;
    word = letters2;
    vector<char>::iterator it;

    for(i=0;i<parent.size();i++){
        it = find(word.begin(), word.end(), parent[i]);
        if(it != word.end())
            word.erase(it);
    }

    if(word.size() != 0){
        std::random_device rd;
        std::uniform_int_distribution<int> dist(0, word.size()-1);
        std::uniform_int_distribution<int> dist2(0, parent.size()-1);
        int position;
        position = dist2(rd);

        p = dist(rd); //random letter
        letter = word[p];
        parent[position] = letter; //podmiana literki

        it = find(word.begin(), word.end(), word[p]);
        word.erase(it);

        if(word.size() != 0){
            std::uniform_int_distribution<int> dist3(0, word.size()-1);
            p = dist3(rd);
            parent += word[p];
        }
    }
}

void generate_new_population(vector<string> &population, int s){

    int i,j, p, p2, q;
    vector<string> to_cross;
    vector<string> from_cross;
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 4*s - 1);

        for(i=0;i<10*s;i++){
            p = dist(rd);
            to_cross.push_back(population[p]);
        }
        for(i=0;i<to_cross.size();i++){
            for(j=i+1;j<to_cross.size();j++){
                from_cross = cross(to_cross[i], to_cross[j]);
                for(q=0;q<from_cross.size();q++)
                    population.push_back(from_cross[q]);
            }
        }

        for(i=0;i<5*s;i++){
            p = dist(rd);
            mutate(to_cross[p]);
            population.push_back(to_cross[p]);
        }
}

void first_population(vector<string> &population, int s){

    int i, p;
    string x, parent;
    std::random_device rd;
    vector<char>word;
    vector<char>::iterator it;

    while(population.size() < 10*s){
        std::uniform_int_distribution<int> dist(0, population.size() - 1);
        p = dist(rd);
        parent = population[p];
        word = letters2;
        for(i=0;i<parent.size();i++){
            it = find(word.begin(), word.end(), parent[i]);
            if(it != word.end())
                word.erase(it);
        }
        std::uniform_int_distribution<int> dist2(0, word.size() - 1);
        p = dist2(rd);
        parent += word[p];
        population.push_back(parent);
    }
}

int main() {

    int time, i, j, s, points, l=0, X, counter=0, last_best;
    char letter;
    string word, x2, best;
    vector<string>words;
    vector<string>population;
    ifstream read;
    head = new Trie();

    cin>>time>>n>>s;
    for(i=0;i<n;i++){
        cin>>letter>>points;
        letters.insert(pair<char, int>(letter, points));
        l++;
        letters2.push_back(letter);
    }
    for(i=0;i<s;i++){
        cin>>word;
        words.push_back(word);
    }

    clock_t start = clock();
    read.open("dict.txt");
    if (!read.is_open()) {
        cout<<"unable to open file"<<endl;
    }
    else{
        while (read >> x2) {
            head->insert(x2);
        }
    }
    for(j=0;j<words.size();j++){
        population.push_back(words[j]);
    }
    first_population(population, s);

    struct greater{
        bool operator()( string x, string y){
            return goal(x) > goal(y);
        }
    };
    struct greater2{
        bool operator()( string x, string y){
            return goal2(x) > goal2(y);
        }
    };

    while((clock()-start)/CLOCKS_PER_SEC < time){
        generate_new_population(population, s);
        std::sort(population.begin(), population.end(), greater());
        for(i=0;i<population.size();i++){
            if(goal(population[i]) == -1){
                X = i;
                break;
            }
        }
        std::sort(population.begin(), population.begin()+X, greater());
        std::sort(population.begin()+X, population.end(), greater2());

        while(population.size() > 10*s){
            population.pop_back();
        }
        i = 0;
        best = population[i];
        while(head->search(best) != 1 && i<population.size()-1){
            i++;
            best = population[i];
        }

        if(goal(best) == last_best){
            counter++;
            if(counter == 100)
                break;
        } else
            counter = 0;

        last_best = goal(best);
    }
    cout<<goal(best)<<endl;
    cerr<<best<<endl;

    return 0;
}