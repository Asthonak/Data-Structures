/**
 @file Heap.cpp

 @author Ethan M. Park

 @brief This program is the implimentation file for a max
 heap.

 @version Original Code 1.00 (11/12/2017) - Ethan M. Park
 
 @date Wednesday, November 15, 2017

*/

// Program Description/Support /////////////////////////////////////
/**
 @mainpage
 This program contains the implementation of Heap.h, which contains
 the definition for the class Heap. This class serves to create a
 max heap. Multiple helper function are used to help with recurssion.
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
#include "Heap.h"
#include <stdexcept>
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
/** @brief Member Function: Heap<DataType, KeyType, Comparator>::Heap(int maxNumber) : maxSize(maxNumber), size(0)
 * A default constructor for the Heap class.
 *
 * This function will set Heap members to inital values
 *
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Initializes the max heap with default values.
 *
 */
template<typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::Heap(int maxNumber) : maxSize(maxNumber), size(0)
{
  dataItems = new DataType[maxSize];
}
/** @brief Member Function: Heap<DataType, KeyType, Comparator>::Heap(const Heap& other)
 * A copy constructor for the Heap class. 
 *
 * This function will be used to initialize the a max
 * heap with the values of another heap.
 *
 * @param other Contains the source heap that will be copied
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Initializes the heap with the values of another heap.
 *
 */
template<typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::Heap(const Heap& other)
{
  maxSize = other.maxSize;
  size = other.size;
  dataItems = new DataType[maxSize];
  for(int i=0;i<size;i++)
  {
    dataItems[i] = other.dataItems[i];
  }
}
/** @brief Member Function: Heap<DataType, KeyType, Comparator>& Heap<DataType, KeyType, Comparator>::operator=(const Heap& other)
 * An overloaded assignment operator for the Heap class.
 *
 * This function will be used to initialize the a max
 * heap with the values of another heap.
 *
 * @param other Contains the source heap that will be copied
 * @return Heap<DataType, KeyType, Comparator>& Returns the address of the this heap
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Initializes the heap with the values of another heap.
 *
 */
template<typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>& Heap<DataType, KeyType, Comparator>::operator=(const Heap& other)
{
  if(this != &other)
  {
    delete [] dataItems;
    maxSize = other.maxSize;
    size = other.size;
    dataItems = new DataType[maxSize];
    for(int i=0;i<size;i++)
    {
      dataItems[i] = other.dataItems[i];
    }
  }
  return *this;
}
/** @brief Member Function: Heap<DataType, KeyType, Comparator>::~Heap()
 * The destructor for the Heap class.
 *
 * This function will be used to deallocate dynamic
 * memmory in the max heap using the clear() method
 * then deleting the dynamic array.
 *
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a heap.
 * @post Deletes the data of the heap.
 *
 */
template<typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::~Heap()
{
  clear();
  delete [] dataItems;
}
/** @brief Member Function: void Heap<DataType, KeyType, Comparator>::insert (const DataType &newDataItem) throw(logic_error)
 * Inserts an item into the max heap
 *
 * This function will take in an a data item and insert
 * the item in the correct spot and increase the current,
 * size of the arrry by 1. It then rearanges the heap by
 * comparing the inserted item with its parent stopping
 * if it is less than its parent. Uses the helper
 * functions swap()and Parent()
 *  
 * @param &newDataItem Data item that will be inserted into the heap.
 * @return NONE
 * 
 * @exception Heap cannot be full.
 * 
 * @pre Heap is does not contain data item.
 * @post Data item is in proper position in the heap.
 *
 */
template<typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::insert (const DataType &newDataItem) throw(logic_error)
{
  if(isFull())
  {
    throw(logic_error("insert() heap full"));
  }
  int childIndex = size++;
  dataItems[childIndex] = newDataItem;
  //while childIndex > 0 or child is greater than parent, swap child and parent
  while(childIndex > 0 && comparator(newDataItem.getPriority(), dataItems[Parent(childIndex)].getPriority()))
  {
    swap(Parent(childIndex),childIndex);
    childIndex = Parent(childIndex);
  }
}
/** @brief Member Function: DataType Heap<DataType, KeyType, Comparator>::remove() throw(logic_error)
 * Deletes an item from the max heap
 *
 * This function will remove the largest item (the root),
 * replace it with the last item item (size-1), and reduces
 * the current size by 1. It then rearanges the heap by
 * comparing the new root with its children, stoping if 
 * it is greater than both children. Uses the helper
 * functions swap(), LeftChild(), and RightChild()
 *  
 * @param NONE
 * @return returns the data of the removed item.
 * 
 * @exception Heap cannot be empty.
 * 
 * @pre Heaps max item is requested.
 * @post Data item in root is removed and heap is rearranged.
 *
 */
