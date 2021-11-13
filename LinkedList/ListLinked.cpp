/*
Name: ListLinked.cpp
Purpose: This program contains the implemntation of methods within the List and ListNode classes.
Author: Ethan M. Park
*/

#include "ListLinked.h"

using namespace std;

/*************************************ListNode**************************************/

/*PARA CONSTRUCTOR*/
template <typename DataType>
List<DataType>::ListNode::ListNode(const DataType& nodeData, ListNode* nextPtr){
  next = nextPtr;
  dataItem = nodeData;
}

/***************************************List****************************************/

/*DEFAULT CONSTRUCTOR*/
template <typename DataType>
List<DataType>::List(int ignored){
  head = NULL;
  cursor = NULL;
}

/*COPY CONSTRUCTOR*/
template <typename DataType>
List<DataType>::List(const List& other){
  if(other.head != NULL){
    ListNode* temp = other.head;
    head = new ListNode(temp->dataItem, NULL);
    ListNode* current = head;
    while(1){
      if(current->next==NULL){
        break;
      }
      current->next = new ListNode(temp->dataItem, NULL);
      temp = temp->next;
      current = current->next;
    }
    cursor = other.cursor;
  }
}

/*This method sets the members of the current class equal to another, using dynamic memory allocation, a while loop, and memory address manipulation*/
template <typename DataType>
List<DataType>& List<DataType>::operator=(const List& other){
  if(head != other.head || other.head != NULL){
    ListNode* temp = other.head;
    head = new ListNode(temp->dataItem, NULL);
    ListNode* current = head;
    while(1){
      if(current->next==NULL){
        break;
      }
      current->next = new ListNode(temp->dataItem, NULL);
      temp = temp->next;
      current = current->next;
    }
  }
  return *this;
}

/*DESTRUCTOR*/
template <typename DataType>
List<DataType>::~List(){
  ListNode* current = head;
  while(current!=0){
    ListNode *temp = current->next;
    delete current;
    current = temp;
  }
}

/*This method adds a node to the list after the cursor using dynamic memory allocation, memory address manipulation, and a series of if statments.*/
template <typename DataType>
void List<DataType>::insert(const DataType& newDataItem) throw (logic_error){
  if(isFull()){
    throw(logic_error("insert() full list"));
  }
  else if(isEmpty()){
    head = new ListNode(newDataItem, NULL);
    cursor = head;
  }
  else if(cursor->next!=NULL){
    ListNode *temp = new ListNode(newDataItem, cursor->next);
    cursor->next = temp;
    cursor = temp;
  }
  else{
    ListNode *temp = new ListNode(newDataItem, NULL);
    cursor->next = temp;
    gotoNext();
  }
}

/*This method removes the node that the cursor is pointing to using dynamic memory allocation, memory address manipulation, and a series of if statments.*/
template <typename DataType>
void List<DataType>::remove() throw (logic_error){
  if(isEmpty()){
    throw(logic_error("remove() empty list"));
  }
  else if(cursor==head && head->next==NULL){
    delete head; //clear
    head = NULL;
  }
  else if(cursor==head){
    gotoNext();
    delete head;
    head = cursor;
  }
  else if(cursor->next == NULL){
    ListNode *temp = cursor;
    gotoPrior();
    delete temp;
    cursor->next = NULL;
    gotoBeginning();
  }
  else{
    ListNode *temp = cursor;
    gotoPrior();
    cursor->next = temp->next;
    delete temp;
    cursor = cursor->next;
  }
}

/*This method replaces a the data of a node of the cursor with a new set of data.*/
template <typename DataType>
void List<DataType>::replace(const DataType& newDataItem) throw (logic_error){
  if(isEmpty()){
    throw(logic_error("replace() empty list."));
  }
  else{
    cursor->dataItem = newDataItem;
  }
}


/*This method clears the list using dynamic memory allocation, memory address manipulation, and a while loop.*/
template <typename DataType>
void List<DataType>::clear(){
  gotoBeginning();
  while(cursor!=NULL){
    ListNode *temp = cursor->next;
    delete cursor;
    cursor = temp;
  }
  delete head;
  head = NULL;
}

