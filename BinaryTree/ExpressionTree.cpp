/**
 @file ExpressionTree.cpp

 @author Ethan M. Park

 @brief This program is the implimentation file of the ExprTree
 class which creates and solves an expression using a binary tree
 taking in the expression in prefix notation.

 @version Original Code 1.00 (10/08/2017) - Ethan M. Park
 
 @date Wednesday, October 8, 2017

*/

// Program Description/Support /////////////////////////////////////
/**
 @mainpage
 This program contains the implementation of ExpressionTree.h, which
 contains class definition for the class ExprTree as well as the class
 ExprTreeNode (a private member of the ExprTree class). These classes
 serve to create and solve an expression using a binary tree. It reads
 in the expression in prefix notation and builds a hierarchical structure
 that represents the expression, transaltes the input into infix notation,
 and solves the expression. It also can copy an expression, commute an
 expression, and compare 2 expressions. Multiple helper function are
 used to help with recurssion.
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
#include "ExpressionTree.h"
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
/** @brief Member Function: ExprTree<DataType>::ExprTreeNode::ExprTreeNode(char elem, ExprTreeNode *leftPtr, ExprTreeNode *rightPtr)
 * A parameterized constructor for the ExprTreeNode class.
 *
 * This function will be used to initialize the an expression
 * tree node with initial values.
 *
 * @param elem contains the data that will be assigned to the tree node's datatype
 * @param leftPtr pointer to an address that the expression tree node's left node will point to
 * @param rightPtr pointer to an address that the expression tree node's right node will point to
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Initializes the expression tree node with given values.
 *
 */
template <typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode(char elem, ExprTreeNode *leftPtr, ExprTreeNode *rightPtr)
: dataItem(elem), left(leftPtr), right(rightPtr)
{
}
/** @brief Member Function: ExprTree<DataType>::ExprTree()
 * A default constructor for the ExprTree class.
 *
 * This function will set ExprTree members to inital value
 *
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Initializes the expression tree node with default values.
 *
 */
template <typename DataType>
ExprTree<DataType>::ExprTree() : root(NULL)
{
}
/** @brief Member Function: ExprTree<DataType>::ExprTree(const ExprTree& source) *leftPtr, ExprTreeNode *rightPtr)
 * A copy constructor for the ExprTreeNode class. 
 *
 * This function will be used to initialize the an expression
 * tree with the values of another tree. Uses the helper
 * function copyHelper().
 *
 * @param source Contains the source expression tree that will be copied
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Initializes the expression tree node with the values of another expression tree.
 *
 */
template <typename DataType>
ExprTree<DataType>::ExprTree(const ExprTree& source)
{
  copyHelper(root, source.root);
}
/** @brief Member Function: ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree& source)
 * An overloaded assignment operator for the ExprTreeNode class.
 *
 * This function will be used to initialize the an expression
 * tree with the values of another tree. Uses the helper
 * function copyHelper().
 *
 * @param source Contains the source expression tree that will be copied
 * @return ExprTree<DataType>& Returns the address of the this expression tree
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Initializes the expression tree node with the values of another expression tree.
 *
 */
template <typename DataType>
ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree& source)
{
  if(this!=&source)
  {
    clear();
    copyHelper(root, source.root);
  }
  return *this;
}
/** @brief Member Function: void ExprTree<DataType>::copyHelper(ExprTreeNode *&c, const ExprTreeNode *s)
 * A helper function for the copy contructor and overloaded assignment operator.
 *
 * This function will be used to initialize the an expression
 * tree with the values of another tree. In order to achieve this
 * it uses pre-order recurssion to assign each node of the expression
 * tree the node of the other tree, stoping if the node of the other
 * tree is NULL.
 *
 * @param *s Points to the source expression tree node that will be copied
 * @param *&c Points to the address of the current expression tree node that will be assigned the data of the source node.
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a sources node and the node to the current tree.
 * @post Copies the content of source into current.
 *
 */
