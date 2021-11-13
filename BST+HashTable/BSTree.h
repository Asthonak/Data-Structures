/**
 @file BSTree.h

 @author Ethan M. Park

 @brief This program is the header file of the BSTree
 class which creates a binary search tree

 @version Original Code 1.00 (10/25/2017) - Ethan M. Park
 
 @date Wednesday, October 26, 2017

*/

// Program Description/Support /////////////////////////////////////
/**
 @mainpage
 This program contains the header BSTree.h, which contains
 the definition for the class BSTree and BSTreeNode (a private member
 of the ExprTree class). These classes serve to create a binary search
 tree that sorts data in a way that allows a user to easily find a data
 item with its key. Multiple helper function are used to help with
 recurssion.

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
#ifndef BSTREE_H
#define BSTREE_H
//
// Global Constant Definitions ////////////////////////////////////
//
///// NONE
//
// Class Definitions //////////////////////////////////////////////
//
template < typename DataType, class KeyType >    // DataType : tree data item
class BSTree                                     // KeyType : key field
{
  public:

    // Constructor
    BSTree ();                         // Default constructor
    BSTree ( const BSTree<DataType,KeyType>& other );   // Copy constructor
    BSTree& operator= ( const BSTree<DataType,KeyType>& other );
						  // Overloaded assignment operator

    // Destructor
    ~BSTree ();

    // Binary search tree manipulation operations
    void insert ( const DataType& newDataItem );  // Insert data item
    bool retrieve ( const KeyType& searchKey, DataType& searchDataItem ) const;
                                                  // Retrieve data item
    bool remove ( const KeyType& deleteKey );            // Remove data item
    void writeKeys () const;                      // Output keys
    void clear ();                                // Clear tree

    // Binary search tree status operations
    bool isEmpty () const;                        // Tree is empty
    // !! isFull() has been retired. Not very useful in a linked structure.

    // Output the tree structure -- used in testing/debugging
    void showStructure () const;

    // In-lab operations
    int getHeight () const;                       // Height of tree
    int getCount () const;			  // Number of nodes in tree
    void writeLessThan ( const KeyType& searchKey ) const; // Output keys < searchKey

  protected:

    class BSTreeNode                  // Inner class: facilitator for the BSTree class
    {
      public:
    
        // Constructor
        BSTreeNode ( const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr );

        // Data members
        DataType dataItem;         // Binary search tree data item
        BSTreeNode *left,    // Pointer to the left child
                   *right;   // Pointer to the right child
    };

    // Recursive helpers for the public member functions -- insert
    // prototypes of these functions here.
    void copyHelper(BSTreeNode *&c, const BSTreeNode *o);
    void insertHelper(BSTreeNode *&ptr, const DataType& data);
    bool retrieveHelper(BSTreeNode *ptr, const KeyType& key, DataType& data) const;
    bool removeHelper(BSTreeNode *&ptr, const KeyType& key);
    void writeHelper(BSTreeNode *ptr) const;
    void clearHelper(BSTreeNode *&ptr);
    void showHelper      ( BSTreeNode *p, int level ) const;
    void getHeightHelper(BSTreeNode *ptr, int &h ,int &l) const;
    void getCountHelper(BSTreeNode *ptr, int &c) const;


    // Data member
    BSTreeNode *root;   // Pointer to the root node
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
#endif	// define BSTREE_H
//
