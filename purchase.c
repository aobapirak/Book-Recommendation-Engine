/*
*   purchase.c
*   This file is used for the functions of various purchase processing 
*   systems which are asked to purchase make a purchase list to hold
*   book that user purchased, and make a checkout
*   
*   Created by Poonyavee Wongwisetsuk (Pup) ID: 63070503430
*    on 3-5 May 2021
*      Created: purechaseOption(), purchaseBook(), checkout()
*    on 19 May 2021
*      Created: purchaseMain() => to purchase incase of after recommend
*               
*   Update by Poonyavee Wongwisetsuk (Pup) ID: 63070503430
*     on 21 May 2021
*       Updated: fixed the bug
*   
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "abstractHashTable.h"
#include "declareFunction.h"

/* Provide option to purchase or not
 * if yes, then it will add the book to your cart
 *   Argument : 
 *              Book - to add to cart
 *              List - to holds the purchased books
 *              User - that is currently logged in
 *  return: the list of book you purchased so far
 */
BOOKLIST_T* purchaseOption(BOOK_T* book, BOOKLIST_T* purchaselist, USER_T* currentuser)
{
    char input[MAX];        /* getting input from user */
    char option[MAX];       /* option to select */

    while (1)
    {
        printf("\n\tWould you like to purchase this book? [Y/N]: ");
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%s", option);
        if (strcasecmp(option,"Y") == 0)
        {
            purchaselist = purchaseBook(book, purchaselist, currentuser);
            break;
        }
        else if (strcasecmp(option,"N") == 0)
            break;
        else
            printf("\t>>> Invalid input - should be Y or N\n");
    }
    return purchaselist;
}

/* Take book and add to the end of the list of purchased book 
 *   Argument : 
 *                 book         - book information 
 *                 purchaselist - list of purchased books
 *                 currentuser  - user information
 *   Return: purchaselist that create/insert to list
 */
BOOKLIST_T* purchaseBook(BOOK_T* book, BOOKLIST_T* purchaselist, USER_T* currentuser)
{
    if(alreadyBought(currentuser,book) == 0)
    {
        if (purchaselist == NULL)
        {
            purchaselist = (BOOKLIST_T*) calloc(1, sizeof(BOOKLIST_T));
        }
        if(purchaselist->bookList == NULL)
        {
            purchaselist->bookList = newList();
        }
        listReset(purchaselist->bookList);
        BOOK_T* compare = listGetNext(purchaselist->bookList);
        while(compare != NULL)
        {
            if(compare->bookID == book->bookID)
            {
                printf("\n => User '%s' have already purchased book '%s'\n",currentuser->username,book->titleBook);
                return purchaselist;
            }
            compare = listGetNext(purchaselist->bookList);
        }
        listInsertEnd(purchaselist->bookList,book); 
        purchaselist->count++;
        printf("\n\t\t[Added to cart!]\n");
    }
    else 
    {
        printf("\n => User '%s' have already purchased book '%s'\n",currentuser->username,book->titleBook);
    }
    return purchaselist;
}

/* Traverse the purchaselist, call function to record, write into the file
 * then, prints out all the book that purchased
 *   Argument : 
 *             purchase - hold the list structure that store bookList of purchased
 *             user     - current user that login to system
 */
void checkout(BOOKLIST_T* purchase, USER_T* user)
{
    BOOK_T** info = NULL;   /* double pointer - for keep data from bookList */
    LIST_HANDLE list;       /* linkedlist - list to handle the bookList */
    BOOK_T* tmp = NULL;     /* temporary holds the current book */
    int j = 0;              /* counter the loop */

    info = (BOOK_T**) calloc(purchase->count, sizeof(BOOK_T*));
    if (info == NULL)
    {
        printf("Error - allocation\n");
        exit(0);
    }
    list = purchase->bookList;
    listReset(list);
    info[j] = listGetNext(list);
    printf("%s", CLEAR_ESCAPE);
    drawLine();
    printf("\n\t\t   [All book purchased]\n");
    drawLine();
    printf("\n");

    // If the user haven't already bought this book, it will be added to the record and write into file
    // else if user has bought it, it will be removed from record
    while (info[j] != NULL)
    {    
        if((alreadyBought(user,info[j]) == 0) && (alreadyhaveUser(user,info[j]) == 0))
        {
            addToUserList(user,info[j]); 
            addToBookList(user,info[j]);
            writeFile(user,info[j]);
            printf("\t[#No.%d] Book: %s\n", j+1, info[j]->titleBook);
        }
        else
        {
            printf("\n => User '%s' have already purchased book '%s'\n\n",user->username,info[j]->titleBook);
        }
        j++;
        info[j] = listGetNext(list);
    }
    drawLine();
}

/* This function will let user select the book that got recommend by content or community
 * in main function. After that, will let user purchase book that user like to buy
 *   Argument : 
 *             recommendlist - hold the list structure which got recommend by content/community
 *             currentUser   - current user that login to system
 *             purchaselist  - list of book that user purchased
 *   Return : list of purchased book
 */
BOOKLIST_T* purchaseMain(BOOKLIST_T* recommendlist, USER_T* currentUser, BOOKLIST_T* purchaselist)
{
    char input[32];                     /* getting input from user */
    char option[32];                    /* option to select */
    BOOK_T* selectedBook = NULL;        /* book - selected by user */

    while(1)
    {
        selectedBook = printFoundBook(recommendlist->bookList, recommendlist->count);
        if(selectedBook != NULL)
        {
            displayBook(selectedBook);
            purchaselist = purchaseOption(selectedBook, purchaselist, currentUser);
            while(1)
            {
                printf("\n\tWould you like to select again?\n");
                printf("\tElse you will proceed to checkout [Y/N]: ");
                fgets(input,sizeof(input),stdin);
                sscanf(input,"%s", option);
                if(strcasecmp(option,"Y") == 0)
                    break;
                else if(strcasecmp(option,"N") == 0)
                {
                    if(purchaselist == NULL)
                    {
                        printf("\n\tCannot checkout, please select an item\n");
                        break;
                    }
                    else
                        return purchaselist;
                }
                else 
                    printf("\t>>> Invalid - input Y or N\n"); 
            }
        }
        if (selectedBook == NULL)
            return purchaselist;
    }
}