/**
 @file PriorityQueue.cpp

 @author Ethan M. Park

 @brief This program is the implimentation file for a
 priority queue.

 @version Original Code 1.00 (11/13/2017) - Ethan M. Park
 
 @date Wednesday, November 15, 2017

*/

// Program Description/Support /////////////////////////////////////
/**
 @mainpage
 This program contains the implementation of PriorityQueue.h, which
 contains the definition for the class PriorityQueue. These class
 serves to create a priority queue.
*/

/*
Author self-assessment statement:
This program is complete and working according to spcecifications,
according to the best of my knowledge.
*/

// Precompiler Directives //////////////////////////////////////////
//
///// NONE
//
// Header Files ///////////////////////////////////////////////////
//
#include "PriorityQueue.h"
#include <iostream>
using namespace std;
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
// Class/Data Structure Member Implementation //////////////////////
//
/** @brief Member Function: PriorityQueue<DataType, KeyType, Comparator>::PriorityQueue(int maxNumber) : Heap<DataType,KeyType,Comparator>(maxNumber)
 * A default constructor for the PriorityQueue class.
 *
 * This function will set PriorityQueue members to inital values
 *
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Initializes the priority queue with default values.
 *
 */
template<typename DataType, typename KeyType, typename Comparator>
PriorityQueue<DataType, KeyType, Comparator>::PriorityQueue(int maxNumber) : Heap<DataType,KeyType,Comparator>(maxNumber)
{
}
/** @brief Member Function: void PriorityQueue<DataType, KeyType, Comparator>::enqueue(const DataType &newDataItem)
 * Inserts an item into the queue.
 *
 * This function will insert an item into the
 * queue based on priority using the Heap class.
 *
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a prioirity queue.
 * @post Inserts an item into the queue.
 *
 */
template<typename DataType, typename KeyType, typename Comparator>
void PriorityQueue<DataType, KeyType, Comparator>::enqueue(const DataType &newDataItem)
{
  Heap<DataType, KeyType, Comparator>::insert(newDataItem);
}
/** @brief Member Function: DataType PriorityQueue<DataType, KeyType, Comparator>::dequeue()
 * Removes an item from the queue.
 *
 * This function will remove an item into the
 * and return the data of the removed item using
 * the Heap class.
 *
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a prioirity queue.
 * @post Removes an item from the queue.
 *
 */
template<typename DataType, typename KeyType, typename Comparator>
DataType PriorityQueue<DataType, KeyType, Comparator>::dequeue()
{
  return Heap<DataType, KeyType, Comparator>::remove();
}
