/**
 @file Heap.h

 @author Ethan M. Park

 @brief This program is the header file of the Heap
 class which creates a heap

 @version Original Code 1.00 (11/12/2017) - Ethan M. Park
 
 @date Wednesday, November 15, 2017

*/

// Program Description/Support /////////////////////////////////////
/**
 @mainpage
 This program contains the header BSTree.h, which contains
 the definition for the class Heap. This class serves to create a
 max heap. Multiple helper function are used to help with recurssion.

 NOTE: This header file was created using the shell header given in the
 lab folder.
*/

/*
Author self-assessment statement:
This program is complete and working according to spcecifications,
according to the best of my knowledge.
*/

//
// Header Files ///////////////////////////////////////////////////
//
#include <stdexcept>
#include <iostream>
using namespace std;
//
// Precompiler Directives //////////////////////////////////////////
//
#ifndef HEAP_H
#define HEAP_H
//
// Global Constant Definitions ////////////////////////////////////
//
///// NONE
//
// Class Definitions //////////////////////////////////////////////
//
template < typename KeyType=int >
class Less {
  public:
    bool operator()(const KeyType &a, const KeyType &b) const { return a < b; }
};
//
template < typename DataType, typename KeyType=int, typename Comparator=Less<KeyType> >
class Heap
{
  public:

    static const int DEFAULT_MAX_HEAP_SIZE = 10;    // Default maximum heap size

    // Constructor
    Heap ( int maxNumber = DEFAULT_MAX_HEAP_SIZE ); // Default constructor + basic constr
    Heap ( const Heap& other );		    // Copy constructor
    Heap& operator= ( const Heap& other );  // Overloaded assignment operator

    // Destructor
    ~Heap ();

    // Heap manipulation operations
    void insert ( const DataType &newDataItem )    // Insert a data item
        throw ( logic_error );
    DataType remove () throw ( logic_error );  // Remove max priority element
    void clear ();                          // Clear heap

    // Heap status operations
    bool isEmpty () const;                  // Heap is empty
    bool isFull () const;                   // Heap is full

    // Output the heap structure -- used in testing/debugging
    void showStructure () const;

    // Programming exercise #3 operation
    void writeLevels () const;              // Output in level order

  private:

    // Recursive helper of the showStructure() function
    void swap(int a, int b);
    int LeftChild(int parent);
    int RightChild(int parent);
    int Parent(int child);
    void showSubtree ( int index, int level ) const;

    // Data members
    int maxSize,   // Maximum number of elements in the heap
        size;      // Actual number of elements in the heap
    DataType *dataItems; // Array containing the heap elements

    Comparator comparator;
};
//
// Free Function Prototypes ///////////////////////////////////////
//
///// NONE
//
// Class/Data Structure Member Implementation //////////////////////
//
///// NONE
//
//
#endif	//#ifndef HEAP_H
//
