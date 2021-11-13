/**
 @file BSTree.cpp

 @author Ethan M. Park

 @brief This program is the implimentation file for a binary
 search tree.

 @version Original Code 1.00 (10/25/2017) - Ethan M. Park
 
 @date Wednesday, October 26, 2017

*/

// Program Description/Support /////////////////////////////////////
/**
 @mainpage
 This program contains the implementation of BSTree.h, which contains
 the definition for the class BSTree and BSTreeNode (a private member
 of the ExprTree class). These classes serve to create a binary search
 tree that sorts data in a way that allows a user to easily find a data
 item with its key. Multiple helper function are used to help with
 recurssion.
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
#include "BSTree.h"
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
/** @brief Member Function: BSTree<DataType,KeyType>::BSTreeNode::BSTreeNode (const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr) : dataItem(nodeDataItem), left(leftPtr), right(rightPtr)
 * A parameterized constructor for the BSTreeNode class.
 *
 * This function will be used to initialize a binary search
 * tree node with initial values.
 *
 * @param nodeDataItem contains the data that will be assigned to the binary search tree node's datatype
 * @param leftPtr pointer to an address that the binary search tree node's left node will point to
 * @param rightPtr pointer to an address that the binary search tree node's right node will point to
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Initializes the binary search tree node with given values.
 *
 */
template < typename DataType, class KeyType > 
BSTree<DataType,KeyType>::BSTreeNode::BSTreeNode (const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr)
{
  dataItem = nodeDataItem;
  left = leftPtr;
  right = rightPtr;
}	
/** @brief Member Function: BSTree<DataType,KeyType>::BSTree () : root(NULL)
 * A default constructor for the BSTree class.
 *
 * This function will set BSTree members to inital value
 *
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Initializes the binary search tree with default values.
 *
 */
template < typename DataType, class KeyType > 
BSTree<DataType,KeyType>::BSTree() : root(NULL)
{
}
/** @brief Member Function: BSTree<DataType,KeyType>::BSTree(const BSTree<DataType,KeyType>& other)
 * A copy constructor for the BSTree class. 
 *
 * This function will be used to initialize the a binary
 * search tree with the values of another tree. Uses the helper
 * helper function copyHelper().
 *
 * @param other Contains the source binary search tree that will be copied
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Initializes the binary search tree node with the values of another binary search tree.
 *
 */
template < typename DataType, class KeyType > 
BSTree<DataType,KeyType>::BSTree(const BSTree<DataType,KeyType>& other)
{
  copyHelper(root, other.root);
}
/** @brief Member Function: BSTree<DataType,KeyType>& BSTree<DataType,KeyType>::operator=(const BSTree<DataType,KeyType>& other)
 * An overloaded assignment operator for the BSTree class.
 *
 * This function will be used to initialize the an binary
 * search tree with the values of another tree. Uses the helper
 * helper function copyHelper().
 *
 * @param other Contains the source binary search tree that will be copied
 * @return BSTree<DataType,KeyType>& Returns the address of the this binary search tree
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Initializes the binary search tree node with the values of another binary search tree.
 *
 */
template < typename DataType, class KeyType > 
BSTree<DataType,KeyType>& BSTree<DataType,KeyType>::operator=(const BSTree<DataType,KeyType>& other)
{
  if(this!=&other)
  {
    clear();
    copyHelper(root, other.root);
  }
  return *this;
}
/** @brief Member Function: void BSTree<DataType,KeyType>::copyHelper(BSTreeNode *&c, const BSTreeNode *o)
 * A helper function for the copy contructor and overloaded assignment operator.
 *
 * This function will be used to initialize the an binary search
 * tree with the values of another tree. In order to achieve this
 * it uses pre-order recurssion to assign each node of the binary search
 * tree the node of the other tree, stoping if the node of the other
 * tree is NULL.
 *
 * @param *&c Points to the address of the current binary search tree node that will be assigned the data of the source node.
 * @param *o Points to the source binary search tree node that will be copied
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a sources node and the node to the current tree.
 * @post Copies the content of source into current.
 *
 */
