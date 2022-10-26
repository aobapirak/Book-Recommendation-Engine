/*
 *  dataManagement.c
 *
 *  This file will build all data that happen in this program which are
 *  [binary tree] => for account, create binary tree, insert node, free node, findUser
 *  [hash table, linkedlist] => build booklist, insert to hash table
 *  [setup record]  => read recordlist.txt which is purchase history to setup data
 *                     to structure
 *
 *  Created by Apirak Senarak (Aob) ID: 63070503458
 *    on 12 April 2021
 *      Created: all function to create binary, node login
 *    on 18 April 2021
 *      Created: create allfunction about hashtable, linkedlist
 *    on 28 April 2021
 *      Updated: buildBookList() to work more efficient
 * 
 *  Created by Poonyavee Wongwisetsuk (Pup) ID: 63070503430
 *    on 1 May 2021
 *      Created: all function to setup record to structure
 *    on 15 May 2021
 *      Update: check alreadybought, fixed the bug
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "declareFunction.h"
#include "abstractHashTable.h"

/* Find a person with a name that matches 'name'
 * Arguments:
 *    usernameSearch  -    userName that we finding
 *    pCurrent        -    userName in file
 * Return the pointer to the person desired, or NULL if no match.
 */
USER_T * findUser(char* usernameSearch, USER_T* pCurrent)
{
    USER_T* pFound = NULL; /* for store value when found the data */

    if(pCurrent != NULL)
    {
        if(strcmp(pCurrent->username, usernameSearch) == 0) // found!
            pFound = pCurrent;
        else if(strcmp(pCurrent->username, usernameSearch) > 0) // left
            pFound = findUser(usernameSearch, pCurrent->leftChild);
        else // right
            pFound = findUser(usernameSearch, pCurrent->rightChild);
    }
    else
        return pFound;
}

/* Traverse a tree and execute to free
 * each leftChild node and rightChild node
 * Arguments:
 *    pCurrent                -   current node
 * freeNode(recursive)     -   function to execute on each node
 */
void freeNode(USER_T* pCurrent)
{
    if(pCurrent->leftChild != NULL)
    {
        freeNode(pCurrent->leftChild); 
    }
    if(pCurrent->rightChild != NULL)
    {
        freeNode(pCurrent->rightChild); 
    }
    
    if(pCurrent->record != NULL)
    {
        listReset(pCurrent->record);
        listDestroy(pCurrent->record);
        pCurrent->record = NULL;
        //printf("Removed user '%s'\n",pCurrent->username);
    }
    free(pCurrent);
}

/* Recursive function to insert a node into the binary tree
 * by sorted with < 0 go left and > 0 go right
 * Arguments:
 *    currentNode -  Current location in the tree
 *    newNode     -  New node to insert
 */
void insertNode(USER_T* currentNode, USER_T* newNode)
{
    if (strcmp(newNode->username, currentNode->username) < 0) /* go left */
    {
        if (currentNode->leftChild == NULL)
        {
            currentNode->leftChild = newNode;
            //printf("Adding '%s' as left child of '%s'\n",newNode->username,currentNode->username);
        }
        else
            insertNode(currentNode->leftChild,newNode);
    }
    else /* go right */
    {
        if (currentNode->rightChild == NULL)
        {
            currentNode->rightChild = newNode;
            //printf("Adding '%s' as right child of '%s'\n",newNode->username,currentNode->username);
        }
        else
            insertNode(currentNode->rightChild,newNode);
    }
}

/* Read the database file and create a binary tree to log in
 * Data from reading will be copied to the data structure.
 * then creat the tree. Once it successfully, it will going to login
 * Return : root node
 */
