/*
 *  recommendBook.c
 *
 *  This file is for usercase of a book recommendation, there are 2 ways:
 *  [1] Community => we will look random book, user to pick as a base to recommend
 *                   then, recommend all book that user has purchased
 *  [2] Content   => we will random book and pick as a base to recommend
 *                   create a similarityScore to count The books that are 
 *                   most similar in each attribute. Then, recommend 1 book to user
 *  After recommend, return recommendlist of community to main, return recommend of content to main
 *  To be used for further purchase if the user wants to
 *  
 *  Created by Poonyavee Wongwisetsuk (Pup) ID: 63070503430
 *   on 20 May 2021
 *      Created: communityBase()
 *   on 21 May 2021
 *      Created: randomNo, getRandomBook, getRandomUser
 * 
 *  Created by Apirak Senarak (Aob) ID: 63070503458
 *   on 22 May 2021
 *      Created: all function to recommend by content
 * 
 *  Updated by Poonyavee Wongwisetsuk (Pup) ID: 63070503430
 *   on 23 May 2021
 *      Updated: return list to main instead of call purchase in this file
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "declareFunction.h"
#include "abstractHashTable.h"

/* Simple function to get a random number
 *      Argument : 
 *          count - the maximum number that will be randomized from zero
 * Return : random - a random number within the given range
 */ 
int randomNo(int count)
{
    srand(time(0));
    int random = rand();
    random = random % count; 
    return random;
}

/* A function to pick a random book with record from a list
 *  Argument: 
 *          purchaselist - a list of purchased book to be randomly picked
 * Return : book[] - return a random book
 */ 
BOOK_T* getRandomBook(BOOKLIST_T* purchaselist)
{
    BOOK_T** book = NULL;   /* double pointer - hold book[] */
    BOOK_T* temp = NULL;    /* to hold data in purchaselist(booklist) */
    int i = 0;              /* counter bucket */
    int random = 0;         /* random number */
    int allEmpty = 1;       /* set all empty before check if has record */
    
    if(purchaselist->bookList != NULL)
    {
        book = (BOOK_T**) calloc(purchaselist->count, sizeof(BOOK_T*));
        if (book == NULL)
        {
            printf("Error - allocation \n");
            exit(1);
        }
        listReset(purchaselist->bookList);
        temp = listGetNext(purchaselist->bookList);
        while(temp != NULL)
        {
            // Check if any of the book has record
            if(temp->usercount > 0)
            {
                allEmpty = 0;
                book[i] = temp;
                i++;
            }
            temp = listGetNext(purchaselist->bookList);
        }
        if(allEmpty == 0)
        {
            random = randomNo(i);
            return book[random];
        }
    }
    return NULL;
}

/* A function to pick a random user with record from a list
 *  Argument: 
 *          book        - a book with record to pick randomized user from
 *          currentUser - user that is currently logged in
 * Return : user[random position] - return a random user
 */
USER_T* getRandomUser(BOOK_T* book, USER_T* currentUser)
{
    int i = 0;              /* counter bucket of array */
    int random = 0;         /* random number */
    int allEmpty = 1;       /* set it empty before check user has a record */
    USER_T* temp = NULL;    /* hold data in list */
    USER_T** user = NULL;   /* user to store data in list */

    if(book != NULL)
    {
        user = (USER_T**) calloc(book->usercount, sizeof(USER_T*));
        if (user == NULL)
        {
            printf("Error - allocation\n");
            exit(1);
        }
        listReset(book->record);
        temp = listGetNext(book->record);
        while(temp != NULL)
        {
            // if the user has a record of book and isn't the current user
            if(temp->bookcount > 0 && strcmp(temp->username,currentUser->username) != 0)
            {
                allEmpty = 0;
                user[i] = temp;
                i++;
            }
            temp = listGetNext(book->record);          
        }
        if(allEmpty == 0)
        {
            random = randomNo(i);
            return user[random];    
        }
    }
    return NULL;
}

/* Recommend the book by community base
 * this function will create a list to hold all the book that record by user that randomizes
 *   Argument:
 *          purchaselist - lsit of book that have been purchased
 *          currentUsere - user that is currently logged in
 * Return: recommendlist - list that hold the book
 */
BOOKLIST_T* communityBase(BOOKLIST_T* purchaselist, USER_T* currentUser)
{
    BOOK_T* temp = NULL;                            /* to hold data user (record) */
    BOOK_T* book = getRandomBook(purchaselist);     /* book that already random */
    BOOKLIST_T* recommendlist = NULL;               /* list - to hold recommend book */

    recommendlist = (BOOKLIST_T*) calloc(1,sizeof(BOOKLIST_T));
    if (recommendlist == NULL)
    {
        printf("Error - allocation\n");
        exit(1);
    }
    recommendlist->bookList = newList();
    printf("\n\t[Recommended by community]\n");
    if(book != NULL)
    {
        USER_T* user = getRandomUser(book,currentUser); 
        if(user != NULL)
        {
            listReset(user->record);
            temp = listGetNext(user->record);
            printf("\n\tUser '%s' who purchased '%s' also bought:\n",user->username,book->titleBook);
            while(temp != NULL)
            {
                if ((alreadyBought(currentUser,temp) == 0) && (strcasecmp(temp->bookID, book->bookID) != 0))
                {
                    printf("\n\tBook:'%s'\n", temp->titleBook);
                    printf("\tWritten by %s\n", temp->authorBook);
                    listInsertEnd(recommendlist->bookList,temp);
                    recommendlist->count++;
                }
                temp = listGetNext(user->record);
            }   
        }
        else    
            printf("\n  => Not enough information to recommend community-based (no user with previous purchase)\n");
    }
    else
        printf("\n  => Not enough information to recommend community-based (no book with previous purchase)\n");

    return recommendlist;
}