template <typename DataType>
void ExprTree<DataType>::copyHelper(ExprTreeNode *&c, const ExprTreeNode *s)
{
  if(s != NULL)
  {
    ExprTreeNode *left = NULL;
    ExprTreeNode *right = NULL;
    copyHelper(left, s->left);
    copyHelper(right, s->right);
    c = new ExprTreeNode(s->dataItem, left, right);
  }
}
/** @brief Member Function: ExprTree<DataType>::~ExprTree()
 * The destructor for the ExprTree class.
 *
 * This function will be used to deallocate each node in the
 * tree usinig the clear() method.
 *
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes an expression tree.
 * @post Deletes the data and of the expression tree.
 *
 */
template <typename DataType>
ExprTree<DataType>::~ExprTree()
{
  clear();
}
/** @brief Member Function: void ExprTree<DataType>::build()
 * A builds an expression tree with user input
 *
 * This function will take in an prefix expression and build
 * a hierarchical expression tree. Uses the helper function
 * buildHelper()
 *  
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Tree is uninitialized.
 * @post Tree is built with prefix expression given by the user.
 *
 */
template <typename DataType>
void ExprTree<DataType>::build()
{
  buildHelper(root);
}
/** @brief Member Function: void ExprTree<DataType>::buildHelper(ExprTreeNode *&ptr)
 * A builds an expression tree with user input
 *
 * This function will take in an prefix expression and build
 * a hierarchical expression tree. Uses pre-order recurssion 
 * to initialize values, stopping if the input is not an operator
 * (+, -, *, or /)
 *  
 * @param *&ptr A pointer to the address of the current expression tree node in the tree
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes an unitialized tree node.
 * @post Initializes the tree node.
 *
 */
template <typename DataType>
void ExprTree<DataType>::buildHelper(ExprTreeNode *&ptr)
{
  char c;
  cin >> c;
  ptr = new ExprTreeNode(c, NULL, NULL);
  if((c <= '0' && c >= '9') && (c != '+' || c != '-' || c != '*' || c != '/'))
  {
    cout << "Error: invalid input" << endl;
  }
  else if(c == '+' || c == '-' || c == '*' || c == '/')
  {
    buildHelper(ptr->left);
    buildHelper(ptr->right);
  }
}
/** @brief Member Function: void ExprTree<DataType>::expression() const
 * Transalates a expression tree.
 *
 * This function transalates a expression tree and converts
 * it to a infix expression using the helper function
 * expressionHelper().
 *  
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes an expression tree node.
 * @post Outputs the infix expression of the tree.
 *
 */
template <typename DataType>
void ExprTree<DataType>::expression() const
{
  expressionHelper(root);
}
/** @brief Member Function: void ExprTree<DataType>::expressionHelper(ExprTreeNode *ptr) const
 * Interprets a given node and outputs a value to that
 * contributes to the building of an infix expression that
 * an expression represents
 *
 * This function will take in a node containing data,
 * interpret the data, and choose and apprprate output
 * that will make an infix expression from an expression
 * tree. It does this using in-order recurssion stoping
 * if the data is an character representing an integer
 * 1-9.
 *  
 * @param *ptr A pointer to the current expression tree node in the tree
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a tree node.
 * @post Interprets the data and outputs based on its interpretation.
 *
 */
template <typename DataType>
void ExprTree<DataType>::expressionHelper(ExprTreeNode *ptr) const
{
  if(ptr->dataItem >= '0' && ptr->dataItem <= '9')
  {
    cout << ptr->dataItem;
  }
  else
  {
    cout << "(";
    expressionHelper(ptr->left);
    cout << ptr->dataItem;
    expressionHelper(ptr->right);
    cout << ")";
  }
}
/** @brief Member Function: DataType ExprTree<DataType>::evaluate() const throw (logic_error)
 * Evaluates an expression tree.
 *
 * This function will evaluate and solve and expression
 * tree using the helper function evaluateHelper().
 *  
 * @param NONE
 * @return DataType Returns the solution to the expression given by the expression tree.
 * 
 * @exception The expression tree cannot be empty.
 * 
 * @pre Takes a tree node.
 * @post Returns the solution to the expression given by the expression tree.
 *
 */
