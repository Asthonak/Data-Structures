/**
 @file HashTable.cpp

 @author Ethan M. Park

 @brief This program is the implimentation file for a hash
 table.

 @version Original Code 1.00 (11/4/2017) - Ethan M. Park
 
 @date Wednesday, Novemeber 6, 2017

*/

// Program Description/Support /////////////////////////////////////
/**
 @mainpage
 This program contains the implementation of HashTable.h, which contains
 the definition for the class HashTable. These classes serve to create a
 hash table that creates an index of binary searsch trees. It uses a 
 single helper function to help the copy constructor and the overloaded
 assignment operator.
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
#include "HashTable.h"
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
/** @brief Member Function: HashTable<DataType,KeyType>::HashTable(int initTableSize) : tableSize(initTableSize)
 * A default constructor for the HashTable class.
 *
 * This function will set HashTable members to inital values
 *
 * @param initTableSize sets the table size to an initial value
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Initializes the binary search tree with default values.
 *
 */
template <typename DataType, typename KeyType>
HashTable<DataType,KeyType>::HashTable(int initTableSize) : tableSize(initTableSize)
{
  dataTable = new BSTree<DataType,KeyType>[initTableSize];
}
/** @brief Member Function: HashTable& HashTable<DataType,KeyType>::operator=(const HashTable& other)
 * A copy constructor for the HashTable class. 
 *
 * This function will be used to initialize the a hash table
 * with the values of another table. Uses the helper
 * function copyTable().
 *
 * @param other Contains the source hash table that will be copied
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Initializes the hash table with the values of another hash table.
 *
 */
template <typename DataType, typename KeyType>
HashTable<DataType,KeyType>::HashTable(const HashTable& other)
{
  copyTable(other);
}
/** @brief Member Function: HashTable& HashTable<DataType,KeyType>::operator=(const HashTable& other)
 * An overloaded assignment operator for the HashTable class.
 *
 * This function will be used to initialize the a hash table
 * with the values of another table. Uses the helper
 * function copyTable().
 *
 * @param other Contains the source hash table that will be copied
 * @return HashTable<DataType,KeyType>& Returns the address of the this hash table
 * 
 * @exception NONE
 * 
 * @pre NONE
 * @post Initializes the hash table with the values of another hash table.
 *
 */
template <typename DataType, typename KeyType>
HashTable<DataType,KeyType>& HashTable<DataType,KeyType>::operator=(const HashTable& other)
{
  if(this != &other)
  {
    clear();
    copyTable(other);
  }
  return *this;
}
/** @brief Member Function: void copyTable(const HashTable& source)
 * A helper function for the copy contructor and overloaded assignment operator.
 *
 * This function first sets the table size of the current
 * to the value of the source and dynamically allocates the
 * data table to fit this size. It then navigates the indexes
 * seting each binary tree in each index of the current
 * equal to the source.
 *
 * @param &source Contains the source hash table that will be copied;
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a source hash table.
 * @post Sets the current hash table equal to the source.
 *
 */
template <typename DataType, typename KeyType>
void HashTable<DataType,KeyType>::copyTable(const HashTable& source)
{
  tableSize = source.tableSize;
  dataTable = new BSTree<DataType,KeyType>[tableSize];
  for(int i=0;i<tableSize;i++)
  {
    dataTable[i] = source.dataTable[i];
  }
}
/** @brief Member Function: HashTable<DataType,KeyType>::~HashTable()
 * The destructor for the HashTable class.
 *
 * This function will be used to delete the hash table
 * usinig the clear() method.
 *
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a hash table.
 * @post Delete the hash table.
 *
 */
template <typename DataType, typename KeyType>
HashTable<DataType,KeyType>::~HashTable()
{
  clear();
  delete [] dataTable;
  dataTable = NULL;
}
/** @brief Member Function: void HashTable<DataType,KeyType>::insert(const DataType& newDataItem)
 * Inserts an item into the binary search tree
 *
 * This function will take in an a data item and insert
 * the item in the correct index in the hash table using
 * the hash() and the BSTree insert() functions.
 *  
 * @param newDataItem Data item that will be inserted into the table.
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Table is does not contain data item.
 * @post Data item is in proper position in table.
 *
 */
