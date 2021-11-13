/**
 @file ossim.cpp

 @brief This program simulates a priority queue.

 @version Original Code 1.00 (11/13/2017) - Ethan M. Park

 @date Wednesday, November 15, 2017
*/

// Program Description/Support /////////////////////////////////////
/**
 @mainpage
 This program simulates a priority queue in which items are placed into a queue based on their given priority.

 NOTE: This header file was created using the shell ossim.cs given in the lab folder.
*/

/*
Author self-assessment statement:
This program is complete and working according to spcecifications,
according to the best of my knowledge.
*/


// Header Files ///////////////////////////////////////////////////
//
#include <iostream>
#include <cstdlib>
#include "PriorityQueue.cpp"
using namespace std;
//
// Precompiler Directives //////////////////////////////////////////
//
///// NONE
//
// Global Constant Definitions ////////////////////////////////////
//
///// NONE
//
// Class Definitions //////////////////////////////////////////////
//
///// NONE
//
//
// Declaration for the task data struct///////////////////////////
//
struct TaskData
{
    int getPriority () const
        { return priority; }     // Returns the priority. Needed by the heap.

    int priority,                // Task's priority
        arrived;                 // Time when task was enqueued

};
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
    PriorityQueue<TaskData, int, Less<int> > taskPQ;   // Priority queue of tasks
    TaskData task;               // Task
    int simLength,               // Length of simulation (minutes)
        minute,                  // Current minute
        numPtyLevels,            // Number of priority levels
        numArrivals,             // Number of new tasks arriving
        j;                       // Loop counter

    // Seed the random number generator
    srand( 7 );

    cout << endl << "Enter the number of priority levels : ";
    cin >> numPtyLevels;

    cout << "Enter the length of time to run the simulator : ";
    cin >> simLength;

    for ( minute = 0 ; minute < simLength ; minute++ )
    {
        // Dequeue the first task in the queue (if any).
	// Your code here
        if(!taskPQ.isEmpty())
        {
            task = taskPQ.dequeue();
            cout << "At " << minute << " dequeued : " << task.priority << " " 
            << task.arrived << " " << (minute - task.arrived) << endl;
        }

        // Determine the number of new tasks and add them to
        // the queue.
	// Your code here
        int k = rand() % 4;
        if(k==1)
        {
            if(!taskPQ.isFull())
            {
                task.arrived = minute;
                task.priority = rand() % numPtyLevels;
                taskPQ.enqueue(task);
            }
        }
        else if(k==2)
        {
            for(j=0;j<2;j++)
            {
                if(!taskPQ.isFull())
                {
                    task.arrived = minute;
                    task.priority = rand() % numPtyLevels;
                    taskPQ.enqueue(task);
                }
            }
        }
    }

    return 0;
}
//
