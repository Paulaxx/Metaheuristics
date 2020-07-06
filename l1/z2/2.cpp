#include <iostream>
#include <ctime>
#include <random>

using namespace std;

thread_local std::mt19937 gen{std::random_device{}()};

template<typename T>
T random(T min, T max) {
    return std::uniform_int_distribution<T>{min, max}(gen);
}

int is(int tab[], int n, int x){
    int i;
    for(i=0;i<n;i++){
        if(tab[i]==x){
            return 0;
        }
    }
    return 1;
}

int is2(int **tab, int x, int y, int c){
    int i,j;
    for(i=0;i<c;i++){
        if(tab[i][0] == x && tab[i][1] == y){
            return 0;
        }
        else if(tab[i][0] == y && tab[i][1] == x){
            return 0;
        }
    }
    return 1;
}

void gen_candidates(int current[], int **tabu, int n, int **candidates, int c){
    int x,y,i;
    for(i=0;i<c;i++){
        do{
            x = random(2,n);
            y = random(2,n);
        }
        while(x == y || is2(candidates, x, y, c) == 0);
        candidates[i][0] = x;
        candidates[i][1] = y;
    }
}

int calculate_cost(int **distance, int actual_path[], int n){
    int cost=0,i;
    cost = distance[0][actual_path[0]-1];
    for(i=0;i<n-1;i++){
        cost = cost + distance[actual_path[i]-1][actual_path[i+1]-1];
    }
    return cost;
}

void swap(int tab[], int x, int y){
    int temp=tab[x];
    tab[x] = tab[y];
    tab[y] = temp;
}

void insertTabu(int **tabu, int x, int y, int size, int t){
        int i;
        if(t < size){
            tabu[t][0] = x;
            tabu[t][1] = y;
        }
        else{
            int **temp = new int *[size];
            for (i=0;i<size;i++)
                temp[i] = new int [2];

            for(i=0;i<size-1;i++){
                temp[i][0] = tabu[i+1][0];
                temp[i][1] = tabu[i+1][1];
            }
            temp[size-1][0] = x;
            temp[size-1][1] = y;
        }
}

int find(int *current, int n, int x){
    int i;
    for(i=0;i<n;i++){
        if(current[i] == x)
            return i;
    }
    return 0;
}


int main() {
    int n,i,j,x,cost, minCost, pomCost,X,Y, t=0, time, tabuSize, neightbours, k, l;

    cin>>time>>n;
    tabuSize = 3*n;
    if(n>=50)
        neightbours = n*10;
    else
        neightbours = n;

    int * best = new int[n];
    int * current = new int[n];
    for(i=0;i<n;i++){
        current[i]=0;
    }

    int **tabu = new int *[tabuSize];
    for (i=0;i<tabuSize;i++)
        tabu[i] = new int [2];

    int **distance = new int *[n];
    for (i=0;i<n;i++)
        distance[i] = new int [n];

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            cin>>distance[i][j];
        }
    }

    int **candidates = new int *[neightbours];
    for (i=0;i<neightbours;i++)
        candidates[i] = new int [2];

    for(i=0;i<tabuSize;i++){
        for(j=0;j<2;j++){
            tabu[i][j] = 0;
        }
    }
    for(i=0;i<n-1;i++){
        do {
            x = random(2,n);
        }
        while(is(current, n-1, x) == 0);
        current[i] = x;
    }
    current[n-1] = 1;
    cost = calculate_cost(distance, current, n);
    for(i=0;i<n;i++){
        best[i] = current[i];
    }
    //minCost = calculate_cost(distance, current, n);

    clock_t start = clock();
    while((clock()-start)/CLOCKS_PER_SEC < time){
        gen_candidates(current, tabu, n, candidates, neightbours);

        k = find(current, n, candidates[0][0]);
        l = find(current, n, candidates[0][1]);
        swap(current, k, l);
        minCost = calculate_cost(distance, current, n);
        swap(current, k, l);
        X = candidates[0][0];
        Y = candidates[0][1];

        for(i=1;i<neightbours;i++){

            k = find(current, n, candidates[i][0]);
            l = find(current, n, candidates[i][1]);
            swap(current, k, l);
            pomCost = calculate_cost(distance, current, n);
            swap(current, k, l);

            if(pomCost<minCost && is2(tabu, candidates[i][0], candidates[i][1], tabuSize) == 1){
                minCost = pomCost;
                k = find(current, n, candidates[i][0]);
                l = find(current, n, candidates[i][1]);
                X = candidates[i][0];
                Y = candidates[i][1];
                swap(current, k, l); //najlepszy sasiad = swap k l
                if(pomCost < calculate_cost(distance, best, n)){
                    for(j=0;j<n;j++){
                        best[j] = current[j]; //best = najlepszy sasiad && current = najlepszy sasiad
                    }
                    insertTabu(tabu, X, Y, tabuSize, t);
                    t++;
                }
            }
            else if(pomCost < calculate_cost(distance, best, n)){
                minCost = pomCost;
                k = find(current, n, candidates[i][0]);
                l = find(current, n, candidates[i][1]);
                X = candidates[i][0];
                Y = candidates[i][1];
                swap(current, k, l);
                for(j=0;j<n;j++){
                    best[j] = current[j];
                }
                insertTabu(tabu, X, Y, tabuSize, t);
                t++;

            }
        }
    }

    cout<<calculate_cost(distance, best, n)<<endl;
    cerr<<"1"<<" ";
    for(i=0;i<n;i++){
        cerr<<best[i]<<" ";
    }
    cerr<<endl;
    return 0;
}