template <typename DataType, typename KeyType>
void HashTable<DataType,KeyType>::insert(const DataType& newDataItem)
{
  int i = newDataItem.hash(newDataItem.getKey()) % tableSize;
  dataTable[i].insert(newDataItem);
}
/** @brief Member Function: bool HashTable<DataType,KeyType>::remove(const KeyType& deleteKey)
 * Inserts an item into the binary search tree
 *
 * This function will find an item in the hash table
 * that matches a given key and remove this item from
 * the table using the hash() and the BSTree insert()
 * functions.
 *  
 * @param &deleteKey Key that will be used to remove item.
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Given a key.
 * @post Deletes item from the table that matches key.
 *
 */
template <typename DataType, typename KeyType>
bool HashTable<DataType,KeyType>::remove(const KeyType& deleteKey)
{
  for(int i=0;i<tableSize;i++)
  {
    if(dataTable[i].remove(deleteKey))
    {
      return true;
    }
  }
  return false;
}
/** @brief Member Function: bool HashTable<DataType,KeyType>::retrieve(const KeyType& searchKey, DataType& returnItem) const
 * Finds and returns a data item in the hash table
 *
 * This function finds and returns a data item in the
 * hash table returning true if it finds a
 * data item that matches the key and false if not.
 * Uses the hash() and the BSTree insert() functions.
 *  
 * @param &searchKey Key that the data item must match
 * @param &searchDataItem Used to retrieve the data
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a key and variable to retrieve data.
 * @post Sets variable if key match is found.
 *
 */
template <typename DataType, typename KeyType>
bool HashTable<DataType,KeyType>::retrieve(const KeyType& searchKey, DataType& returnItem) const
{
  int i = returnItem.hash(searchKey) % tableSize;
  return dataTable[i].retrieve(searchKey,returnItem);
}
/** @brief Member Function: void HashTable<DataType,KeyType>::clear()
 * Deletes the data of a hash table.
 *
 * This function will delete a hash table, by
 * by iterating though its index and using BSTree
 * clear() to clear each binary search tree. It
 * then deletes the array representing the data table.
 *  
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a hash table.
 * @post Deletes the table's data.
 *
 */
template <typename DataType, typename KeyType>
void HashTable<DataType,KeyType>::clear()
{
  for(int i=0;i<tableSize;i++)
  {
     dataTable[i].clear();
  }
}
/** @brief Member Function: bool HashTable<DataType,KeyType>::isEmpty() const
 * Checks if the hash table is empty
 *
 * This function checks if the hash table is
 * empty by iterating through the index
 * returning true if all binary search trees
 * are empty and false if not.
 *  
 * @param NONE
 * @return Retruns a boolean, true if the tree is empty, false if it's not.
 * 
 * @exception NONE
 * 
 * @pre Takes a hash table.
 * @post Returns true if the table is empty and false if not.
 *
 */
template <typename DataType, typename KeyType>
bool HashTable<DataType,KeyType>::isEmpty() const
{
  for(int i=0;i<tableSize;i++)
  {
     if(!dataTable[i].isEmpty())
     {
       return false;
     }
  }
  return true;
}
/** @brief Member Function:void HashTable<DataType, KeyType>::showStructure() const
 * Shows the hash table structure.
 *
 * This function shows the structure of
 * a hash table.
 *  
 * @note This function was provided by Dr. Harris.
 *
 * @param NONE
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes a hash table.
 * @post Outputs the structure of the table.
 *
 */
template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::showStructure() const {
    for (int i = 0; i < tableSize; ++i) {
	cout << i << ": ";
	dataTable[i].writeKeys();
    }
}
//
