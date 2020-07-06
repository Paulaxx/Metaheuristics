#include <iostream>
#include<string>
#include<ctime>
#include <random>
#include<algorithm>

using namespace std;

int n, m, agentX, agentY;
int **T;

int reach(string road, int **grid, int n, int m, int actualX, int actualY){
    int i;
    for(i=0;i<road.size();i++){
        switch(road[i]){
            case 'U':
                actualX--;
                break;
            case 'D':
                actualX++;
                break;
            case 'R':
                actualY++;
                break;
            case 'L':
                actualY--;
                break;
        }
        if(grid[actualX][actualY] == 1)
            return -1;  //wchodzi w sciane
        else if(grid[actualX][actualY] == 8)
            return i+1; //osiagnal cel po i krokach
    }
    return 0; //nie doszedl
}

string random_string(int l){

    string road;
    int p;
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 3);
    while(road.size() < l){
        p = dist(rd);
        switch(p){
            case 0:
                road += 'U';
                break;
            case 1:
                road += 'D';
                break;
            case 2:
                road += 'R';
                break;
            case 3:
                road += 'L';
                break;
        }
    }
    return road;
}

vector<string> crossover(string p1, string p2){

    int pos1, pos2;
    string temp, temp2, child, child2;
    vector<string>childs;
    std::random_device rd;
    std::uniform_int_distribution<int> dist2(0, p1.size() - 1);
    std::uniform_int_distribution<int> dist3(0, p2.size() - 1);
    pos1 = dist2(rd);
    pos2 = dist3(rd);

    temp = p1.substr(pos1, p1.size());
    temp2 = p2.substr(pos2, p2.size());
    child = temp + temp2;
    child2 = temp2 + temp;
    childs.push_back(child);
    childs.push_back(child2);
    return childs;

}

string mutate(string p1){

    int pos1, pos2, t, length, i;
    string temp, child;
    std::random_device rd;
    std::uniform_int_distribution<int> dist2(0, p1.size() - 1);
    pos1 = dist2(rd);
    pos2 = dist2(rd);
    if(pos1 > pos2){
        t = pos1;
        pos1 = pos2;
        pos2 = t;
    }
    length = pos2 - pos1;
    if(pos1 != 0)
        length ++;
    temp = random_string(length);
    p1.replace(pos1, pos2, temp);
    child = p1;

    for(i=0;i<child.size()-1;i++){
        if((child[i] == 'R' && child[i+1] == 'L') ||  (child[i] == 'L' && child[i+1] == 'R') ||
        (child[i] == 'D' && child[i+1] == 'U') || (child[i] == 'U' && child[i+1] == 'D')){
            if(i == 0)
                child.erase(0, i+2);
            else
                child.erase(i, i+1);
            if(child.size() == 0)
                break;
        }
    }
    return child;

}

void generate_population(vector<string> &population, int p){

    int i, m, j;
    string Mutate;
    vector<string> to_cross;
    vector<string> cross;
    std::random_device rd;
    std::uniform_int_distribution<int> dist2(0, p-1);
    for(i=0;i<p;i++){
        m = dist2(rd);
        to_cross.push_back(population[m]);
    }
    for(i=0;i<p;i++){
        for(j=i+1;j<p;j++){
            cross = crossover(to_cross[i], to_cross[j]);
            population.push_back(cross[0]);
            population.push_back(cross[1]);
        }
    }

    for(i=0;i<p/2;i++){
        m = dist2(rd);
        Mutate = mutate(to_cross[m]);
        population.push_back(Mutate);
    }
}

int main() {

    int time, s, p, i, j, X, counter=0;
    string e, best, last_best;
    vector<string>roads; //population

    cin>>time>>n>>m>>s>>p;

    T = new int *[n];
    for (i=0;i<n;i++)
        T[i] = new int [m];
    for(i=0;i<n;i++){
        cin>>e;
        for(j=0;j<m;j++){
            T[i][j] = e[j]-48;
        }
    }

    for(i=0;i<s;i++){
        cin>>e;
        roads.push_back(e);
    }
    best = roads[0];

    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            if(T[i][j] == 5){
                agentX = i; //starting position
                agentY = j;
            }
        }
    }

    i=0;
    while(roads.size() < p){
        roads.push_back(roads[i%p]);
        i++;
    }

    struct greater{
        bool operator()( string x, string y){
            return reach(x, T, n, m, agentX, agentY) > reach(y, T, n, m, agentX, agentY);
        }
    };
    struct greater2{
        bool operator()( string x, string y){
            return reach(x, T, n, m, agentX, agentY) < reach(y, T, n, m, agentX, agentY);
        }
    };


    clock_t start = clock();
    while((clock()-start)/CLOCKS_PER_SEC < time){

        generate_population(roads, p);
        std::sort(roads.begin(), roads.end(), greater());
        for(i=0;i<roads.size();i++){
            int x = reach(roads[i], T, n, m, agentX, agentY);
            if(x > 0 && x != roads[i].size()){
                roads[i].erase(x, roads[i].size());
            }
        }

        for(i=0;i<roads.size();i++)
            if(reach(roads[i], T, n, m, agentX, agentY) == 0 || reach(roads[i], T, n, m, agentX, agentY) == -1){
                X = i;
                i = roads.size();
                break;
            }

        std::sort(roads.begin(), roads.begin()+X, greater2());

        if(reach(roads[0], T, n, m, agentX, agentY) < reach(best, T, n, m, agentX, agentY) &&
            reach(roads[0], T, n, m, agentX, agentY) != 0 && reach(roads[0], T, n, m, agentX, agentY) != -1)
            best = roads[0];
        while(roads.size() > p)
            roads.pop_back();

        if(best.size() == last_best.size()){
            counter++;
            if(counter == 1000)
                break;
        } else
            counter = 0;

        last_best = best;
    }

    cout<<reach(best, T, n, m, agentX, agentY)<<endl;
    cerr<<best<<endl;
    return 0;
}