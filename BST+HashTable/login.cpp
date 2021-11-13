/**
 @file login.cpp

 @author Ethan M. Park

 @brief This program stores usernames and passwords as well
 as allows users to enter usernames and passwords and authenticates
 information entered by the user.

 @version Original Code 1.00 (11/05/2017) - Ethan M. Park
 
 @date Wednesday, Novemeber 6, 2017

*/

// Program Description/Support /////////////////////////////////////
/**
 @mainpage
 This program takes usernames and passwords from an input file and stores
 as well this infomation into a hash table. It then allows users to enter
 usernames and passwords and authenticates information entered by the user
 stoping if user input EOF.
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
#include <iostream>
#include <fstream>
#include "HashTable.cpp"
using namespace std;
//
// Global Constant Definitions ////////////////////////////////////
//
///// NONE
//
// Class Definitions //////////////////////////////////////////////
//
class Login
{
  public:
    void setUsername(const string &u);
    void setPassword(const string &p);
    string getKey() const;
    string getPassword() const;
    static unsigned int hash(const string& str);

  private:
    string username, password;
};
//
// Free Function Prototypes ///////////////////////////////////////
//
///// NONE
//
// Class/Data Structure Member Implementation //////////////////////
//
/** @brief Member Function: void Login::setUsername(const string &u) : username(u)
 * Intitialzes the username.
 *
 * This function intitialzes the username
 * by seting it to the string passed to
 * the function.
 *
 * @param &u string that the username will be set to
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes Login class.
 * @post Sets it's username to the passed in string.
 *
 */
void Login::setUsername(const string &u)
{
  username = u;
}
/** @brief Member Function: void Login::setPassword(const string &p) : password(p)
 * Intitialzes the password.
 *
 * This function intitialzes the password
 * by seting it to the string passed to
 * the function.
 *
 * @param &p string that the password will be set to
 * @return NONE
 * 
 * @exception NONE
 * 
 * @pre Takes Login class.
 * @post Sets it's password to the passed in string.
 *
 */
void Login::setPassword(const string &p)
{
  password = p;
}
/** @brief Member Function: string Login::getUsername() const
 * Gets the username.
 *
 * This function gets the username.
 *
 * @param NONE
 * @return returns the username member
 * 
 * @exception NONE
 * 
 * @pre Takes Login class.
 * @post Returns the username member.
 *
 */
string Login::getKey() const
{
  return username;
}
/** @brief Member Function: string Login::getPassword() const
 * Gets the username.
 *
 * This function gets the password.
 *
 * @param NONE
 * @return returns the password member
 * 
 * @exception NONE
 * 
 * @pre Takes Login class.
 * @post Returns the password member.
 *
 */
string Login::getPassword() const
{
  return password;
}
/** @brief Member Function: unsigned int Login::hash(const string& str)
 * The hash function for the hash table.
 *
 * @note This function was provided by Dr. Harris.
 *
 * @param NONE
 * @return returns the hash index for the string
 * 
 * @exception NONE
 * 
 * @pre Takes a string.
 * @post Returns the hash index for the string.
 *
 */
unsigned int Login::hash(const string& str) {
    unsigned int val = 0;

    for (int i = 0; i < str.length(); ++i) {
	val += str[i];
    }

    return val;
}
//
// Main Function ///////////////////////////////////////////////
//
int main()
{
  HashTable<Login, string> data(8);
  Login temp;
  string user, pass;
  ifstream inputFile("password.dat");
  
  inputFile >> user;
  while(inputFile.good())
  {
    inputFile >> pass;
    temp.setUsername(user);
    temp.setPassword(pass);
    data.insert(temp);
    inputFile >> user;
  }

  data.showStructure();

  cout << "Login: ";
  while(cin >> user)
  {
    cout << "Password: ";
    cin >> pass;
    if(data.retrieve(user,temp))
    {
      if(pass == temp.getPassword())
      {
        cout << "Authentication successful" << endl;
      }
      else
      {
        cout << "Authentication failure" << endl;
      }
    }
    else
    {
      cout << "Authentication failure" << endl;
    }
    cout << "Login: ";
  }

  return 0;
}
//
