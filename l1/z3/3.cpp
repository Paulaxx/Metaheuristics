#include <iostream>
#include <ctime>
#include <random>
#include<cmath>
#include<string>

using namespace std;

string generateX0(int **T, int n, int m, int actX, int actY){
    int i, j;
    string result = "";
    for(i=actY+1;i<m && T[actX][i] != 1;i++){
        result = result + 'R';
        actY++;
    }
    if(T[actX][i] == 8){
        result = result + 'R';
        return result;
    }

    for(j=actX-1;j>=0 && T[j][actY] != 1;j--){
        result = result + 'U';
        actX--;
        if(T[actX][actY+1] == 8){
            result = result + 'R';
            return result;
        }
    }
    if(T[j][actY] == 8){
        result = result + 'U';
        return result;
    }

    for(i=actY-1;i>=0 && T[actX][i] != 1;i--){
        result = result + 'L';
        actY--;
    }
    if(T[actX][i] == 8){
        result = result + 'L';
        return result;
    }

    for(j=actX+1;j<n && T[j][actY] != 1;j++){
        result = result + 'D';
        actX++;
        if(T[actX][actY] == 8){
            return result;
        }
    }
    if(T[j][actY] == 8){
        result = result + 'D';
        return result;
    }

    for(i=actY+1;i<m && T[actX][i] != 1;i++){
        result = result + 'R';
        actY++;
        if(T[actX][actY] == 8){
            return result;
        }
    }
    if(T[actX][i] == 8){
        result = result + 'R';
        return result;
    }

    for(j=actX-1;j>=0 && T[j][actY] != 1;j--){
        result = result + 'U';
        actX--;
        if(T[actX][actY] == 8){
            return result;
        }
    }
    if(T[j][actY] == 8){
        result = result + 'U';
        return result;
    }
}


string generateX(int **T, int n, int m, int actX, int actY){
    int i, j;
    string result = "";

    while(actY < m-1){
        if(T[actX+1][actY] == 8){
            result = result + 'D';
            return result;
        }
        else if(T[actX][actY+1] == 8){
            result = result + 'R';
            return result;
        }
        else if(T[actX-1][actY] == 8){
            result = result + 'U';
            return result;
        }

        if(T[actX][actY+1] != 1){
            result = result + 'R';
            actY++;
        }
        else
            break;
    }

    while(actX > 0){
        if(T[actX-1][actY] == 8){
            result = result + 'U';
            return result;
        }
        else if(T[actX][actY+1] == 8){
            result = result + 'R';
            return result;
        }
        else if(T[actX][actY-1] == 8){
            result = result + 'L';
            return result;
        }

        if(T[actX-1][actY] != 1){
            result = result + 'U';
            actX--;
        } else
            break;
    }

    while(actY > 0){
        if(T[actX-1][actY] == 8){
            result = result + 'U';
            return result;
        }
        else if(T[actX][actY-1] == 8){
            result = result + 'L';
            return result;
        }
        else if(T[actX+1][actY] == 8){
            result = result + 'D';
            return result;
        }

        if(T[actX][actY-1] != 1){
            result = result + 'L';
            actY--;
        } else
            break;
    }

    while(actX < n-1){
        if(T[actX+1][actY] == 8){
            result = result + 'D';
            return result;
        }
        else if(T[actX][actY-1] == 8){
            result = result + 'L';
            return result;
        }
        else if(T[actX][actY+1] == 8){
            result = result + 'R';
            return result;
        }

        if(T[actX+1][actY] != 1){
            result = result + 'D';
            actX++;
        } else
            break;
    }

    while(actY < m-1){
        if(T[actX+1][actY] == 8){
            result = result + 'D';
            return result;
        }
        else if(T[actX][actY+1] == 8){
            result = result + 'R';
            return result;
        }
        else if(T[actX-1][actY] == 8){
            result = result + 'U';
            return result;
        }

        if(T[actX][actY+1] != 1){
            result = result + 'R';
            actY++;
        } else
            break;
    }

    while(actX > 0){
        if(T[actX-1][actY] == 8){
            result = result + 'U';
            return result;
        }
        else if(T[actX][actY+1] == 8){
            result = result + 'R';
            return result;
        }
        else if(T[actX][actY-1] == 8){
            result = result + 'L';
            return result;
        }

        if(T[actX-1][actY] != 1){
            result = result + 'U';
            actX--;
        } else
            break;
    }

}


