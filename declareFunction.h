/****************************************************************************
*		This file using for declare all the function from this project
*****************************************************************************/

#include "structure.h"
#define CLEAR_ESCAPE "\e[1;1H\e[2J" // for skip display the previous character 

/* to create a line between command */
void drawLine();

/************************************************************************** 
 *                           Main fucntion
 **************************************************************************/

/* This function will display an option for the user to choose to log in.
 * If the user selects outside of the selection range, it will send an error message.
 * Return: 0 when out of range option, Return 1 when select in range option.
 */
int accountMenu();

/************************************************************************** 
 *                           Login fucntion
 **************************************************************************/

/* This function will login to program from user.
 * Users are required to enter a username and password to login.
 * If the username or password of the user cannot be found in the 
 * database, will send message error.
 * Arguments:
 *    pRootNode -  First node of tree
 * Return: 4 if login success, 0 if login fail
 */
USER_T* login(USER_T* pRootNode);

/* This function checks for the format of the username, 
 * whether there are special characters or not.
 * Arguments:
 *      username   - The username entered by the user
 * Return 0 when the data has special characters, 
 * Return 1 when the data does not contain special characters.
 */
int checkFormat(char username[]);

/************************************************************************** 
 *                           Registor fucntion
 **************************************************************************/

/* This function is the main part of the registration operation.
 * If the file cannot be opened successfully, it will be closed.
 * When validating each item entered from a user has been successfully 
 * verified, the program will write all the information to the database.
 */
void regist();

/* This function checks the name from the user's enter.
 * If the name format is incorrect, an error message will be sent.
 * If the name entered is correct, the system will save.
 */
void enterName();

/* This function checks the username from the user's enter.
 * If the username format is incorrect, it will send an error message.
 * The username must be unique to any other user. If a username is 
 * detected same other, it will send a error message.
 * If the username entered is correct, the system will save.
 */
void enterUsername();

/* This function checks the password from the user's enter.
 * If the password format is incorrect, it will send an error message.
 * The password must be entered both letters and numbers.
 * If the password entered is correct, the system will save.
 * Return: return 0 when the data has wrong format, return 1 when the data correctly.
 */
int enterPassword();

/************************************************************************** 
 *                           Validation fucntion
 **************************************************************************/

/* This function verifies that the data is all characters and 
 * verifies that the first character is uppercase. 
 * Arguments:
 *      input   - The data entered by the user
 * Return 0 when the data is not a letter, Return -1 when the first 
 * character is not uppercase, Return 1 when the data is a letter.
 */
int checkAlpha(char input[]);

/* This function checks if the data contains special characters in the data 
 * contain special characters.
 * Arguments:
 *      input   - The data entered by the user
 * Return 0 when the data has special characters, Return 1 when the data does not
 */
int checkSpecific(char input[]);

/* This function checks if the username has more than or less than determined.
 * Arguments:
 *      username   - The username entered by the user
 * Return 0 when the data is less than 6 or more than 16 characters, 
 * Return 1 when the data does not exceed the number of characters allowed.
 */
int lenghtUsername(char username[]);

/* This function checks if the password has more than or less than determined.
 * Arguments:
 *      password   - The password entered by the user
 * Return 0 when the data is less than 8 or more than 16 characters, 
 * Return 1 when the data does not exceed the number of characters allowed.
 */
int lenghtPassword(char password[]);

/* This function checks if the data has space.
 * Arguments:
 *      input   - The data entered by the user
 * Return 0 when the data has space, Return 1 when the data does not space.
 */
int checkSpace(char input[]);

/* This function checks if username has found in the database.
 * Compare the information between the user entered and 
 * the information in the database, where data is read from the file.
 * If there is the same username in the database, it will send an error message to user.
 * Arguments:
 *      user   - The username entered by the user
 * Return 0 when the data has space, Return 1 when the data does not space.
 */
int checkUniqueUsername();

/* This function checks if the data contains only numbers.
 * Arguments:
 *      password   - The password entered by the user
 * Return 0 when there are numbers in the data, 
 * Return 1 when there are no numbers in the data.
 */
int checkAllDigit(char password[]);

/* This function checks if the data contains only alphabets. 
 * Arguments:
 *      password   - The password entered by the user
 * Return 0 when there are alphabets in the data,
 * Return 1 when there are no alphabets in the data.
 */
int checkAllAlpha(char password[]);

