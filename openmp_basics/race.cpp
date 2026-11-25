#include <iostream>
#ifdef _OPENMP
#include <omp.h>
#endif
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int flag;

void hello(int * sum, int n) {
    int teamsize = 0;
    int tid = 0;
    #ifdef _OPENMP
        teamsize = omp_get_num_threads();
        tid = omp_get_thread_num();

        // *sum = *sum + tid; // this can be a race condition
        /*
        thread 1 reads sum as 10 and does 10 + 1
        thread 2 also reads sum as 10 and does 10 + 2

        now who ever is last to update sum, the value of sum will be that

        critical section -> where threads can access shared resources
        */
        #pragma omp critical
        {
            *sum = *sum + tid;
        }
        n = n+ tid;

    #else 
        teamsize = 1;

    #endif

    // cout<<"Thread num "<<tid<<" in the team size of "<<teamsize<<"\n";

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

    // if openmp flag is not set while compiling this gets ignored
    #pragma omp parallel num_threads(thread_count)
    // entry point
    {
        hello(&sum,n);
    
    }
    cout << sum << " "<<n<<'\n';


    return 0;
}
