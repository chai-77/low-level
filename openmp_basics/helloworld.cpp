// master thread in serial region spwans team of threads in the parallel region
// those threads execute the code in the parallel region and can have nested parallel regions
// after execution the threads join the master thread

// pragma omp <directive> [clause[, clause] ...]
// <directive> parallel, for, paralllel for, section, sections, ingle ,master, critical, flush, ordered, atomic


// runtime routines
// set and retrieve info about the environment

// omp_get_num_threads() 
// omp_ser_num_treads(n)
// omp_gex_max_treads()

// g++ -E test.cpp -o preprocessed.cpp
// The -E flag tells GCC to stop after preprocessing.

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <iostream>

using namespace std;

void hello() {
    int teamsize = omp_get_num_threads();
    int tid = omp_get_thread_num();

    #pragma omp critical
    {
        // otherwise the op lines dont print in order
        cout<<"Thread num "<<tid<<" in the team size of "<<teamsize<<"\n";
    }
    

}


int main(int argc, char* argv[]) {

    int thread_count;

    if(argc == 2) {
        thread_count = strtol(argv[1], NULL, 10); //sting to long strtol(string, end_pointer, base);
    } else {
        cout<<"Please enter the second argument to the command line while running \n";
        return 0;
    }

    // if no number clause is defined, runs as runtime configuration and environment.
    /* 
        Once the OpenMP runtime creates the thread team,
        the OS scheduler schedules runnable software threads
        onto available logical CPUs.

        On many systems, the default team size is based on the number of processors available to the program.

        The default value of num in the Visual C++ implementation of the OpenMP standard 
        is the number of virtual processors, including hyperthreading CPUs.

        GCC links your program against an OpenMP runtime library (commonly libgomp).

            That runtime is software installed on your system. It is not part of the CPU or the OS scheduler.
            Its job includes:
            Creating and managing OpenMP thread teams.
            Deciding the default team size.
            Synchronizing threads.
            Managing parallel regions.

    */
    if (thread_count < 1000) {
        cout << omp_get_max_threads()<<'\n'; // gets max number of threads possible or greater than
        
        #pragma omp parallel num_threads(thread_count) 
        // entry point
        {
            hello();
        }
        // exit point (cannot jump and end outside this block)
        /* 
            goto outside the parallel region        Not allowed

            throw an exception out of the region        Not allowed

            //exit will exit program, exit() terminates the entire process
        */

    }
    else {
        cout<< "please enter a second argument less than 1000\n";
    }




    return 0;
}


// The master thread does not disappear when OpenMP creates child threads. It is itself one of the threads executing the parallel region.

//  By default, Thread 0 is the master (primary) thread in an OpenMP parallel region.

// Thread 0 is the thread that was already executing your main() before entering the parallel region.