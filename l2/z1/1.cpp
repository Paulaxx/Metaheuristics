#include <iostream>
#include <cmath>
#include<string>
#include<ctime>
#include <random>
#include <iomanip>
using namespace std;

double salomon(int w, int x, int y, int z){
    double sum = w*w + x*x + y*y + z*z;
    double s = 2.0 * M_PI * sqrt(sum);
    double cosinus = cos(s);
    double result = 1.00 - cosinus + 0.1*sum;
    return result;
}

int main() {

    double time, x1, x2, x3, x4, initialTemperature, currentT, cooling = 0.9, current[4], best[4], bestValue, random;
    double currentValue, E, EA, p, r;
    bool accept;
    int number, n = 1, i, j, z=0;

    cin>>time>>x1>>x2>>x3>>x4;
    number = time*time*1000;
    initialTemperature = 120.0;
    current[0] = x1, current[1] = x2, current[2] = x3, current[3] = x4;
    best[0] = x1, best[1] = x2, best[2] = x3, best[3] = x4;
    bestValue = salomon(best[0], best[1], best[2], best[3]);
    currentT = initialTemperature;

    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> distr(-1.0, 1.0);

    clock_t start = clock();
    while((clock()-start)/CLOCKS_PER_SEC < time){
        for(i=0; i<number; i++){

            for(j=0;j<4;j++){ //generate neightbour
                random = distr(eng);
                current[j] = best[j] + 0.1*random;
                current[j] = max(min(current[j], 1.00), -1.00);
            }
            currentValue = salomon(current[0], current[1], current[2], current[3]);
            E = abs(currentValue - bestValue);
            if(z == 0){
                z = 100;
                EA = E;
            }

            if(currentValue > bestValue){
                p = exp((-E)/(EA * currentT));
                r = ((double) rand() / (RAND_MAX));
                if(r < p){
                    accept = true;
                }
                else
                    accept = false;
            }
            else
                accept = true;

            if(accept == true) {
                best[0] = current[0], best[1] = current[1], best[2] = current[2], best[3] = current[3];
                bestValue = salomon(best[0], best[1], best[2], best[3]);
                n++;
                EA = (EA * (n - 1) + E) / n;
            }
        }
        currentT = currentT * cooling;

    }
    cout<<fixed<<std::setprecision(3)<<best[0]<<" "<<best[1]<<" "<<best[2]<<" "<<best[3]<<" ";
    cout<<salomon(best[0], best[1], best[2], best[3])<<endl;

    return 0;
}
