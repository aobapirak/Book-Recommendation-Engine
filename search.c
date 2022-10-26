/*
*   search.c
*
*   This file will initial the hash table with 1001 size, then build the bookList to hold list of book.
*   After that, will insert the data to hash table. Then will let user to search by attribute that user
*   want to search then the program will list all the book founds and let user pick which book to
*   display the information
*   
*   Created by Poonyavee Wongwisetsuk (Pup) ID: 63070503430
*       on 12 April 2021
*       Created: Read file, call init with the size, hash insert the data, lookup each data and create search function 
*
*   Updated by Apirak Senarak (Aob) ID: 63070503458
*       on 18 April 2021
*       Additional: link to linkedListUill.c to using LIST_HANDLE_T to list all the book
*                   before insert to hash table
*       on 20 April 2021
*       Update: update search function, let use can pick which book user interested intead of only display
*               all books that we found
*    
*   Updated by Poonyavee Wongwisetsuk (Pup) ID: 63070503430
*       on 14 May 2021
*       Update: divide the function into smaller parts
*               
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "abstractHashTable.h"
#include "declareFunction.h"

/*  This function for call all function to linked list the data
*   insert to hash table and search
*   Argument : 
*       currentuser  - user that is currently logged in
*       purchaselist - list that hold all book user purchased
*   Returns :
*       list of books that was purchased as BOOKLIST_T
*/
BOOKLIST_T* searchSystem(USER_T* currentuser, BOOKLIST_T* purchaselist)
{
    char input[MAX];         /* for input while reading file */
    char searchOpt[MAX];     /* select the option */        
    int countData;           /* for store amount of data that read from file */
    
    printf("%s",CLEAR_ESCAPE);
    drawLine();
    printf("\n\t\t   [Search system]\n");
    while(1)
    {
        drawLine();
        printf("\n\tSelect the desired attribute to search\n");
        printf("\t    [1] Search by Name\n\t    [2] Search by Author\n\t    [3] Search by Genre\n\t    [4] Search by Keyword\n\t    [5] Checkout\n");
        printf("\n\tEnter [DONE to back]: ");
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%s", searchOpt);
        if(strcasecmp(searchOpt,"DONE") == 0)
            break;
          
        if (strcmp(searchOpt, "1") == 0)
            purchaselist = search("\n\tSearch by title [DONE to back]: ", NAME, currentuser, purchaselist);
        else if (strcmp(searchOpt, "2") == 0)
           purchaselist = search("\n\tSearch by author [DONE to back]: ", AUTHOR, currentuser, purchaselist);
        else if (strcmp(searchOpt, "3") == 0)
            purchaselist = search("\n\tSearch by genre [DONE to back]: ", GENRE, currentuser, purchaselist);
        else if (strcmp(searchOpt, "4") == 0)
            purchaselist = search("\n\tSearch by keyword [DONE to back]: ", KEYWORD, currentuser, purchaselist);
        else if (strcmp(searchOpt, "5") == 0)
        {
            if(purchaselist != NULL)
                return purchaselist;
            else
                printf("\t>>> Cannot checkout, the cart is empty\n");
        }
        else
            printf("\t>>> Wrong input, should be 1-5\n");
    }
    return purchaselist;
}