bool reach(string road, int l, int x, int y, int **T, int n, int m){
    int i, j;
    for(i=0;i<l;i++){
        if(road[i] == 'R' && y+1 < m){
            y = y + 1;
        }
        else if(road[i] == 'L' && y-1 >= 0){
            y = y - 1;
        }
        if(road[i] == 'U' && x-1 >= 0){
            x = x - 1;
        }
        if(road[i] == 'D' && x+1 < n){
            x = x + 1;
        }
    }

    if(T[x][y] == 8)
        return 1;
    return 0;
}


int lengthRoad(string road, int x, int y, int **T, int n, int m){ //funkcja celu(-1 nie dotarl, l dotarl w tylu krokach)
    int l = road.length();
    if(reach(road, l, x, y, T, n, m) == 1)
        return l;
    return -1;
}

int generateNeightbours(string road, string *N){

    int i, j, l=0;
    for(i=0;i<road.length();i++){
        for(j=i+1;j<road.length();j++){
            swap(road[i], road[j]);
            N[l] = road;
            l++;
        }
    }
    return l;
}

string deleteFromRoad(string road, int i1, int i2){
    int j;
    string answer="";
    for(j=0;j<road.length();j++){
        if(j != i1 && j != i2){
            answer = answer + road[j];
        }
    }
    return answer;
}

string shorten(string road){
    int i, l=road.length();
    string x, result;
    for(i=0;i<l-1;i++){
        if((road[i] == 'D' && road[i+1] == 'U') || (road[i] == 'U' && road[i+1] == 'D')
        || (road[i] == 'R' && road[i+1] == 'L') || (road[i] == 'L' && road[i+1] == 'R')){
            road = deleteFromRoad(road, i, i+1);
        }
    }
    return road;
}

void insertTabu(string *Tabu, string road, int t, int tabuSize){
    int i;
    if(t < tabuSize){
        Tabu[t] = road;
    }
    else {
        string *temp = new string[tabuSize];
        for (i = 0; i < tabuSize - 1; i++) {
            temp[i] = Tabu[i + 1];
        }
        temp[tabuSize - 1] = road;
    }
}

bool isInTabu(string *Tabu, string road, int tabuSize){
    int i;
    for(i=0;i<tabuSize;i++){
        if(Tabu[i].compare(road) == 0){
            return 1;
        }
    }
    return 0;
}

int main() {

    int time, n, m, i, j, agentX, agentY, x, l, L, t=0;
    string e, road;

    cin>>time>>n>>m;
    int **T = new int *[n];
    for (i=0;i<n;i++)
        T[i] = new int [m];
    for(i=0;i<n;i++){
        cin>>e;
        for(j=0;j<m;j++){
            T[i][j] = e[j]-48;
        }
    }

    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            if(T[i][j] == 5){
                agentX = i;
                agentY = j;
            }
        }
    }

    road = generateX(T, n, m, agentX, agentY);
    L = road.length();
    x = L*(L-1)/2;
    string * Neightbours = new string[x];
    string * Tabu = new string[x];

    insertTabu(Tabu, road, t, x);
    t++;

    clock_t start = clock();
    while((clock()-start)/CLOCKS_PER_SEC < time){

        l = generateNeightbours(road, Neightbours);
        for(i=0;i<l;i++){
            if(reach(Neightbours[i], Neightbours[i].length(), agentX, agentY, T, n, m) == 1
                && isInTabu(Tabu, Neightbours[i], x) == 0){
                insertTabu(Tabu, Neightbours[i], t, x);
                t++;
                Neightbours[i] = shorten(Neightbours[i]);
                if(lengthRoad(Neightbours[i], agentX, agentY, T, n, m) < lengthRoad(road, agentX, agentY, T, n, m)
                    && reach(Neightbours[i], Neightbours[i].length(), agentX, agentY, T, n, m) == 1){
                    road = Neightbours[i];
                }
            }
        }
    }
    cout<<lengthRoad(road, agentX, agentY, T, n, m)<<endl;
    cerr<<road<<endl;

    return 0;
}