/************************************************************************** 
 *                          Search fucntion
 **************************************************************************/

/*  This function for call all function to linked list the data
*   insert to hash table and search
*   Argument : 
*       currentuser  - user that is currently logged in
*       purchaselist - list that hold all book user purchased
*   Returns :
*       list of books that was purchased as BOOKLIST_T
*/
BOOKLIST_T* searchSystem(USER_T* currentuser, BOOKLIST_T* purchaselist);

/*  This function will let the user search the book by
*   each attribute. This function will lookup first to see
*   that inputted from the user is in the hash table or not
*   After that, if it has we will list all the bookList() to 
*   let the user select the book
*   Arguments
*       prompt      -   command print set such as search by author, search by ______
*       category    -   attribute of book
*       currentuser -   current user that is logged in
*       purchaselist-   list of book user has purchased
*/
BOOKLIST_T* search(char* prompt, int category, USER_T* currentUser, BOOKLIST_T* purchaselist);

/* to display infomation of book 
*     Argument:
*       book    -   hold all the information's book
*/
void displayBook(BOOK_T* book);

/* print all the book from the list
 * ask to select a book and return the book data
 * Argument : list of book, countData
 * Return: a book info
 */ 
BOOK_T* printFoundBook(LIST_HANDLE list, int countData);

/* Based on code by Sally Goldin from [Lab8: hashDictionary.c]
 * - Used with permission.
 * Robust hash function that uses bitwise operations to
 * modify string values. Adapted from Kyle Loudon,
 * "Mastering Algorithms with C"
 */
unsigned int bitwiseOpHash(char* key);

/************************************************************************** 
 *                          Purchase fucntion
 **************************************************************************/

/* Provide option to purchase or not
 * if yes, then it will add the book to your cart
 *   Argument : 
 *              Book - to add to cart
 *              List - to holds the purchased books
 *              User - that is currently logged in
 *  return: the list of book you purchased so far
 */
BOOKLIST_T* purchaseOption(BOOK_T* book, BOOKLIST_T* purchaselist,USER_T* currentuser);

/* Take book and add to the end of the list of purchased book 
 *   Argument : 
 *              book         - book information 
 *              purchaselist - list of purchased books
 *              currentuser  - user information
 *   Return: purchaselist that create/insert to list
 */
BOOKLIST_T* purchaseBook(BOOK_T* book, BOOKLIST_T* purchaselist, USER_T* currentuser);

/* Traverse the purchaselist, call function to record, write into the file
 * then, prints out all the book that purchased
 *   Argument : 
 *             purchase - hold the list structure that store bookList of purchased
 *             user     - current user that login to system
 */
void checkout(BOOKLIST_T* purchase, USER_T* user);

/* This function will let user select the book that got recommend by content or community
 * in main function. After that, will let user purchase book that user like to buy
 *   Argument : 
 *             recommendlist - hold the list structure which got recommend by content/community
 *             currentUser   - current user that login to system
 *             purchaselist  - list of book that user purchased
 *   Return : list of purchased book
 */
BOOKLIST_T* purchaseMain(BOOKLIST_T* recommendlist, USER_T* currentUser, BOOKLIST_T* purchaselist);

/************************************************************************** 
 *                        Recommend Book fucntion
 **************************************************************************/

/* Simple function to get a random number
 *      Argument : 
 *          count - the maximum number that will be randomized from zero
 * Return : random - a random number within the given range
 */ 
int randomNo(int count);

/* A function to pick a random book with record from a list
 *  Argument: 
 *          purchaselist - a list of purchased book to be randomly picked
 * Return : book[] - return a random book
 */ 
BOOK_T* getRandomBook(BOOKLIST_T* purchaselist);

/* A function to pick a random user with record from a list
 *  Argument: 
 *          book        - a book with record to pick randomized user from
 *          currentUser - user that is currently logged in
 * Return : user[random position] - return a random user
 */ 
USER_T* getRandomUser(BOOK_T* book, USER_T* currentUser);

/*  Recommend the book by community base
 *  this function will create a list to hold all the book that record by user that randomizes
 *    Argument:
 *          purchaselist - lsit of book that have been purchased
 *          currentUsere - user that is currently logged in
 *  Return: recommendlist - list that hold the book
 */
BOOKLIST_T* communityBase(BOOKLIST_T* purchaselist, USER_T* currentUser);