/* to display infomation of book 
*       Argument:
*               book    -   hold all the information's book
*/
void displayBook(BOOK_T* book)
{
    printf("\n\t  Title Book  : %s\n",book->titleBook);
    printf("\t  Author      : %s\n",book->authorBook);
    printf("\t  Genre       : %s\n",book->genre);
    printf("\t  Page Length : %s\n",book->pageLength);
    drawLine();
}

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
BOOKLIST_T* search(char* prompt, int category, USER_T* currentUser, BOOKLIST_T* purchaselist)
{
    char search[MAX];       /* for store search */
    char input[MAX];        /* for getting input */
    int selectBook;         /* for select the book that found */
    int select;             /* keep value of selecBook from string to integer */
    int i = 0, j = 0;       /* counter the loop */
    char option[32];        /* for select continue or not */
    char purchaseOpt[32];   /* for select buy or not */
    int countData = 0;      /* count how many data in file */
    FILE *pInfile = NULL;   /* for reading input file */

    BOOK_T** info = NULL;   /* double pointer - for keep data from bookList */
    LIST_HANDLE list;       /* linkedlist - list to handle the bookList */
    
    /* read file to get the amount of data */
    pInfile = fopen("bookInfo.txt","r");
    if(pInfile == NULL)
    {
        printf("Error - opening file");
        exit(1);
    }
    while(fgets(input,sizeof(input),pInfile) != NULL)
        countData++;
    fclose(pInfile);

    while(1)
    {
        j = 0;
        printf("%s",prompt);
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%[^\n]", search);
        if(strcasecmp(search,"DONE") == 0)
            return purchaselist;

        for (i=0; i<strlen(search); i++)
            search[i] = tolower(search[i]);
        
        BOOKLIST_T* book = hashTableLookup(category, search);
        if (book == NULL)
            printf("\t==> Couldn't find any book\n");
        else
        {
            BOOK_T* selectedBook = printFoundBook(book->bookList,countData);
            if(selectedBook != NULL)
            {
                displayBook(selectedBook);
                /** purchase usecase **/
                purchaselist = purchaseOption(selectedBook, purchaselist, currentUser);
                while(1)
                {
                    printf("\n\tWould you like to search again?\n");
                    printf("\tElse you will return to menu [Y/N]: ");
                    fgets(input,sizeof(input),stdin);
                    sscanf(input,"%s", option);
                    if(strcasecmp(option,"Y") == 0)
                        break;
                    else if(strcasecmp(option,"N") == 0)
                            return purchaselist;
                    else
                        printf("\t-> Invalid - input Y or N\n"); 
                }
            }
        }
    }
}

/* print all the books from the list
 * ask to select a book and return the book data
 * Argument : list of book, countData
 * Return: a book info
 */ 
BOOK_T* printFoundBook(LIST_HANDLE list, int countData)
{
    BOOK_T* info = NULL;   /* double pointer - for keep data from bookList */
    int i = 0;              /* for loop*/
    int j = 0;              /* counter the loop */
    int check = 0;          /* check condition */
    char input[32];         /* getting input from user */
    int selectBook = 0;     /* for select the book that found */

    info = (BOOK_T*) calloc(countData, sizeof(BOOK_T));
    if (info == NULL)
    {
        printf("Error - allocation\n");
        exit(0);
    }
    
    printf("%s", CLEAR_ESCAPE);
    drawLine();
    printf("\n\t\t   [All book founds]\n");
    drawLine();
    printf("\n");

    listReset(list);
    info = listGetNext(list);
    while (info != NULL)
    {    
        printf("\t[#No.%d] Book: %s\n", j+1, info->titleBook);
        info = listGetNext(list);
        j++;
    }
    drawLine();
    printf("\n\tWhich book are you interested in?\n");
    while (1)
    {
        printf("\n\tSelect [0 to back]: ");
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%d", &selectBook);
        input[strlen(input)-1] = '\0';
        for (i=0; i<strlen(input); i++)
        {
            if (!isdigit(input[i]))
            {
                printf("\t=> Invalid - should be digit\n");
                check = 0;
                break;
            }
            check = 1;
        }
        if (check == 1)
        {
            if (selectBook == 0)
                return NULL;
            else if ((selectBook > j) || (selectBook <= 0))
                printf("\t=> Invalid - should be in the range of the book found\n");
            else
            {
                listReset(list);
                for (i=0; i<selectBook; i++)
                {
                    info = listGetNext(list);
                }
                BOOK_T* selectedBook = info;
                return selectedBook;
            }
        }
    }
}