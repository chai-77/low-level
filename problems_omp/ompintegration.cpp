#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <math.h>

#define PI 3.14159265358

using namespace std;

/*
    divide n trapaziums into m threads
    n >> m & n%m == 0


    // how to assign local_a and local_b to each thread?
    // local_n = N/M

    local_a = a + tid*(h*local_n)
    local_b = local_a + (h*local_n)

*/

double func(double x) {
    return sin(x)/(2*x*x*x);
}

void trapazoidal_rule (int n, double a, double b, double *result) {
    double h, x, total;
    int i;
    int tid = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
    int local_n;
    double local_a, local_b;

    h = (b-a)/n;


    local_n = n / thread_count;
    local_a = a + tid*local_n*h;
    local_b = local_a + local_n*h;

    total = (func(local_a) + func(local_b))/2.0;

    for(i = 1; i < local_n; i++) {

        x = local_a + i*h;
        total += func(x);
    }

    total = total*h;
    #pragma omp critical 
    {
        // cout<<tid<<" "<<total<<"\n"; 
        *result = *result + total;
    }

   


}


int main(int argc, char* argv[]) {
    double a, b, final_result;
    int n;

    int thread_count = 1;

    if(argc == 2) {
        thread_count = strtol(argv[1], NULL, 10); //sting to long strtol(string, end_pointer, base);
    } else {
        cout<<"Please enter the second argument to the command line while running \n";
        return 1;
    }

    n = 32;
    a = 1.0;
    b = PI;
    final_result = 0.0;

    #pragma omp parallel num_threads(thread_count) 
    {
        trapazoidal_rule(n,a,b,&final_result);
    }

    printf("\nArea under the curve = %lf\n\n", final_result);



    return 0;
}