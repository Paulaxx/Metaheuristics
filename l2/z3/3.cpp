#include <iostream>
#include<cmath>
#include <vector>
#include <random>
#include<algorithm>
using namespace std;

char possible_move(int x, int y, int **T, int direction, int n, int m){

    switch(direction){
        case(1):{
            if( x>0 && T[x-1][y] != 1)
                return true;
            break;
        }
        case(0):{
            if(x+1 < n && T[x+1][y] != 1)
                return true;
            break;
        }
        case(3):{
            if(y > 0 && T[x][y-1] != 1)
                return true;
            break;
        }
        case(2):{
            if(y+1 < m && T[x][y+1] != 1)
                return true;
            break;
        }
    }
    return false;
}

bool wall_in_the_back(int **T, int x, int y, char direction, int n, int m){
    switch(direction){
        case('U'):{
            if(x+1 < n && T[x+1][y] == 1)
                return true;
            break;
        }
        case('D'):{
            if( x>0 && T[x-1][y] == 1)
                return true;
            break;
        }
        case('L'):{
            if(y+1 < m && T[x][y+1] == 1)
                return true;
            break;
        }
        case('R'):{
            if(y > 0 && T[x][y-1] == 1)
                return true;
            break;
        }
    }
    return false;
}

int main() {

    std::random_device rd;
    std::uniform_real_distribution<double> dist(0, 1);
    std::uniform_int_distribution<int> dist2(0, 4);
    int t, n, m, i, j, agentX, agentY, max_road_length, actualX, actualY, road_length=0, l, d;
    int best_road_length; //T
    string e, current_road="", best_road;
    double x;
    char direction;
    vector<char> moves;

    cin>>t>>n>>m;
    int **T = new int *[n];
    for (i=0;i<n;i++)
        T[i] = new int [m];
    for(i=0;i<n;i++){
        cin>>e;
        for(j=0;j<m;j++){
            T[i][j] = e[j]-48;
        }
    }
    max_road_length = n * m; //number of tries
    best_road_length = max_road_length;

    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            if(T[i][j] == 5){
                agentX = i; //starting position
                agentY = j;
            }
        }
    }

    clock_t start = clock();
    while((clock()-start)/CLOCKS_PER_SEC < t){
        actualX = agentX;
        actualY = agentY;
        road_length = 0;
        current_road = "";

        for(i=0;i<max_road_length;i++){

            if((clock()-start)/CLOCKS_PER_SEC >= t)
                break;
            d = dist2(rd);
            if(possible_move(actualX, actualY, T, d, n, m) == true && wall_in_the_back(T, actualX, actualY, direction, n, m) == false){
                road_length++;

                switch(d){
                    case(0): {
                        actualX++;
                        current_road.push_back('D');
                        break;
                    }
                    case(1): {
                        actualX--;
                        current_road.push_back('U');
                        break;
                    }
                    case(2): {
                        actualY++;
                        current_road.push_back('R');
                        break;
                    }
                    case(3): {
                        actualY--;
                        current_road.push_back('L');
                        break;
                    }
                }
                if(road_length == best_road_length){
                    i = max_road_length*2;
                    break;
                }
                if(T[actualX][actualY] == 8){
                    if(road_length < best_road_length){
                        best_road_length = road_length;
                        best_road = current_road;
                    }
                    i = max_road_length*2;
                    break;
                }
            }
            else if(possible_move(actualX, actualY, T, d, n, m)){
                x = dist(rd);
                if(x < (1.0/exp(road_length/best_road_length))){
                    road_length++;

                    switch(d){
                        case(0): {
                            actualX++;
                            current_road.push_back('D');
                            break;
                        }
                        case(1): {
                            actualX--;
                            current_road.push_back('U');
                            break;
                        }
                        case(2): {
                            actualY++;
                            current_road.push_back('R');
                            break;
                        }
                        case(3): {
                            actualY--;
                            current_road.push_back('L');
                            break;
                        }
                    }
                    if(road_length == best_road_length){
                        i = max_road_length*2;
                        break;
                    }
                    if(T[actualX][actualY] == 8){
                        if(road_length < best_road_length){
                            best_road_length = road_length;
                            best_road = current_road;
                        }
                        i = max_road_length*2;
                        break;
                    }
                }
            }

        }
    }

    if(best_road_length < max_road_length){
        cout<<best_road_length<<endl;
        cerr<<best_road<<endl;
    } else
        cerr<<"too long road"<<endl;
}