template < typename DataType, class KeyType > 
void BSTree<DataType,KeyType>::copyHelper(BSTreeNode *&c, const BSTreeNode *o)
{
  if(o != NULL)
  {
    c = new BSTreeNode(o->dataItem, NULL, NULL);
    copyHelper(c->left, o->left);
    copyHelper(c->right, o->right);
  }
}
/** @brief Member Function: BSTree<DataType,KeyType>::~BSTree()
 * The destructor for the BSTree class.
 *
 * This function will be used to deallocate each node in the
 * tree usinig the clear() method.
 *
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes an binary search tree.
 * @post Deletes the data and of the binary search tree.
 *
 */
template < typename DataType, class KeyType > 
BSTree<DataType,KeyType>::~BSTree()
{
  clear();
}
/** @brief Member Function: void BSTree<DataType,KeyType>::insert(const DataType& newDataItem)
 * Inserts an item into the binary search tree
 *
 * This function will take in an a data item and insert
 * the item in the correct spot on the tree depending on
 * on the value of its key compared to other keys in the
 * tree. Uses the helper function insertHelper()
 *  
 * @param newDataItem Data item that will be inserted into the tree.
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Tree is does not contain data item.
 * @post Data item is in proper position in tree.
 *
 */
template < typename DataType, class KeyType > 
void BSTree<DataType,KeyType>::insert(const DataType& newDataItem)
{
  insertHelper(root, newDataItem);
}
/** @brief Member Function: void ExprTree<DataType>::void BSTree<DataType,KeyType>::insertHelper(BSTreeNode *&ptr, const DataType& data)
 * Inserts an item into the binary search tree
 *
 * This function will take in an a data item and insert
 * the item in the correct spot on the tree depending on
 * on the value of its key compared to other keys in the
 * tree. Uses recurssion and if statements to
 * navigate the tree and insert the data in the correct
 * position
 *  
 * @param *&ptr A pointer to the address of the current binary search tree node in the tree
 * @param data Data item that will be inserted into the tree.
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes data.
 * @post If the node is NULL the data is inserted.
 *
 */
template < typename DataType, class KeyType >
void BSTree<DataType,KeyType>::insertHelper(BSTreeNode *&ptr, const DataType& data)
{
  if(ptr == NULL)
  {
    ptr = new BSTreeNode(data, NULL, NULL);
    return;
  }
  else if(ptr->dataItem.getKey() > data.getKey())
  {
    insertHelper(ptr->left, data);
  }
  else if(ptr->dataItem.getKey() < data.getKey())
  {
    insertHelper(ptr->right, data);
  }
  else if(data.getKey() == (ptr->dataItem.getKey()))
  {
    ptr->dataItem = data;
    return;
  }
}
/** @brief Member Function: bool BSTree<DataType,KeyType>::retrieve(const KeyType& searchKey, DataType& searchDataItem) const
 * Finds and returns a data item in the binary search tree
 *
 * This function finds and returns a data item in the
 * binary search tree returning true if it finds a
 * data item that matches the key and false if not.
 * Uses the helper function retrieveHelper().
 *  
 * @param &searchKey Key that the data item must match
 * @param &searchDataItem Used to retrieve the data
 * @return Returns true if it retrieved the data item and false if not.
 * 
 * @exception NONE
 * 
 * @pre Takes a key and variable to retrieve data.
 * @post Sets variable if key match is found.
 *
 */
