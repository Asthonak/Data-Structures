/**
 @file database.cpp

 @author Ethan M. Park

 @brief This program simulates a data base and uses the BSTree
 class to organize the database and find/output specific 
 account IDs.

 @version Original Code 1.00 (10/08/2017) - Ethan M. Park
 
 @date Wednesday, October 8, 2017

*/

// Program Description/Support /////////////////////////////////////
/**
 @mainpage
 This program builds a binary search tree index for the account
 records in the text file accounts.dat. It contains the struct
 A IndexEntry to facilitate the building of the tree and the class
 AccountRecord to hold the account records of an individual record
 in the data base.

 NOTE: This header file was created using the shell program given in the
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
#include <iostream>
#include <fstream>
#include "BSTree.cpp"
using namespace std;
//
// Precompiler Directives //////////////////////////////////////////
//
///// NONE
//
// Global Constant Definitions ////////////////////////////////////
//
const int nameLength      = 11;   // Maximum number of characters in
                                  //   a name
const long bytesPerRecord = 38;   // Number of bytes used to store
                                  //   each record in the accounts
                                  //   database file
//--------------------------------------------------------------------
// Structs ////////////////////////////////////
struct AccountRecord
{
    int acctID;                   // Account identifier
    char firstName[nameLength],   // Name of account holder
         lastName[nameLength];
    double balance;               // Account balance
};
//--------------------------------------------------------------------
//
// Declaration specifying the database index
//

struct IndexEntry
{
    int acctID;              // (Key) Account identifier
    long recNum;             // Record number

    int getKey () const
        { return acctID; }   // Return key field
};
//--------------------------------------------------------------------
// Main Function ////////////////////////////////////
int main ()
{
    ifstream acctFile ("accounts.dat");   // Accounts database file
    AccountRecord acctRec;                // Account record
    BSTree<IndexEntry,int> index;         // Database index
    IndexEntry entry;                     // Index entry
    int searchID;                         // User input account ID
    long recNum;                          // Record number

    // Iterate through the database records. For each record, read the
    // account ID and add the (account ID, record number) pair to the
    // index.
    string skip;
    for(recNum=0;acctFile.good();recNum++)
    {
      acctFile >> entry.acctID;
      entry.recNum = recNum;
      index.insert(entry);
      acctFile >> skip >> skip >> skip;
    }

    // Output the account IDs in ascending order.

    cout << endl << "Account IDs :" << endl;
    index.writeKeys();
    cout << endl;

    // Clear the status flags for the database file.

    acctFile.clear();
    acctFile.close();
    acctFile.open("accounts.dat");

    // Read an account ID from the keyboard and output the
    // corresponding record.
    cout << "Enter account ID : ";
    while(cin >> searchID)
    {
      if(index.retrieve(searchID, entry))
      {
          for(int i=0;i<=entry.recNum;i++)
          {
              acctFile >> acctRec.acctID;
              acctFile >> acctRec.firstName >> acctRec.lastName;
              acctFile >> acctRec.balance;
          }

          cout << entry.recNum << " : ";
          cout << acctRec.acctID << " " << acctRec.firstName << " ";
          cout << acctRec.lastName << " ";
          cout << acctRec.balance;
      }
      else
      {
        cout << "No record with that account ID";
      }

     acctFile.clear();
     acctFile.close();
     acctFile.open("accounts.dat");

     cout << endl << "Enter account ID (EOF to quit): ";
    }
}
//