template <typename DataType>
DataType ExprTree<DataType>::evaluate() const throw (logic_error)
{
  if(isEmpty())
  {
    throw(logic_error("evaluate() tree empty"));
  }
  return evaluateHelper(root);
}
/** @brief Member Function: DataType ExprTree<DataType>::evaluateHelper(ExprTreeNode *ptr) const
 * Evaluates an expression tree.
 *
 * This function will evaluate and solve and expression
 * tree using post-order recurssion, stoping if the data
 * item is not an operator (+, -, *, or /), as well as a
 * switch statement to determine if this is the case.
 *  
 * @param *ptr A pointer to the current expression tree node in the tree
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a tree node.
 * @post Calculates the portion of the expression tree and returns it.
 *
 */
template <typename DataType>
DataType ExprTree<DataType>::evaluateHelper(ExprTreeNode *ptr) const
{
  switch(ptr->dataItem)
  {
    case '-' : return(evaluateHelper(ptr->left) - evaluateHelper(ptr->right));
               break;
    case '+' : return(evaluateHelper(ptr->left) + evaluateHelper(ptr->right));
               break;
    case '/' : return(evaluateHelper(ptr->left) / evaluateHelper(ptr->right));
               break;
    case '*' : return(evaluateHelper(ptr->left) * evaluateHelper(ptr->right));
               break;
    default  : DataType i = ptr->dataItem - '0';
               return i;
               break;
  }
}
/** @brief Member Function: DataType ExprTree<DataType>::void ExprTree<DataType>::clear()
 * Deletes the data of an expression tree.
 *
 * This function will delete the expression tree, by
 * deallocating each node and setting its pointers to
 * NULL.
 *  
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes an expression tree.
 * @post Deletes the trees data.
 *
 */
template <typename DataType>
void ExprTree<DataType>::clear()
{
    if (!isEmpty())
    {
       clearHelper(root);
    }
}

/** @brief Member Function: void ExprTree<DataType>::clearHelper(ExprTreeNode *&ptr)
 * Deletes the data of a node of an expression tree.
 *
 * This function will delete the expression tree, by
 * deallocating each node and setting its pointers to
 * NULL. It deletes each node individually using post-order
 * recurssion, stopping if the pointer is already NULL.
 *  
 * @param *&ptr A pointer to the address of the current expression tree node in the tree
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes an expression tree node.
 * @post Deletes the nodes data.
 *
 */
template <typename DataType>
void ExprTree<DataType>::clearHelper(ExprTreeNode *&ptr) //post-order
{
  if(ptr!=NULL)
  {
    clearHelper(ptr->left);
    clearHelper(ptr->right);
    delete ptr;
    ptr = NULL;
  }
}

/** @brief Member Function: bool ExprTree<DataType>::isEmpty() const
 * Checks if the expression tree is empty
 *
 * This function checks if the expression tree
 * is empty by checking if the root node is NULL.
 *  
 * @param NONE
 * @return Retruns a boolean, true if the tree is empty, false if it's not.
 * 
 * @exception NONE
 * 
 * @pre Takes a expression tree.
 * @post Returns true if the tree is empty and false if not.
 *
 */