template<typename DataType, typename KeyType, typename Comparator>
DataType Heap<DataType, KeyType, Comparator>::remove() throw(logic_error)
{
  if(isEmpty())
  {
    throw(logic_error("remove() heap empty"));
  }

  DataType et = dataItems[0];
  dataItems[0] = dataItems[--size];
  int parentIndex = 0;
  while(parentIndex<size)
  {
    if(RightChild(parentIndex) <= size)
    {
      //if parent greater than left and right
      if(comparator(dataItems[LeftChild(parentIndex)].getPriority(),dataItems[parentIndex].getPriority())
      && comparator(dataItems[RightChild(parentIndex)].getPriority(),dataItems[parentIndex].getPriority()))
      {
        return ret;
      }
      //if left is greater than right
      else if(comparator(dataItems[LeftChild(parentIndex)].getPriority(),dataItems[RightChild(parentIndex)].getPriority()))
      {
        swap(parentIndex,LeftChild(parentIndex));
        parentIndex = LeftChild(parentIndex);
      }
      //else if right is greater than left
      else if(comparator(dataItems[RightChild(parentIndex)].getPriority(),dataItems[LeftChild(parentIndex)].getPriority()))
      {
        swap(parentIndex,RightChild(parentIndex));
        parentIndex = RightChild(parentIndex);
      }
      //else if left is equal to right (default to left)
      else
      {
        swap(parentIndex,LeftChild(parentIndex));
        parentIndex = LeftChild(parentIndex);
      }
    }
    else if(LeftChild(parentIndex) <= size)
    {  
       //if left child is greater than parent
      if(comparator(dataItems[parentIndex].getPriority(),dataItems[LeftChild(parentIndex)].getPriority()))
      {
        swap(parentIndex,LeftChild(parentIndex));
        parentIndex = LeftChild(parentIndex);
      }
      else
      {
        return ret;
      }
    }
    else
    {
      return ret;
    }
  }
  return ret;
}
/** @brief Member Function: void Heap<DataType, KeyType, Comparator>::swap(int a, int b)
 * Swaps two items in a heap
 *
 * This function will swap two items in
 * a heap
 *  
 * @param a Index of first item.
 * @param b Index of second item.
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Given a the index of 2 items in the heap
 * @post Swaps the position of these two items in the heap.
 *
 */
template<typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::swap(int a, int b)
{
  DataType temp = dataItems[a];
  dataItems[a] = dataItems[b];
  dataItems[b] = temp;
}
/** @brief Member Function: int Heap<DataType, KeyType, Comparator>::LeftChild(int parent)
 * Returns the index of the left child from a given parent index
 *
 * This function returns index of the
 * left child from a given parent index.
 *  
 * @param parent Index of the parent.
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Given a the index of a parent item in the heap
 * @post Returns the index of its left child.
 *
 */
template<typename DataType, typename KeyType, typename Comparator>
int Heap<DataType, KeyType, Comparator>::LeftChild(int parent)
{
  return 2 * parent + 1;
}
/** @brief Member Function: int Heap<DataType, KeyType, Comparator>::RightChild(int parent)
 * Returns the index of the right child from a given parent index
 *
 * This function returns index of the
 * right child from a given parent index.
 *  
 * @param parent Index of the parent.
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Given a the index of a parent item in the heap
 * @post Returns the index of its right child.
 *
 */
template<typename DataType, typename KeyType, typename Comparator>
int Heap<DataType, KeyType, Comparator>::RightChild(int parent)
{
  return 2 * parent + 2;
}
/** @brief Member Function:int Heap<DataType, KeyType, Comparator>::Parent(int child)
 * Returns the index of the parent from a given child index
 *
 * This function returns index of the
 * parent from a given child index.
 *  
 * @param child Index of the child.
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Given a the index of a child item in the heap
 * @post Returns the index of its parent.
 *
 */
template<typename DataType, typename KeyType, typename Comparator>
int Heap<DataType, KeyType, Comparator>::Parent(int child)
{
  return (child-1) / 2;
}
/** @brief Member Function: void Heap<DataType, KeyType, Comparator>::clear()
 * Clears data from heap.
 *
 * This function will clear the max heap, by setting
 * its size to zero..
 *  
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a max heap.
 * @post clears the heaps data.
 *
 */
template<typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::clear()
{
  size = 0;
}
/** @brief Member Function: bool Heap<DataType, KeyType, Comparator>::isEmpty() const
 * Checks if the heap is empty
 *
 * This function checks if the heap is empty by
 * checking if the size is zero.
 *  
 * @param NONE
 * @return Retruns a boolean, true if the heap is empty, false if it's not.
 * 
 * @exception NONE
 * 
 * @pre Takes a max heap.
 * @post Returns true if the heap is empty and false if not.
 *
 */