template < typename DataType, class KeyType >
bool BSTree<DataType,KeyType>::retrieve(const KeyType& searchKey, DataType& searchDataItem) const
{
  return retrieveHelper(root, searchKey, searchDataItem);
}
/** @brief Member Function: bool BSTree<DataType,KeyType>::retrieveHelper(BSTreeNode *ptr, const KeyType& key, DataType& data) const
 * Navigates binary search tree and retrieves data.
 *
 * This function will find and return a data item in the
 * binary search tree if its key matches the given key.
 * Uses recurssion and if statements to
 * navigate the tree and check if the keys are equal.
 *  
 * @param *&ptr A pointer to the address of the current binary search tree node in the tree
 * @param &key Key that the data item must match
 * @param &data Used to retrieve the data
 * @return Returns true if it retrieved the data item and false if not.
 * 
 * @exception NONE
 * 
 * @pre Takes a key and variable to retrieve data.
 * @post Sets variable if key match is found.
 *
 */
template < typename DataType, class KeyType >
bool BSTree<DataType,KeyType>::retrieveHelper(BSTreeNode *ptr, const KeyType& key, DataType& data) const
{
  if(ptr==NULL)
  {
    return 0;
  }
  else if(ptr->dataItem.getKey() == key)
  {
    data = ptr->dataItem;
    return 1;
  }
  else if(ptr->dataItem.getKey() > key)
  {
    retrieveHelper(ptr->left, key, data);
  }
  else if(ptr->dataItem.getKey() < key)
  {
    retrieveHelper(ptr->right, key, data);
  }
}
/** @brief Member Function: bool BSTree<DataType,KeyType>::remove(const KeyType& deleteKey)
 *
 * This function will find an item in the binary search
 * tree that matches a given key and remove this item
 * from the tree. Uses the helper function removeHelper()
 *  
 * @param &deleteKey Key that will be used to remove item.
 * @return Returns true if it can remove the item and false if not.
 * 
 * @exception NONE
 * 
 * @pre Given a key.
 * @post Deletes item from tree that matches key.
 *
 */
template < typename DataType, class KeyType >
bool BSTree<DataType,KeyType>::remove(const KeyType& deleteKey)
{
  return removeHelper(root, deleteKey);
}
/** @brief Member Function: bool BSTree<DataType,KeyType>::removeHelper(BSTreeNode *&ptr, const KeyType& key)
 * Deletes an item from the binary search tree
 *
 * This function will find an item in the binary search
 * tree that matches a given key and remove this item
 * from the tree. Uses  recurssion and if statements to
 * navigate the tree and delete the node if the item matches
 * the key
 *  
 * @param *&ptr A pointer to the address of the current binary search tree node in the tree
 * @param key Key that will be used to remove item.
 * @return Returns true if it can remove the item and false if not.
 * 
 * @exception NONE
 * 
 * @pre Given a key.
 * @post Deletes node if key matches data item.
 *
 */
template < typename DataType, class KeyType >
bool BSTree<DataType,KeyType>::removeHelper(BSTreeNode *&ptr, const KeyType& key)
{
  if(ptr==NULL)
  {
    return 0;
  }
  else if(ptr->dataItem.getKey() > key)
  {
    removeHelper(ptr->left, key);
  }
  else if(ptr->dataItem.getKey() < key)
  {
    removeHelper(ptr->right, key);
  }
  else if(ptr->dataItem.getKey() == key)
  {
    if(ptr->left == NULL && ptr->right == NULL)
    {
      delete ptr;
      ptr = NULL;
      return true;
    }
    else if(ptr->left != NULL && ptr->right == NULL)//only need to do ptr->left check
    {
      BSTreeNode *temp = ptr;
      ptr = ptr->left;
      delete temp;
      return true;
    }
    else if(ptr->left == NULL && ptr->right != NULL)//only need to do ptr->left check
    {
      BSTreeNode *temp = ptr;
      ptr = ptr->right;
      delete temp;
      return true;
    }
    else if(ptr->left != NULL && ptr->right != NULL) //can turn this into an else
    {
      BSTreeNode *temp = ptr->left;
      while(temp->right!=NULL)
      {
        temp = temp->right;
      }
      ptr->dataItem = temp->dataItem;
      removeHelper(ptr->left, ptr->dataItem.getKey());
      return true;
    }
  }
}
/** @brief Member Function: void BSTree<DataType,KeyType>::writeKeys () const
 * Writes out the keys of the binary serach tree.
 *
 * This function will write out the keys of the 
 * binary search tree in acending order. Uses the
 * helper function writeHelper().
 *  
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Outputs keys of binary search tree.
 *
 */
