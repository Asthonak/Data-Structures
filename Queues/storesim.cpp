/**
 @file storesim.cpp

 @brief This program simulates customers in a line.

 @version Original Code 1.00 (09/10/2017) - Ethan M. Park
*/
/*
Author self-assessment statement:
This program is complete and working according to spcecifications,
according to the best of my knowledge.
*/
// Program Description/Support /////////////////////////////////////
/**
 @mainpage
 This program simulates the flow of customers in a line at a store. 

 NOTE: This program is the modification/full implementation of the 
 storesim.cs shell from lab 7. I only wrote the code from lines 
 82-108
*/
// Header Files ///////////////////////////////////////////////////
//
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "config.h"
using namespace std;
//
// Precompiler Directives //////////////////////////////////////////
//
#if LAB7_TEST1
#   include "QueueLinked.cpp"
#else
#   include "QueueArray.cpp"
#endif
//

// Global Constant Definitions ////////////////////////////////////
//
///// NONE
//
// Class Definitions //////////////////////////////////////////////
//
///// NONE
//
// Free Function Prototypes ///////////////////////////////////////
//
///// NONE
//
//
// Main Function Implementation ///////////////////////////////////
//
int main ()
{
#if LAB7_TEST1
    QueueLinked<int> custQ;      // Line (queue) of customers containing the
#else
    QueueArray<int> custQ;       // Line (queue) of customers containing the
#endif 				 //   time that each customer arrived and
                                 //   joined the line
    int simLength,               // Length of simulation (minutes)
        minute,                  // Current minute
        timeArrived,             // Time dequeued customer arrived
        waitTime,                // How long dequeued customer waited
        totalServed = 0,         // Total customers served
        totalWait   = 0,         // Total waiting time
        maxWait     = 0,         // Longest wait
        numArrivals = 0;         // Number of new arrivals

    // Seed the random number generator. Equally instructive to run the
    // simulation with the generator seeded and not seeded.
    srand( 7 );

    cout << endl << "Enter the length of time to run the simulator : ";
    cin >> simLength;

    // Put your code here to run this simulation. Use "rand()" to get
    // a pseudorandom number that you can use to calculate probabilities.

#if LAB7_TEST1
  QueueLinked<int> line1;
  minute = 0;
  waitTime = 0;
  while(minute!=simLength){
    minute++;
    if(!line1.isEmpty()){
      timeArrived = line1.dequeue();
      waitTime = minute-timeArrived;
      if(waitTime>=maxWait){
        maxWait = waitTime;
      }
      totalWait += waitTime;
      totalServed++;
    }
    int k = rand() % 4;
    if(k==1){
      line1.enqueue(minute);
      numArrivals++;
    }
    else if(k==2){
      line1.enqueue(minute);
      line1.enqueue(minute);
      numArrivals+=2;
    }
  }
#endif

    // Print out simulation results
    cout << endl;
    cout << "Customers served : " << totalServed << endl;
    cout << "Average wait     : " << setprecision(2)
         << double(totalWait)/totalServed << endl;
    cout << "Longest wait     : " << maxWait << endl;

    return 0;
}