template<typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType, KeyType, Comparator>::isEmpty() const
{
  if(size==0)
  {
    return true;
  }
  else
  {
    return false;
  }
}
/** @brief Member Function: bool Heap<DataType, KeyType, Comparator>::isFull() const
 * Checks if the heap is full
 *
 * This function checks if the heap is full by
 * checking if the size equals max size.
 *  
 * @param NONE
 * @return Retruns a boolean, true if the heap is full, false if it's not.
 * 
 * @exception NONE
 * 
 * @pre Takes a max heap.
 * @post Returns true if the heap is full and false if not.
 *
 */
template<typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType, KeyType, Comparator>::isFull() const
{
  if(size==maxSize)
  {
    return true;
  }
  else
  {
    return false;
  }
}
/** @brief Member Function: void Heap<DataType,KeyType,Comparator>:: showStructure () const
 * Shows the heap tree structure.
 *
 * This function shows the structure of
 * a heap using the helper function
 * showSubtree().
 *  
 * @note This function was provided by Dr. Harris.
 *
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a heap.
 * @post Outputs the structure of the heap.
 *
 */
template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: showStructure () const

// Outputs the priorities of the data items in a heap in both array
// and tree form. If the heap is empty, outputs "Empty heap". This
// operation is intended for testing/debugging purposes only.

{
    int j;   // Loop counter

    cout << endl;
    if ( size == 0 )
       cout << "Empty heap" << endl;
    else
    {
       cout << "size = " << size << endl;       // Output array form
       for ( j = 0 ; j < maxSize ; j++ )
           cout << j << "\t";
       cout << endl;
       for ( j = 0 ; j < size ; j++ )
           cout << dataItems[j].getPriority() << "\t";
       cout << endl << endl;
       showSubtree(0,0);                        // Output tree form
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/** @brief Member Function: template < typename DataType, typename KeyType, typename Comparator >
 * Shows the heap tree structure.
 *
 * This function shows the structure of
 * a sub heap.
 *  
 * @note This function was provided by Dr. Harris.
 *
 * @param index Current index of the heap.
 * @param level Current level of the heap.
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes an index and level.
 * @post Outputs the structure of the sub heap.
 *
 */
template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: showSubtree ( int index, int level ) const

// Helper function for the showStructure() function. Outputs the
// subtree (subheap) whose root is stored in dataItems[index]. Argument
// level is the level of this dataItems within the tree.

{
     int j;   // Loop counter

     if ( index < size )
     {
        showSubtree(2*index+2,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )        // Tab over to level
            cout << "\t";
        cout << " " << dataItems[index].getPriority();   // Output dataItems's priority
        if ( 2*index+2 < size )                // Output "connector"
           cout << "<";
        else if ( 2*index+1 < size )
           cout << "\\";
        cout << endl;
        showSubtree(2*index+1,level+1);        // Output left subtree
    }
}
/** @brief Member Function: void Heap<DataType,KeyType,Comparator>::writeLevels() const
 * Writes out the items of a heap based on level.
 *
 * This function will write out the items of a heap
 * based on level.
 *  
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a heap.
 * @post Outputsitems of a heap based on level.
 *
 */
template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>::writeLevels() const
{
  if(isEmpty())
  {
    cout << "Empty heap" << endl;
  }
  else
  {
    int level = 1;
    int levelIndex = 0;
    for(int i=0;i<size;i++)
    {
      if(levelIndex==level)
      {
        cout << endl;
        level*=2;
        levelIndex = 0;
      }
      cout << dataItems[i].getPriority() << " ";
      levelIndex++;
    }
    cout << endl;
  }
}
//

/*
int Heap::remove()
{
  DataType temp = dataItems[0];
  dataItems[0] = dataItems[--size]; 
  int parent = 0;
  while(LeftChild(parent) < size)
  {
    if((dataItems[RightChild(parent)] <= dataItems[LeftChild(parent)] && dataItems[parent] <= dataItems[LeftChild(parent)])
    || (RightChild(parent) >= size && dataItems[parent] <= dataItems[LeftChild(parent)]))
    {
      swap(parent,LeftChild(parent));
      parent = LeftChild(parent);
    }
    else if(RightChild(parent) < size && dataItems[parent] <= dataItems[RighChild(parent)])
    {
      swap(parent,RightChild(parent));
      parent = RightChild(parent);
    }
    else
    {
      return temp;
    }
  }
  return temp;
}
*/


