USER_T* createBinaryTree()
{
    FILE *pInfile = NULL;       /* for reading input file */
    char input[MAX];            /* for getting input from user */           
    char info[4][MAX];          /* store infomation from file */
    int countData = 0;          /* counting how many data inserted */
    
    USER_T* pRootNode = NULL;   /* root node of binary tree */
    USER_T* user = NULL;        /* for copy data */

    pInfile = fopen("account.txt","r");

    if(pInfile == NULL)
    {
        printf("Error - opening file");
        exit(1);
    }

    while((fgets(input,sizeof(input),pInfile) != NULL))
    {
        sscanf(input,"Name:%[^,],Username:%[^,],Password:%[^\n]", info[0], info[1], info[2]);
        
        user = (USER_T*) calloc(1,sizeof(USER_T));
        if(user == NULL)
        {
            printf("Error - allocation \n");
            exit(1);
        }
        else
        {
            strcpy(user->name, info[0]);
            strcpy(user->username, info[1]);
            strcpy(user->password, info[2]);
            
            if(pRootNode == NULL)
                pRootNode = user;
            else
              insertNode(pRootNode, user);
            countData++;
        }
    }
    fclose(pInfile);

    //printf("\n[Successfully inserted the data!]\n");
    //printf(" Inserted #%d data\n\n", countData);  
    //freeNode(pRootNode);
    return pRootNode;
}

/*  This function using for build the bookList to keep data
*   into the linkedlist and insert data to the hash table
*/
void buildBookList()
{
    FILE *pInfile = NULL;               /* for reading input file */
    char input[MAX];                    /* for getting input */
    int i = 0, j = 0, attribute = 0;    /* counting indexthe array and counter the loop */
    char key[5][MAX];                   /* for copy the data from structure and sent to hash table */
    int pCollision = -1;                /* pointer - collision */
    int countData = 0;                  /* counter the data that read from file */

    BOOK_T* pNewBook = NULL;            /* structure to hold information of book */

    pInfile = fopen("bookInfo.txt","r");
    if(pInfile == NULL)
    {
        printf("Error - opening file");
        exit(1);
    }

    while(fgets(input,sizeof(input),pInfile) != NULL)
    {   
        pNewBook = calloc(1,sizeof(BOOK_T));
        if(pNewBook == NULL)
        {
            printf("Error - allocation \n");
            exit(1);
        }
    	if(sscanf(input, "bookID:%[^~]~title:%[^~]~author:%[^~]~genre:%[^~]~length in pages:%[^~]~keywords:%[^\r\n]", pNewBook->bookID, pNewBook->titleBook, pNewBook->authorBook, pNewBook->genre, pNewBook->pageLength, pNewBook->keyword) != 6)
            continue;
        
        countData++;        

        for (attribute = 0; attribute < 5; attribute++)
        {
            //set key to "" before copy the data to key[0]
            for (i = 0; i < 3; i++)
                strcpy(key[i],"");

            if (attribute == 0)
                strcpy(key[0], pNewBook->bookID);
            else if (attribute == 1)
                strcpy(key[0], pNewBook->titleBook);
            else if (attribute == 2)
                strcpy(key[0], pNewBook->authorBook); 
            else if (attribute == 3)
                strcpy(key[0], pNewBook->genre); 
            else if (attribute == 4)
                sscanf(pNewBook->keyword,"%[^,],%[^,],%[^\n]",key[0],key[1],key[2]);

            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < strlen(key[i]); j++)
                    key[i][j] = tolower(key[i][j]); 

                //no data left
                if (strcmp(key[i], "") == 0)
                    break;

                BOOKLIST_T* item = hashTableLookup(attribute,key[i]);
                if (item == NULL)
                {
                    item = calloc(1, sizeof(BOOKLIST_T));
                    if (item == NULL)
                    {
                        printf("Error - allocation");
                        exit(1);
                    }
                    item->attribute = attribute;
                    strcpy(item->key, key[i]);
                    item->bookList = newList();
                }
                listInsertEnd(item->bookList, pNewBook); 
                hashTableInsert(item->attribute,item->key,item,&pCollision);
            }
        }
    }
    fclose(pInfile);
}

/* A simple function to add user to book's record
 *      Argument : 
 *          user    -   user that is currently logged in
 *          book    -   book to record user in there
 */
void addToBookList(USER_T* user, BOOK_T* book)
{
    int check = alreadyhaveUser(user,book); /* check already buy before record */
    if(check == 0)
    {
        if(book->record == NULL)
        {
            book->record = newList();
        }
        listInsertEnd(book->record,user);
        book->usercount++;
        //printf("Added %s to %s's record\n",user->username,book->titleBook);
    }
}

