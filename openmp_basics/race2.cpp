#include <iostream>
#ifdef _OPENMP
#include <omp.h>
#endif
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int flag;

int hello() {
    int teamsize = 0;
    int tid = 0;
    #ifdef _OPENMP
        teamsize = omp_get_num_threads();
        tid = omp_get_thread_num();
    #else 
        teamsize = 1;

    #endif

    // cout<<"Thread num "<<tid<<" in the team size of "<<teamsize<<"\n";

    return tid;

}


int main(int argc, char* argv[]) {

    int thread_count = 1;

    if(argc == 2) {
        thread_count = strtol(argv[1], NULL, 10); 
    } else {
        cout<<"Please enter the second argument to the command line while running \n";
        return 0;
    }
    int sum = 0;
    // int *sum = new int(0);
    int n = 0; 


    #pragma omp parallel num_threads(thread_count)

    {

        // this just becomes a serial code
        // #pragma omp crititcal 
        // write write conflict
        // sum += hello();

        /*
            ➜  openmp_basics git:(main) ✗ g++ -fopenmp helloworld2.cpp
            ➜  openmp_basics git:(main) ✗ ./a.out 900                 
            sum: 397649
        */

        int tid = hello();

        #pragma omp atomic update
        sum += tid;


        /*
            ➜  openmp_basics git:(main) ✗ g++ -fopenmp helloworld2.cpp
            ➜  openmp_basics git:(main) ✗ ./a.out 900                 
            sum: 404550
        */
        
    
    }
    cout <<"sum: "<<sum<<'\n';


    return 0;
}