/*This method checks if the list is empty using if statments.*/
template <typename DataType>
bool List<DataType>::isEmpty() const{
  if(head==NULL){
    return 1;
  }
  else{
    return 0;
  }
}

/*This method checks if the list is full using if statments.*/
template <typename DataType>
bool List<DataType>::isFull() const{
  return 0;
}

/*This method moves the cursor to the begining of the list using memory address manipulation and if statments.*/
template <typename DataType>
void List<DataType>::gotoBeginning() throw (logic_error){
  if(isEmpty()){
    throw(logic_error("gotoBeginning() empty list"));
  }
  else{
    cursor = head;
  }
}

/*This method moves the cursor to the begining of the list using memory address manipulation, a while loop, and if statments.*/
template <typename DataType>
void List<DataType>::gotoEnd() throw (logic_error){
  if(isEmpty()){
    throw(logic_error("gotoEnd() empty list"));
  }
  else{
    while(cursor->next!=NULL){
      gotoNext();
    }
  }
}

/*This method moves the cursor to the end of the list using memory address manipulation, a while loop, and if statments.*/
template <typename DataType>
void List<DataType>::moveToBeginning () throw (logic_error){
  if(isEmpty()){
    throw(logic_error("moveToBeginning() empty list"));
  }
  if(cursor!=head){
    ListNode *temp = new ListNode(cursor->dataItem, head);
    head = temp;
    remove();
    gotoBeginning();
  }
}

/*This method inserts a node before the cursor using dynamic memory allocation, memory address manipulation, and a series of if statments.*/
template <typename DataType>
void List<DataType>::insertBefore(const DataType& newDataItem) throw (logic_error){
  if(isFull()){
    throw(logic_error("insertBefore() full list"));
  }
  /*************************************************************************************/
  if(isEmpty()){
    head = new ListNode(newDataItem, NULL);
    cursor = head;
  }
  else if(cursor==head){
    ListNode *temp = new ListNode(newDataItem, head);
    head = temp;
    cursor = head;
  }
  else{
    ListNode *temp = new ListNode(newDataItem, NULL);
    gotoPrior();
    temp->next = cursor->next;
    cursor->next = temp;
    cursor = temp->next;
  }
}

/*This method moves the cursor to the next node using memory address manipulation and a series of if statments.*/
template <typename DataType>
bool List<DataType>::gotoNext() throw (logic_error){
  if(isEmpty()){
    throw(logic_error("gotoNext() empty list."));
  }
  else if(cursor->next!=NULL){
    cursor = cursor->next;
    return 1;
  }
  else{
    return 0;
  }
}

/*This method moves the cursor to the previous node using memory address manipulation, a while loop, and a series of if statments.*/
template <typename DataType>
bool List<DataType>::gotoPrior() throw (logic_error){
  if(isEmpty()){
    throw(logic_error("gotoPrior() empty list."));
  }
  else if(cursor!=head){
    ListNode *temp = cursor;
    gotoBeginning();
    while(cursor->next!=temp){
      gotoNext();
    }
    return 1;
  }
  else{
    return 0;
  }
}

/*This method returns the data of the node pointed to by the cursor.*/
template <typename DataType>
DataType List<DataType>::getCursor() const throw (logic_error){
  if(isEmpty()){
    throw(logic_error("getCursor() empty list"));
  }
  else{
    return cursor->dataItem;
  }
}

/*NOTE: This code was taken from show5.ccp in the lab 5 folder.*/
template <typename DataType>
void List<DataType>::showStructure() const{
// Outputs the items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing and
// debugging purposes only.
  if ( isEmpty() ){
    cout << "Empty list" << endl;
  }
  else{
    for (ListNode* temp = head; temp != 0; temp = temp->next){
      if (temp == cursor){
        cout << "[";
      }

      // Assumes that dataItem can be printed via << because
      // is is either primitive or operator<< is overloaded.
      cout << temp->dataItem;

      if (temp == cursor){
        cout << "]";
      }
      cout << " ";
    }
    cout << endl;
  }
}
