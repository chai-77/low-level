#include <iostream>
#ifdef _OPENMP
#include <omp.h>
#endif
#include <stdio.h>
#include <stdlib.h>

using namespace std;


int main() {

    int arr[6];


    for (int i = 0; i <6; i++) {
        arr[i] = i;
    }


    #pragma omp parallel num_threads(5)
    {   
        int tid;
        #ifdef _OPENMP
            tid = omp_get_thread_num();
        #endif

        //cannot remove this data race as we cannot handle the order of threads
        // read write conflict
            arr[tid] = arr[tid+1] +1; 
       
    }

    for(int i = 0; i < 6; i++) {
        cout<<arr[i]<<" ";
    }

    return 0;


}