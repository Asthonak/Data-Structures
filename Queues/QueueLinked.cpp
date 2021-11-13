/**
 @file QueueLinked.cpp

 @brief This program contains the methods for a linked list queue.

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
 This program is contains the implementation of QueueLinked.h, a 
 linked list queue.  It contains its constructors, destructor, and
 methods. 

 NOTE: It also contains 1 constructor for the QueueNode Class which
 creates the nodes the linked list uses.
*/
// Precompiler Directives //////////////////////////////////////////
//
//// NONE
//
// Header Files ///////////////////////////////////////////////////
//
#include "QueueLinked.h"
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

/*****************************QueueNode****************************/
// Class/Data Structure Member Implementation //////////////////////
//
template <typename DataType>
/** @brief Member Function:QueueNode(const DataType& nodeData, QueueNode* nextPtr)
 is a constructor for the QueueNode class.
 Initializes the member dataItem to dataItem
 and next to nextPtr.
 Returns nothing.
*/QueueLinked<DataType>::QueueNode::QueueNode(const DataType& nodeData, QueueNode* nextPtr)
{
  next = nextPtr;
  dataItem = nodeData;
}
//
/**************************QueueLinked*****************************/
// Class/Data Structure Member Implementation //////////////////////
//
template <typename DataType>
/** @brief Member Function: QueueLinked(int maxNumber)
 is a constructor for the QueueLinked class.
 Creates an empty queue the size of maxNumber.
 NOTE: Since this is the linked list verson
 the front and back members are simply set to
 NULL.
 Returns nothing.
*/QueueLinked<DataType>::QueueLinked(int maxNumber)
{
  front = NULL;
  back = NULL;
}
template <typename DataType>
/** @brief Member Function: QueueLinked(const QueueLinked& other)
 is a copy constructor for the QueueLinked class.
 First checks if RHS is empty, if it is not it
 creates a new QueueLinked class that has the 
 same content as the other class.
 Returns nothing.
*/QueueLinked<DataType>::QueueLinked(const QueueLinked& other)
{
  if(other.front != NULL)
  {
    QueueNode* temp = other.front;
    front = new QueueNode(temp->dataItem, NULL);
    QueueNode* current = front;
    while(temp!=other.back)
    {
      current->next = new QueueNode(temp->next->dataItem, NULL);
      temp = temp->next;
      current = current->next;
    }
    back = new QueueNode(other.back->dataItem, NULL);
    back=current;
  }
}
template <typename DataType>
/** @brief Member Function:operator=(const QueueLinked& other)
 is an overloaded = operator for the QueueLinked
 class.
 First checks if RHS does not equal the current 
 call and if RHS is not empty, if both are true
 the current class is cleared and the other class
 is copied.
 Returns QueueLinked& if sucessfull.
*/QueueLinked<DataType>& QueueLinked<DataType>::operator=(const QueueLinked& other)
{
  if(front != other.front || other.front != NULL)
  {
    clear();
    QueueNode* temp = other.front;
    QueueNode* current = front;
    while(temp!=other.back)
    {
      current = temp;
      temp = temp->next;
      current = current->next;
    }
    back = other.back;
  }
  return *this;
}
template <typename DataType>
/** @brief Member Function:~QueueLinked()
 is a destructor for the QueueLinked class.
 Uses a while loop to delete all nodes
 in the linked list.
 Returns nothing.
*/QueueLinked<DataType>::~QueueLinked()
{
  QueueNode* current = front;
  while(current!=back)
  {
    QueueNode* temp = current->next;
    delete current;
    current = temp;
  }
  delete back;
}
template <typename DataType>
/** @brief Member Function: enqueue(const DataType& newDataItem) throw (logic_error)
 adds a new node containing newDataItem to 
 the rear of the queue.
 If the queue is full it throws an error.
 Returns nothing.
*/void QueueLinked<DataType>::enqueue(const DataType& newDataItem) throw (logic_error)
{
  if(isFull())
  {
    throw(logic_error("enqueue() queue full"));
  }
  else if(isEmpty())
  {
    QueueNode* temp = new QueueNode(newDataItem, NULL);
    front = temp;
    back = temp;
  }
  else
  {
    back->next = new QueueNode(newDataItem, NULL);
    back = back->next;
  }
}
template <typename DataType>
/** @brief Member Function: dequeue() throw (logic_error)
 removes the first node of the queue and 
 returns its data.
 If the queue is empty it throws an error.
 Returns DataType of sucessful.
*/DataType QueueLinked<DataType>::dequeue() throw (logic_error)
{
  if(isEmpty())
  {
    throw(logic_error("dequeue() queue empty"));
  }
  else if(front==back)
  {
    DataType i = front->dataItem;
    clear();
    return i;
  }
  else
  {
    DataType i = front->dataItem;
    delete front;
    front = front->next;
    return i;
  }
}
template <typename DataType>
/** @brief Member Function: clear()
 uses a while loop to delete all nodes
 in the linked list.
 Returns nothing.
*/void QueueLinked<DataType>::clear()
{
  QueueNode* current = front;
  while(current!=back)
  {
    QueueNode* temp = current->next;
    delete current;
    current = NULL;
    current = temp;
  }
  front = NULL;
  delete front;
  back = NULL;
  delete back;
}
template <typename DataType>
/** @brief Member Function: isEmpty()
 checks if the queue is empty.
 Returns 1 if front is NULL and 0 if
 it is not.
*/bool QueueLinked<DataType>::isEmpty() const
{
  if(front==NULL)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
template <typename DataType>
/** @brief Member Function: isFull()
 checks if the queue is full.
 NOTE: Since this is a linked list
 implementation of a queue this method
 will always return 0.
*/bool QueueLinked<DataType>::isFull() const
{
  return 0;
}
template <typename DataType>
/** @brief Member Function: putFront(const DataType& newDataItem) throw (logic_error)
 adds a new node containing newDataItem to 
 the front of the queue.
 If the queue is full it throws an error.
 Returns DataType of nothing.
*/void QueueLinked<DataType>::putFront(const DataType& newDataItem) throw (logic_error)
{
  if(isFull())
  {
    throw(logic_error("putFront() queue full"));
  }
  if(isEmpty())
  {
    front = new QueueNode(newDataItem, NULL);
    back = front;
  }
  else
  {
    QueueNode *temp = new QueueNode(newDataItem, front);
    front = temp;
  }
}
template <typename DataType>
/** @brief Member Function: getRear() throw (logic_error)
 removes the last node of the queue and 
 returns its data.
 If the queue is empty it throws an error.
 Returns DataType of sucessful.
*/DataType QueueLinked<DataType>::getRear() throw (logic_error)
{
  if(isEmpty())
  {
    throw(logic_error("getRear() queue empty"));
  }
  else if(back==front && back->next==NULL)
  {
    DataType i = back->dataItem;
    clear();
    return i;
  }
  else
  {
    DataType i = back->dataItem;
    QueueNode *current = front;
    QueueNode *temp = back;
    while(current->next!=back){
      current = current->next;
    }
    delete temp;
    back = current;
    back->next = NULL;
    return i;
  }
}
/** @brief Member Function: getLength() const
 gets the length of the queue.
 If the queue is empty it returns 0
 and else it uses a while loop and a counter, i,
 to count nodes, returning i.
*/template <typename DataType>
int QueueLinked<DataType>::getLength() const
{
  if(isEmpty())
  {
    return 0;
  }
  else
  {
    int i = 0;
    QueueNode *current = front;
    while(current!=back)
    {
      i++;
      current = current->next;
    }
    i++;
    return i;
  }
}
template <typename DataType>
/** @brief Member Function: showStructure () const
 outputs the queue.
 NOTE: This code was taken from show7.ccp in the
 lab 7 folder with some slight modifications to
 the template in order to work with this program.
 Returns nothing.
*/void QueueLinked<DataType>:: showStructure () const
// Linked list implementation. Outputs the elements in a queue. If
// the queue is empty, outputs "Empty queue". This operation is
// intended for testing and debugging purposes only.
{
    QueueNode *p;   // Iterates through the queue

    if ( isEmpty() )
	cout << "Empty queue" << endl;
    else
    {
	cout << "Front\t";
	for ( p = front ; p != 0 ; p = p->next )
	{
	    if( p == front ) 
	    {
		cout << '[' << p->dataItem << "] ";
	    }
	    else
	    {
		cout << p->dataItem << " ";
	    }
	}
	cout << "\trear" << endl;
    }
}
//
