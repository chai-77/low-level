
#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <math.h>
/*

    curve 
    i = int a to b f(x)dx

    Trapazoidal rule

    area = half * (sum of length of parallel sides) * (perpendicular distance between parallel sides)
    Area= 1/2 * (a+b) * h
    
    a = height of the left side.
    b = height of the right side.
    h = width of the trapezoid.

    therefore ,
    height = y = f(x)
    Area_i = h * [f(x_i) + f(x_{i+1})] / 2


    divide the interval into n parts, each part's width(delx) is 
    h = (b - a) / n

    calculates cordinates
    h = (b - a) / n  


    now, 
    area = [h * (f(x1) + f(x2))/2] + [h * (f(x2) + f(x3))/2] + ... + [h * (f(xn-1) + f(xn))/2]

    area = h/2 * [f(x1) + 2f(x2) + 2f(3) + ... + 2f(xn-1) + f(xn)]


    in the code 
    I = h [ (f(x₀) + f(xₙ))/2 + f(x₁) + ⋯ + f(xₙ₋₁) ]

    rearranging gets us 
    I = (h/2) [ f(x₀) + 2f(x₁) + ⋯ + 2f(xₙ₋₁) + f(xₙ) ]

*/

#define PI 3.14159265358

using namespace std;

double func(double x) {
    return sin(x)/(2*x*x*x);
}

void trapezoidal_rule(int n, double a, double b, double *result) {

    double h, total;
    int i;

    h = (b-a)/n;

    total = (func(a) + func(b))/2.0;

    for(i = 1; i < n; i++) {
        total += func(a + i*h);
    }

    total = total*h;

    *result = total;
}

int main() {

    double a, b, final_result;
    int n;

    n = 32;
    a = 1.0;
    b = PI;
    final_result = 0.0;

    trapezoidal_rule(n, a, b, &final_result);

    printf("\nArea under the curve = %lf\n\n", final_result);

    return 0;
}
