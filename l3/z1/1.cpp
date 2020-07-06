#include <iostream>
#include <cmath>
#include<ctime>
#include <random>
#include <iomanip>
#include<algorithm>
using namespace std;

vector<double>e;

double function(vector<double>x, vector<double>e){
    int i;
    double result=0;
    for(i=0;i<x.size();i++){
        result += e[i] * pow(abs(x[i]), i);
    }
    return result;
}


int partition(vector<vector<double>> &values, int left, int right, vector<double>e) {
    int pivotIndex = left + (right - left) / 2;
    int pivotValue = function(values[pivotIndex], e);
    int i = left, j = right;
    vector<double> temp;
    while(i <= j) {
        while(function(values[i], e) < pivotValue) {
            i++;
        }
        while(function(values[j],e) > pivotValue) {
            j--;
        }
        if(i <= j) {
            temp = values[i];
            values[i] = values[j];
            values[j] = temp;
            i++;
            j--;
        }
    }
    return i;
}

void quicksort(vector<vector<double>> &values, int left, int right, vector<double>e) {
    if(left < right) {
        int pivotIndex = partition(values, left, right, e);
        quicksort(values, left, pivotIndex - 1, e);
        quicksort(values, pivotIndex, right, e);
    }
}

void cross(vector<double> &parent1, vector<double> &parent2){

    int cross1, cross2;
    double temp;
    std::random_device rd2;
    std::uniform_int_distribution<int> dist2(0, 4);
    cross1 = dist2(rd2);
    cross2 = dist2(rd2);
    temp = parent1[cross1];
    parent1[cross1] = parent2[cross2];
    parent2[cross2] = temp;
}

void mutate(vector<double> &parent){

    int p1, p2;
    double p, q;
    std::random_device rd2;
    std::uniform_int_distribution<int> dist2(0, );
    p1 = dist2(rd2);
    p2 = dist2(rd2);

    std::random_device rd;
    std::uniform_real_distribution<double> dist(0, 1);
    p = dist(rd);
    q = pow(parent[p1]/parent[p2], 2) * pow(1-p, 2) + 1;
    q = sqrt(q);
    parent[p1] = parent[p1] * p;
    parent[p2] = parent[p2] * q;
    if(parent[p1] > 5)
        parent[p1] = 5;
    if(parent[p2] > 5)
        parent[p2] = 5;
}

void generate_new_population(vector<vector<double>> &population){
    int i, j, p;
    vector<vector<double>> parents_to_cross;
    vector<vector<double>> parents_to_mutate;
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 9);
    for(i=0;i<5;i++){
        p = dist(rd);
        parents_to_cross.push_back(population[p]);
    }
    for(i=0;i<parents_to_cross.size();i++){ //pozycja 1 rodzica
        for(j=i;j<parents_to_cross.size();j++){ //pozycja 2 rodzica
            cross(parents_to_cross[i], parents_to_cross[j]);
        }
    }
    for(i=0;i<5;i++){
        p = dist(rd);
        parents_to_mutate.push_back(population[p]);
        mutate(parents_to_mutate[i]);
    }
    for(i=0;i<parents_to_cross.size();i++)
        population.push_back(parents_to_cross[i]);
    for(i=0;i<parents_to_mutate.size();i++)
        population.push_back(parents_to_mutate[i]);
}

int main() {

    int i,j, time, population_size=10, counter=0;
    double iks, ee, best, last_best;
    vector<double>x;
    vector<vector<double>> population;
    cin>>time;
    for(i=0;i<5;i++){
        cin>>iks;
        x.push_back(iks);
    }
    for(i=0;i<5;i++){
        cin>>ee;
        e.push_back(ee);
    }
    struct greater{
        bool operator()( vector<double>x, vector<double>y) const {
            return function(x, e) < function(y, e);
        }
    };
    for(i=0;i<population_size;i++){
        population.push_back(x);
    }
    last_best = best = function(x, e);

    clock_t start = clock();
    while((clock()-start)/CLOCKS_PER_SEC < time){

        generate_new_population(population);
        std::sort(population.begin(), population.end(), greater());
        while(population.size() > 10){
            population.pop_back();
        }
        best = function(population[0], e);
        x = population[0];
        if(best == last_best){
            counter++;
            if(counter == 1000)
                break;
        } else
            counter = 0;
        last_best = best;
    }

    cout<<fixed<<setprecision(5)<<x[0]<<" "<<x[1]<<" "<<x[2]<<" "<<x[3]<<" "<<x[4]<<" "<<best<<endl;
    return 0;
}