/*  find the same book in the list if it is
 *  will counting to similarityScore
 *      Argument
 *          similarList  - list of book that similar to book purchased
 *          temp         - structure of book hold information
 *  Return 1 if count, 0 if not count
 */
int sameBook(LIST_HANDLE similarList, BOOK_T* temp)
{
    BOOK_T* book = NULL;    /* to hold book in similar list */

    listReset(similarList);
    book = listGetNext(similarList);
    while (book != NULL)
    {
        if (strcasecmp(book->bookID, temp->bookID) == 0)
        {
            book->similarityScore++;
            return 1;
        }
        book = listGetNext(similarList);
    }
    return 0;
}

/*  Thie function will lookup to hash table that have this book or not
 *  then counting each book to find most similar book
 *      Argument
 *          similarList  - list of book that similar to book purchased
 *          attribute    - attribute of book which are 2, 3, 4
 *          buffer       - word's each attribute to lookupf
 *          book         - structure of book hold information
 *          currentUSer  - user that is currently logged in
 */
void similarityScore(LIST_HANDLE similarList, int attribute, char *buffer, BOOK_T* book, USER_T* currentUser)
{
    BOOK_T *temp = NULL;    /*  to hold data in recommend(booklist)*/
    BOOKLIST_T* recommend = hashTableLookup(attribute, buffer); /* to store data return after lookup */
    if(recommend != NULL)
    {
        //printf("\n\tAttribute type = %d\n", attribute);
        listReset(recommend->bookList);
        temp = listGetNext(recommend->bookList);
        while(temp != NULL)
        {
            if ((alreadyBought(currentUser,temp) == 0) && (strcasecmp(temp->bookID, book->bookID) != 0))
            {
                //printf("\tName: %s\n", temp->titleBook);
                if (sameBook(similarList, temp) == 0)
                    listInsertEnd(similarList, temp);
            }
            temp = listGetNext(recommend->bookList);
        }
    }
    else
    {
        printf("\n  => Not enough information to recommend content-based\n");
    }
}

/*  Thie function will separate each word's attribute
 *  and copy to buffer then will sent to similartyScore() function
 *  to couting
 *      Argument
 *          similarList  - list of book that similar to book purchased
 *          attribute    - attribute of book which are 2, 3, 4
 *          book         - structure of book hold information
 *          currentUser  - user that is currently logged in
 */
void separateWord(LIST_HANDLE similarList, int attribute, BOOK_T* book, USER_T* currentUser)
{
    char buffer[MAX];   /* for copy data in information of each book */
    char *cutString;    /* string to cut by strtok */

    if (attribute == 2)
        strcpy(buffer, book->authorBook);
    else if (attribute == 3)
        strcpy(buffer, book->genre);
    else if (attribute == 4)
        strcpy(buffer, book->keyword);
    
    if (attribute == 4)
    {
        cutString = strtok(buffer,",");
        while (cutString != NULL)
        {
            similarityScore(similarList, attribute, cutString, book, currentUser);
            cutString = strtok(NULL,",");
        }
    }
    else
        similarityScore(similarList, attribute, buffer, book, currentUser);
}

/*  Recommend the book by content base
 *  This function will random book in purchaselist as a base book then will 
 *  convert every attribute to lower string then sent to other function 
 *  to find most similarity score to recommend to user
 *    Argument:
 *          purchaselist - list of book that have been purchased
 *          currentUser  - user that is currently logged in
 *  Return: the most similar book
 */
BOOK_T* contentBase(BOOKLIST_T* purchaselist, USER_T* currentUser)
{
    /* we will pick random book in purchase list */
    BOOK_T* book = getRandomBook(purchaselist); /* random book in purchaselist */
    BOOK_T* recommend = NULL;                   /* to store temp when temp similarityScore is more */
    BOOK_T* temp = NULL;                        /* to hold data in similarList */
    LIST_HANDLE similarList = newList(); 
    int i = 0;
    char input[32];
    
    drawLine();
    printf("\n\t[Recommended by content]\n");
    if(book != NULL)
    {
        for (i=0; i<strlen(book->genre); i++)
            book->genre[i] = tolower(book->genre[i]);
        for (i=0; i<strlen(book->authorBook); i++)
            book->authorBook[i] = tolower(book->authorBook[i]);
        for (i=0; i<strlen(book->keyword); i++)
            book->keyword[i] = tolower(book->keyword[i]);

        for (i=2; i<5; i++)
            separateWord(similarList, i, book, currentUser);
        
        listReset(similarList);
        temp = listGetNext(similarList);
        if(temp == NULL) // case for when there is not enough book to recommend
        {
            printf("\n  => Not enough information to recommend content-based\n");
            return NULL;
        }
        recommend = temp;
        while (temp != NULL)
        {
            if (temp->similarityScore > recommend->similarityScore)
                recommend = temp;
            temp = listGetNext(similarList);
        }
        printf("\n\tA book that is similar to '%s'\n", book->titleBook);
        printf("\n\tBook:'%s'\n", recommend->titleBook);
        printf("\tWritten by %s\n", recommend->authorBook);
        drawLine();
    }
    else
        printf("\n  => Not enough information to recommend content-based\n");

    return recommend;
}
    