template < typename DataType, class KeyType >
void BSTree<DataType,KeyType>::writeKeys () const
{
  writeHelper(root);
  cout << endl;
}
/** @brief Member Function: void BSTree<DataType,KeyType>::writeHelper(BSTreeNode *ptr) const
 * Writes out keys of the binary serach tree.
 *
 * This function will write out the keys of the 
 * binary search tree in acending order. Uses 
 * in-order recurssion to output the keys in 
 * acending order, stoping if the node is NULL.
 *  
 * @param *ptr A pointer to the address of the current binary search tree node in the tree
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Outputs keys of binary search tree.
 *
 */
template < typename DataType, class KeyType >
void BSTree<DataType,KeyType>::writeHelper(BSTreeNode *ptr) const
{
  if(ptr!=NULL)
  {
    writeHelper(ptr->left);
    cout << (ptr->dataItem).getKey() << " ";
    writeHelper(ptr->right);
  }
}
/** @brief Member Function: void BSTree<DataType,KeyType>::clear()
 * Deletes the data of an binary search tree.
 *
 * This function will delete the binary search tree, by
 * deallocating each node and setting its pointers to
 * NULL. Uses the helper function clearHelper().
 *  
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a binary search tree.
 * @post Deletes the trees data.
 *
 */
template < typename DataType, class KeyType > 
void BSTree<DataType,KeyType>::clear()
{
    if (!isEmpty())
    {
       clearHelper(root);
    }
}
/** @brief Member Function: void BSTree<DataType,KeyType>::clearHelper(BSTreeNode *&ptr)
 * Deletes the data of a node of an binary search tree.
 *
 * This function will delete the binary search tree, by
 * deallocating each node and setting its pointers to
 * NULL. It deletes each node individually using post-order
 * recurssion, stopping if the pointer is already NULL.
 *  
 * @param *&ptr A pointer to the address of the current binary search tree node in the tree
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes an binary search tree node.
 * @post Deletes the nodes data.
 *
 */
template < typename DataType, class KeyType > 
void BSTree<DataType,KeyType>::clearHelper(BSTreeNode *&ptr)
{
  if(ptr!=NULL)
  {
    clearHelper(ptr->left);
    clearHelper(ptr->right);
    delete ptr;
    ptr = NULL;
  }
}

/** @brief Member Function: bool BSTree<DataType,KeyType>::isEmpty () const
 * Checks if the binary search tree is empty
 *
 * This function checks if the binary search tree
 * is empty by checking if the root node is NULL.
 *  
 * @param NONE
 * @return Retruns a boolean, true if the tree is empty, false if it's not.
 * 
 * @exception NONE
 * 
 * @pre Takes a binary search tree.
 * @post Returns true if the tree is empty and false if not.
 *
 */
template < typename DataType, class KeyType > 
bool BSTree<DataType,KeyType>::isEmpty () const
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
/** @brief Member Function: void BSTree<DataType,KeyType>:: showStructure () const
 * Shows the binary search tree structure.
 *
 * This function shows the structure of
 * and binary search tree using the helper
 * function showHelper().
 *  
 * @note This function was provided by Dr. Harris.
 *
 * @param NONE
 * @return Returns true if the tree is empty and fakse if not.
 * 
 * @exception NONE
 * 
 * @pre Takes an binary search tree.
 * @post Outputs the structure of the tree.
 *
 */
template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: showStructure () const

// Outputs the keys in a binary search tree. The tree is output
// rotated counterclockwise 90 degrees from its conventional
// orientation using a "reverse" inorder traversal. This operation is
// intended for testing and debugging purposes only.

