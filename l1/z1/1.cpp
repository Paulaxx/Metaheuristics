#include <ctime>
#include <cstdlib>
#include <random>
#include<ctime>
#include<iostream>
#include <iomanip>
using namespace std;

double happyCat(double x1, double x2, double x3, double x4){
    double w, result, q;
    double nor_euk = sqrt(x1*x1 + x2*x2 + x3*x3 + x4*x4);
    w = pow(pow(nor_euk, 2) - 4.00, 2);
    w = pow(w, (double)1.00/8.00);
    q = (double)1/2 * pow(nor_euk, 2) + x1 + x2 + x3 + x4;
    q = q * (double)1.00/4.00;
    result = w + q + (double)1.00/2.00;
    return result;
}

double griewank(double x1, double x2, double x3, double x4){
    double z, z2, result;
    z = (double)x1*x1/400.00 + (double)x2*x2/400.00 + (double)x3*x3/400.00 + (double)x4*x4/400.00;
    z2 = cos(x1/(double)sqrt(1)) * cos(x2/(double)sqrt(2.00)) * cos(x3/(double)sqrt(3.00)) * cos(x4/(double)sqrt(4.00));
    result = 1.00 + z -z2;
    return result;
}

double happyCatDerivativeX0(double x, double y, double z, double w){
    double g,d, result, exponent=7.00/8.00;
    g = 2.00*x*(w*w + x*x + y*y + z*z -4.00);
    d = pow((w*w + x*x + y*y + z*z -4.00),2);
    d = pow(d, exponent);
    result = (double)(1.00/4.00)*((double)(g/d)+ x + 1.00);
    return result;
}

double happyCatDerivativeX1(double x, double y, double z, double w){
    double g,d, result;
    g = 2.00*y*(w*w + x*x + y*y + z*z -4.00);
    d = pow(pow((w*w + x*x + y*y + z*z -4.00),2), (double)(7.00/8.00));
    result = (double)(1.00/4.00)*((double)(g/d)+ y + 1.00);
    return result;
}

double happyCatDerivativeX2(double x, double y, double z, double w){
    double g,d, result;
    g = 2.00*z*(w*w + x*x + y*y + z*z -4.00);
    d = pow(pow((w*w + x*x + y*y + z*z -4.00),2.00), (double)(7.00/8.00));
    result = (double)(1.00/4.00)*((double)(g/d)+ z + 1.00);
    return result;
}

double happyCatDerivativeX3(double x, double y, double z, double w){
    double g,d, result;
    g = 2.00*w*(w*w + x*x + y*y + z*z -4.00);
    d = pow(pow((w*w + x*x + y*y + z*z -4.00),2), (double)(7.00/8.00));
    result = (double)(1.00/4.00)*((double)(g/d)+ w + 1.00);
    return result;
}

double griewankDerivativeX0(double x, double y, double z, double w){
    double result;
    result = x/2000.00 + sin(x);
    return result;
}

double griewankDerivativeX1(double x, double y, double z, double w){
    double result;
    result = y/2000.00 + sin(y);
    return result;
}

double griewankDerivativeX2(double x, double y, double z, double w){
    double result;
    result = z/2000.00 + sin(z);
    return result;
}

double griewankDerivativeX3(double x, double y, double z, double w){
    double result;
    result = w/2000.00 + sin(w);
    return result;
}



int main(){

    int i, time, b;
    double alfa=0.01, x0[4]={1.00,1.00,1.00,1.00}, grad[4], x[4], xLast[4], xTemp[4], minCost;
    for(i=0;i<4;i++){
        xLast[i] = x0[i];
    }

    cin>>time>>b;
    if(b == 0){
        minCost = happyCat(x[0], x[1], x[2], x[3]);
    }
    else
        minCost = griewank(x[0], x[1], x[2], x[3]);


    clock_t start = clock();
    while((clock()-start)/CLOCKS_PER_SEC < time){
        if(b == 0){
            grad[0] = happyCatDerivativeX0(xLast[0], xLast[1], xLast[2], xLast[3]);
            grad[1] = happyCatDerivativeX1(xLast[0], xLast[1], xLast[2], xLast[3]);
            grad[2] = happyCatDerivativeX2(xLast[0], xLast[1], xLast[2], xLast[3]);
            grad[3] = happyCatDerivativeX3(xLast[0], xLast[1], xLast[2], xLast[3]);

            for(i=0;i<4;i++){
                xTemp[i] = xLast[i] - alfa*grad[i];
            }
            if(happyCat(xTemp[0], xTemp[1], xTemp[2], xTemp[3]) < minCost){
                for(i=0;i<4;i++){
                    x[i] = xTemp[i];
                    minCost = happyCat(xTemp[0], xTemp[1], xTemp[2], xTemp[3]);
                }
            }
            for(i=0;i<4;i++){
                xLast[i] = x[i];
            }
        }
        else{
            grad[0] = griewankDerivativeX0(xLast[0], xLast[1], xLast[2], xLast[3]);
            grad[1] = griewankDerivativeX1(xLast[0], xLast[1], xLast[2], xLast[3]);
            grad[2] = griewankDerivativeX2(xLast[0], xLast[1], xLast[2], xLast[3]);
            grad[3] = griewankDerivativeX3(xLast[0], xLast[1], xLast[2], xLast[3]);

            for(i=0;i<4;i++){
                xTemp[i] = xLast[i] - alfa*grad[i];
            }
            if(griewank(xTemp[0], xTemp[1], xTemp[2], xTemp[3]) < minCost){
                for(i=0;i<4;i++){
                    x[i] = xTemp[i];
                    minCost = griewank(xTemp[0], xTemp[1], xTemp[2], xTemp[3]);
                }
            }
            for(i=0;i<4;i++){
                xLast[i] = x[i];
            }
        }

    }
    std::cout << std::setprecision(5) << std::showpoint << std::fixed;
    cout<<x[0]<<" "<<x[1]<<" "<<x[2]<<" "<<x[3]<<" "<<minCost<<endl;;

}