/*  find the same book in the list if it is
 *  will counting to similarityScore
 *      Argument
 *          similarList  - list of book that similar to book purchased
 *          temp         - structure of book hold information
 *  Return 1 if count, 0 if not count
 */
int sameBook(LIST_HANDLE similarList, BOOK_T* temp);

/*  Thie function will lookup to hash table that have this book or not
 *  then counting each book to find most similar book
 *      Argument
 *          similarList  - list of book that similar to book purchased
 *          attribute    - attribute of book which are 2, 3, 4
 *          buffer       - word's each attribute to lookupf
 *          book         - structure of book hold information
 */
void similarityScore(LIST_HANDLE similarList, int attribute, char *buffer, BOOK_T* book, USER_T* currentUser);

/*  Thie function will separate each word's attribute
 *  and copy to buffer then will sent to similartyScore() function
 *  to couting
 *      Argument
 *          similarList  - list of book that similar to book purchased
 *          attribute    - attribute of book which are 2, 3, 4
 *          book         - structure of book hold information
 *          currentUser  - user that is currently logged in
 */
void separateWord(LIST_HANDLE similarList, int attribute, BOOK_T* book, USER_T* currentUser);

/*  Recommend the book by content base
 *  This function will random book in purchaselist as a base book then will 
 *  convert every attribute to lower string then sent to other function 
 *  to find most similarity score to recommend to user
 *    Argument:
 *          purchaselist - list of book that have been purchased
 *          currentUser  - user that is currently logged in
 *  Return: the most similar book
 */
BOOK_T* contentBase(BOOKLIST_T* purchaselist, USER_T* currentUser);

/************************************************************************** 
 *                        Data management fucntion
 **************************************************************************/

/* Find a person with a name that matches 'name'.
 *    userName        -    userName that we finding
 *    pCurrent        -    userName in file
 * Return: the pointer to the person desired, or NULL if no match.
 */
USER_T * findUser(char* usernameSearch, USER_T* pCurrent);

/* Traverse a tree (post order traversal) and execute to
 * free each leftChild node and rightChild node
 * Argument
 *    pCurrent                -   current node
 * freeNode(recursive) function to execute on each node
 */
void freeNode(USER_T* pCurrent);

/* Recursive function to insert a node into 
 * the tree using the smaller-left, larger-right rule.
 * Assumes that the passed current node is not NULL.
 * Also assumes no two 'name' values will be equal.
 * Arguments:
 *    currentNode -  Current location in the tree
 *    newNode     -  New node to insert
 */
void insertNode(USER_T* currentNode, USER_T* newNode);

/* Read the database file and create a binary tree to log in.
 * Data from reading will be copied to the data structure for use.
 * Once read and copied successfully, it will be sent to the login.
 * If the file does not open successfully, it will send 
 * a message to the user.
 */
USER_T* createBinaryTree();

/*  This function using for build the bookList to keep data
*   into the linkedlist and insert data to the hash table
*/
void buildBookList();

/* A simple function to add user to book's record
 *      Argument : 
 *          user    -   user that is currently logged in
 *          book    -   book to record user in there
 */
void addToBookList(USER_T* user, BOOK_T* book);

/* A simple function to check if book already has user on the list
 *      Argument : 
 *          user    -   user that is currently logged in
 *          book    -   structure's book which hold information
 *      
 * Return : 0 for not on list and 1 for already on list
 */
int alreadyhaveUser(USER_T* user, BOOK_T* book);

/* A simple function to add book to user's record
 *      Argument :
 *          user    -   user that is currently logged in
 *          book    -   book which hold information
 */
void addToUserList(USER_T* user, BOOK_T* book);

/* A simple function to check if user already has book on the list
 *      Argument: 
 *          user    -   user that is currently logged in
 *          book    -   book which hold information
 * Return : 0 for not on list and 1 for already on list
 */
int alreadyBought(USER_T* user, BOOK_T* book);

/*   This function read the recordlist.txt and set up the
*    list 'record'
*    Argument
*       pRootNode - root node of the tree
*/
void setupRecord(USER_T* pRootNode);

/*  Write recordlist into file inform
 *  USER 'username' BOOKID 'XXXXXX'
 *  Argument :
 *      user - current user
 *      book - structure that hold all information of book
 */
void writeFile(USER_T* user, BOOK_T* book);

/*  Free LIST_HANDLE in structure of BOOK_T, BOOKLIST_T to free
*   all list in there, used with listDestroy()
*/
void freeRecordAndBookList();