{
    if ( root == 0 )
       cout << "Empty tree" << endl;
    else
    {
       cout << endl;
       showHelper(root,1);
       cout << endl;
    }
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/** @brief Member Function: void ExprTree<DataType>:: void ExprTree<DataType>:: void BSTree<DataType,KeyType>:: showHelper ( BSTreeNode *p, int level) const
 *
 * This function shows the structure of
 * and binary search tree using pre-order
 * recursion to output each node, stopping
 * when the given node is NULL
 *  
 * @note This function was provided by Dr. Harris.
 *
 * @param *p A pointer to a node in the binary search tree.
 * @param level Indicates what level of the tree the function has reached
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes an binary search tree node.
 * @post Outputs the structure of the node.
 *
 */
template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: showHelper ( BSTreeNode *p, int level) const

// Recursive helper for showStructure. 
// Outputs the subtree whose root node is pointed to by p. 
// Parameter level is the level of this node within the tree.

{
     int j;   // Loop counter

     if ( p != 0 )
     {
        showHelper(p->right,level+1);         // Output right subtree
        for ( j = 0 ; j < level ; j++ )    // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem.getKey();   // Output key
        if ( ( p->left != 0 ) &&           // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);          // Output left subtree
    }
}
/** @brief Member Function: int BSTree<DataType,KeyType>::getHeight() const
 * Gets the height of the binary search tree.
 *
 * Gets the height of a binary search tree. Uses
 * the helper funtion getHeightHelper().
 *  
 * @param NONE
 * @return Retruns the height of the tree
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Retruns the height of the tree.
 *
 */
template < typename DataType, typename KeyType >
int BSTree<DataType,KeyType>::getHeight() const
{
  int height = 0;
  int level = 0;
  getHeightHelper(root,height,level);
  return height;
}
/** @brief Member Function: int BSTree<DataType,KeyType>::getHeightHelper(BSTreeNode *ptr, int &h ,int &l) const
 * Gets the height of the binary search tree.
 *
 * Gets the height of a binary search tree using
 * recurssion and backtracing to find the highest
 * level of the tree.
 *  
 * @param *ptr A pointer to the address of the current binary search tree node in the tree
 * @param &h Current max height of the tree
 * @param *&l Current level of the tree
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Returns the height of the tree.
 *
 */
template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>::getHeightHelper(BSTreeNode *ptr, int &h ,int &l) const
{
  if(ptr!=NULL)
  {
    l++;
    if(l>h)
    {
      h = l;
    }
    getHeightHelper(ptr->left,h,l);
    l--;
    getHeightHelper(ptr->right,h,l);
    l--;
  }
}
/** @brief Member Function: int BSTree<DataType,KeyType>::getCount() const
 * Gets the height of the binary search tree.
 *
 * Gets the number of nodes in the binary
 * search tree. Uses the helper funtion
 * getCountHelper().
 *  
 * @param NONE
 * @return Returns number of nodes in the tree
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Returns the height of the tree.
 *
 */
template < typename DataType, typename KeyType >
int BSTree<DataType,KeyType>::getCount() const
{
  int count=0;
  getCountHelper(root, count);
  return count;
}
/** @brief Member Function: void BSTree<DataType,KeyType>::getCountHelper(BSTreeNode *ptr, int &c) const
 * Gets the height of the binary search tree.
 *
 * Gets the number of nodes in the binary
 * search tree. Uses preorder recursion to
 * count each node, stoping if a node is
 * NULL
 *  
 * @param *ptr A pointer to the address of the current binary search tree node in the tree
 * @param &c Holds the number of nods in the tree
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Returns the number of nodes in the tree.
 *
 */
template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>::getCountHelper(BSTreeNode *ptr, int &c) const
{
  if(ptr!=NULL)
  {
    c++;
    getCountHelper(ptr->left,c);
    getCountHelper(ptr->right,c);
  }
}
//
