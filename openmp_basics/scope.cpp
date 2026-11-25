#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

int main () {

    int b = 23;
    int c = -2;

    // int a = 0;
    
    #pragma omp parallel num_threads(3) 
    {
        // int a =0; // this is a thread private variable, cannot be accessed outside scope
        int a = 0;
        int d;
        #ifdef _OPENMP
        d = omp_get_thread_num();
        #endif

        a = 42 + d;
        b = 1;
        #pragma omp ciritcal
        {
            c += a + b; //data race
        }
        // printf("a=%d b=%d c=%d \n",a,b,c);
    }

    c = c / 2;

    // printf("a=%d b=%d c=%d \n",a,b,c);
    printf("b=%d c=%d \n",b,c);


    return 0;

}