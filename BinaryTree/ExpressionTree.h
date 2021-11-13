/**
 @file ExpressionTree.h

 @author Ethan M. Park

 @brief This program is the header file of the ExprTree
 class which creates and solves an expression using a binary tree
 taking in the expression in prefix notation.

 @version Original Code 1.00 (10/08/2017) - Ethan M. Park
 
 @date Wednesday, October 8, 2017

*/

// Program Description/Support /////////////////////////////////////
/**
 @mainpage
 This program contains the header of ExpressionTree.h, which
 contains class definition for the class ExprTree as well as the class
 ExprTreeNode (a private member of the ExprTree class). These classes
 serve to create and solve an expression using a binary tree. It reads
 in the expression in prefix notation and builds a hierarchical structure
 that represents the expression, transaltes the input into infix notation,
 and solves the expression. It also can copy an expression, commute an
 expression, and compare 2 expressions. Multiple helper function are
 used to help with recurssion.

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
#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H
//
// Global Constant Definitions ////////////////////////////////////
//
///// NONE
//
// Class Definitions //////////////////////////////////////////////
//
template <typename DataType>
class ExprTree {
  public:

    ExprTree ();
    ExprTree(const ExprTree& source);

    ExprTree& operator=(const ExprTree& source);

    ~ExprTree ();

    void build ();
    void expression () const;
    DataType evaluate() const throw (logic_error);
    void clear ();           
    void commute();
    bool isEquivalent(const ExprTree& source) const;

    void showStructure () const;

    bool isEmpty() const;


  private:

    class ExprTreeNode {
      public:
        ExprTreeNode ( char elem, ExprTreeNode *leftPtr, ExprTreeNode *rightPtr );

        char dataItem;
        ExprTreeNode *left, *right;

    };

    void copyHelper(ExprTreeNode *&c, const ExprTreeNode *s);
    void clearHelper(ExprTreeNode *&ptr);
    void buildHelper(ExprTreeNode *&ptr);
    void expressionHelper(ExprTreeNode *ptr) const;
    DataType evaluateHelper(ExprTreeNode *ptr) const;
    void commuteHelper(ExprTreeNode *&ptr);
    bool isEquivalentHelper(ExprTreeNode *current, ExprTreeNode *source) const;

    void showHelper ( ExprTreeNode *p, int level ) const;
    // Data member
    ExprTreeNode *root;   // Pointer to the root node
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
#endif		// #ifndef EXPRESSIONTREE_H
//