/* A simple function to check if book already has user on the list
 *      Argument : 
 *          user    -   user that is currently logged in
 *          book    -   structure's book which hold information
 *      
 * Return : 0 for not on list and 1 for already on list
 */
int alreadyhaveUser(USER_T* user, BOOK_T* book)
{
    USER_T* temp = NULL; /* hold data in book list(record) */
    if(book->record != NULL)
    {
        listReset(book->record);
        temp = listGetNext(book->record);
        while(temp != NULL)
        {   
            if(strcmp(temp->username,user->username) == 0)
            {
                //printf("Already added user '%s' to book '%s'\n",user->username,book->titleBook);
                return 1;
            }
            temp = listGetNext(book->record);
        }
    }
    return 0;
}

/* A simple function to add book to user's record
 *      Argument :
 *          user    -   user that is currently logged in
 *          book    -   book which hold information
 */
void addToUserList(USER_T* user, BOOK_T* book)
{
    int check = alreadyBought(user,book); /* check alreadyBought before record */
    if(check == 0)
    {
        if(user->record == NULL)
        {
            user->record = newList();
        }
        listInsertEnd(user->record,book);
        user->bookcount++;
        //printf("Added %s to %s's record\n",book->titleBook,user->username);
    }
}

/* A simple function to check if user already has book on the list
 *      Argument: 
 *          user    -   user that is currently logged in
 *          book    -   book which hold information
 * Return : 0 for not on list and 1 for already on list
 */
int alreadyBought(USER_T* user, BOOK_T* book)
{
    BOOK_T* temp = NULL; /* hold data in user list(record) */

    if(user->record != NULL)
    {
        listReset(user->record);
        temp = listGetNext(user->record);
        while(temp != NULL)
        {
            if(strcmp(temp->titleBook,book->titleBook) == 0)
            {
                //printf("Already added book '%s' to user '%s' record\n",book->titleBook,user->username);
                return 1;
            }
            temp = listGetNext(user->record);
        }
    }
    return 0;
}

/*   This function read the recordlist.txt and set up the
*    list 'record'
*    Argument
*       pRootNode - root node of the tree
*/
void setupRecord(USER_T* pRootNode)
{                 
    char username[MAX];         /* username as string */           
    char inputline[MAX];        /* inputline in recordlist.txt */
    char bookID[MAX];           /* bookID as string */
    FILE* pInfile = NULL;       /* open file to read data */
    USER_T* user = NULL;        /* to hold data that return from findUser */
    BOOKLIST_T* book = NULL;    /* to hold data that return from lookup with bookID */

    //Open File
    pInfile = fopen("recordlist.txt","r");
    if(pInfile == NULL)
    {
        printf("Error - opening file");
        exit(1);
    }
    //Read file line by line and put in linked list and hash table
    while(fgets(inputline,sizeof(inputline),pInfile) != NULL)
    {   
        book = calloc(1, sizeof(BOOKLIST_T));
        if (book == NULL)
        {
            printf("Error - allocation\n");
            exit(1);
        }
        sscanf(inputline,"USER %s BOOKID %[^~]~",username,bookID);
        
        user = findUser(username,pRootNode);
        book = hashTableLookup(BOOKID,bookID);
        
        listReset(book->bookList);
        BOOK_T* addBook = listGetNext(book->bookList);
        addToUserList(user,addBook);
        addToBookList(user,addBook);
    }  
}

/*  Write recordlist into file inform
 *  USER 'username' BOOKID 'XXXXXX'
 *  Argument :
 *      user - current user
 *      book - structure that hold all information of book
 */
void writeFile(USER_T* user, BOOK_T* book)
{
    FILE* pInfile = NULL;  /* open file 'recordlist.txt' to write */

    pInfile = fopen("recordlist.txt", "a+");
    if(pInfile == NULL)
    {
        printf("Unable to open file\n");
        exit(1);
    }
    else
    {
        fprintf(pInfile, "%s %s %s %s~\n","USER", user->username, "BOOKID", book->bookID);
    }
    fclose(pInfile);
}