template <typename DataType>
bool ExprTree<DataType>::isEmpty() const
{
  if(root == NULL)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
/** @brief Member Function: void ExprTree<DataType>::commute()
 * This function commutes an expression tree.
 *
 * This function commutes an expression tree,
 * swtitching the the postions of the operands
 * for each operator, using the helper function
 * commuteHelper().
 *  
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a expression tree.
 * @post Commutes the expression tree.
 *
 */
template <typename DataType>
void ExprTree<DataType>::commute()
{
  commuteHelper(root);
}
/** @brief Member Function: void ExprTree<DataType>::commute()
 * This function commutes an expression tree.
 *
 * This function commutes an expression tree,
 * swtitching the the postions of the operands
 * for each operator, using pre-order recurssion,
 * stopping if the data of a given node is not
 * and operation (+, -, *, /).
 *  
 * @param *&ptr A pointer to the address of the current expression tree node in the tree
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes an expression tree node.
 * @post Commutes the portion of the tree if the data is an operation.
 *
 */
template <typename DataType>
void ExprTree<DataType>::commuteHelper(ExprTreeNode *&ptr)//preorder
{
  if(ptr!=NULL)
  {
    if(ptr->dataItem == '+' || ptr->dataItem == '-' || ptr->dataItem == '*' || ptr->dataItem == '/')
    {
      ExprTreeNode *temp = ptr->left;
      ptr->left = ptr->right;
      ptr->right = temp;
    }
    commuteHelper(ptr->left);
    commuteHelper(ptr->right);
  }
}
/** @brief Member Function: bool ExprTree<DataType>::isEquivalent(const ExprTree& source) const
 * Checks if two expression trees are equivalent.
 *
 * This function takes two expression trees and
 * checks if they are equal using the helper
 * function isEquivalentHelper().
 *  
 * @param source Contains the source expression tree that the current tree will be compared to.
 * @return Retruns true if the trees are equivalent, and false if not
 * 
 * @exception NONE
 * 
 * @pre Takes two expression trees.
 * @post Retruns true if the trees are equivalent, and false if not
 *
 */
template <typename DataType>
bool ExprTree<DataType>::isEquivalent(const ExprTree& source) const
{
  if(isEmpty() && source.isEmpty())
  {
    return 1;
  }
  else
  {
    return isEquivalentHelper(root, source.root);
  }
}
/** @brief Member Function: bool ExprTree<DataType>::isEquivalentHelper(ExprTreeNode *current, ExprTreeNode *source) const
 * Checks if two expression tree nodes are equivalent.
 *
 * This function takes two expression trees and
 * checks if they are equal using pre-order
 * recurssion to check each node of the trees
 * stopping if the current nodes are NULL.
 *  
 * @param current A pointer to a node in the current expression tree.
 * @param source A pointer to a node in the source expression tree.
 * @return Retruns true if the nodes are equivalent, and false if not
 * 
 * @exception NONE
 * 
 * @pre Takes two expression trees.
 * @post Retruns true if the nodes are equivalent, and false if not
 *
 */
template <typename DataType>
bool ExprTree<DataType>::isEquivalentHelper(ExprTreeNode *current, ExprTreeNode *source) const
{
  if(current == NULL && source == NULL)
  {
        return 1;
  }
  else if(current != NULL && source != NULL)
  {
    if(current->dataItem == source->dataItem)
    {
      if(isEquivalentHelper(current->left, source->left) && isEquivalentHelper(current->right, source->right))
      {
        return 1;
      }
      else if(isEquivalentHelper(current->left, source->right) && isEquivalentHelper(current->right, source->left))
      {
        if(source->dataItem == '*' || source->dataItem == '+')
        {
          return 1;
        }
        else
        {
          return 0;
        }
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  else  
  {
    return 0;
  }
}
/** @brief Member Function: void ExprTree<DataType>:: showStructure () const ExprTreeNode *source) const
 * Shows the expression tree structure.
 *
 * This function shows the structure of
 * and expression tree using the helper
 * function showHelper().
 *  
 * @note This function was provided by Dr. Harris.
 *
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes an expression tree.
 * @post Outputs the structure of the tree.
 *
 */
template <typename DataType>
void ExprTree<DataType>:: showStructure () const

// Outputs an expression tree. The tree is output rotated counter-
// clockwise 90 degrees from its conventional orientation using a
// "reverse" inorder traversal. This operation is intended for testing
// and debugging purposes only.

{
    if ( isEmpty() )
       cout << "Empty tree" << endl;
    else
    {
       cout << endl;
       showHelper(root,1);
       cout << endl;
    }
}
/** @brief Member Function: void ExprTree<DataType>:: void ExprTree<DataType>:: showHelper ( ExprTreeNode *p, int level ) const
 *
 * This function shows the structure of
 * and expression tree using pre-order
 * recursion to output each node, stopping
 * when the given node is NULL
 *  
 * @note This function was provided by Dr. Harris.
 *
 * @param *p A pointer to a node in the expression tree.
 * @param level Indicates what level of the tree the function has reached
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes an expression tree node.
 * @post Outputs the structure of the node.
 *
 */
template <typename DataType>
void ExprTree<DataType>:: showHelper ( ExprTreeNode *p, int level ) const

// Recursive helper for the showStructure() function. Outputs the
// subtree whose root node is pointed to by p. Parameter level is the
// level of this node within the expression tree.

{
     int j;   // Loop counter

     if ( p != 0 )
     {
        showHelper(p->right,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )   // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem;        // Output dataItem
        if ( ( p->left != 0 ) &&          // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);         // Output left subtree
     }
}
//
