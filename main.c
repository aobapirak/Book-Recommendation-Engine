/*
 *  main.c
 *
 *  This program is the main part of the entire 
 *  system for users to choose from. It is divided into 
 *  three parts: Register, Login, and Log out.
 *  
 *  Created by Poonyavee Wongwisetsuk (Pup) ID: 63070503430
 *  on 17 April 2021
 *      Created: accountMenu()
 *  
 *  Created by Chayathit Rattanapokil (Peach) ID: 63070503405 
 *      on 18 April 2021
 *      Created: main()
 *  
 *  Updated by Apirak Senarak (Aob) ID: 63070503458
 *      on 21 April 2021
 *      Updated: manage the all file UI terminal
 *      on 23 May 2021
 *      Updated: call free data -> binary tree, hash table
 * 
 *  Update by Poonyavee Wongwisetsut (Pup) ID: 63070503430
 *      on 23 May 2021
 *      Updated: to call function purchase after recommend
 *      on 24 May 2021
 *      Updated: call freeRecordAndBookList()
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declareFunction.h"
#include "abstractHashTable.h"

USER_T* pRootNode = NULL;   /* declare global - first node of binary tree */

/* to create a line between command */
void drawLine()
{
    printf("__________________________________________________________\n");
}

/* This function will display an option for the user to choose to log in or register.
 * If the user selects outside of the selection range, it will send an error message.
 * Return: return 0 when out of range option, Return the selection when select in range option.
 */
int accountMenu()
{
    char input[64];         /* for getting from user */
    int option = 0;         /* option */

    while(option == 0)
    {
        printf("%s", CLEAR_ESCAPE);
        drawLine();
        printf("\n\tWelcome to Book recommendation engine!\n");
        drawLine();
        printf("\n\t[1] Create an Account\n");
        printf("\t[2] Log in\n");
        printf("\t[3] Exit Program\n\n");
        printf("\tWhat would you like to do?: ");
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%d",&option);
        
        if(option <= 0 || option > 3)
        {
            printf("\n\t[Invalid selection - choose 1 to 3]\n");
            option = 0;
        }
    }
	return option;
}

/* This function will send the user to an action when 
 * they have chosen the desired option.
 * If out of selection range, it will send an error message.
 */
int main()
{
    int returnVal = 0;                        /* keep value that return from accountMenu */
    int bOk = 0;                              /* check to break while loop */
    unsigned int (*hashFn)(char* key) = NULL; /* for store value from bitwiseOpHash */
    USER_T* currentUser = NULL;               /* user who is currently logged in */
    char input[MAX];                          /* getting input from user */
    char search[32];                         /* recieve [Y/N] from user */
    BOOKLIST_T* purchaselist = NULL;          /* hold list of book that user select to buy */
    int searchbook = 0;                       /* option to select */

    /********************** Create & Insert data ***********************/
    pRootNode = createBinaryTree();
    hashFn = &bitwiseOpHash;
    /* assume size of table to 1001 */
    if (!hashTableInit(1001,hashFn))
		printf(">>> Error! Cannot initialize hash table\n");
    buildBookList();
    printf(">>> Finished building booklist\n");
    setupRecord(pRootNode);
    printf(">>> Finished adding books and users to records\n");
    /*******************************************************************/
      
    while(returnVal != 3)
    {
        returnVal = accountMenu();
        switch (returnVal)
        {
            case 1:
                printf("%s", CLEAR_ESCAPE);
                regist(pRootNode);
                break;
            case 2:
                printf("%s", CLEAR_ESCAPE);
                currentUser = login(pRootNode);
                if (currentUser != NULL)
                {
                    while (1)
                    {
                        memset(input,0,sizeof(input));
                        memset(search,0,sizeof(search));
                        printf("\n\tWould you like to search for a book? [Y/N]: ");
                        fgets(input,sizeof(input),stdin);
                        sscanf(input,"%s", search);
                        if(strcasecmp(search,"Y") == 0)
                        {
                            while(1)
                            {
                                purchaselist = searchSystem(currentUser,purchaselist);
                                if (purchaselist != NULL)
                                {
                                    while(strcasecmp(search,"N") != 0)
                                    {
                                        checkout(purchaselist,currentUser);
                                        //recommend usecase
                                        BOOKLIST_T* recommendList = communityBase(purchaselist,currentUser);
                                        BOOK_T* recommendBook = contentBase(purchaselist,currentUser);
                                        while(1)
                                        {
                                            printf("\n\tWould you like to make another purchase?");
                                            printf("\n\tElse you will log out [Y/N]: ");
                                            fgets(input,sizeof(input),stdin);
                                            sscanf(input,"%s",search);
                                            if(strcasecmp(search,"Y") != 0 && strcasecmp(search,"N") != 0)
                                                printf("\t-> Invalid - input Y or N\n");
                                            else if (strcasecmp(search,"Y") == 0)
                                            {
                                                if(recommendBook != NULL) // if there is no book from content-based to recommend
                                                {
                                                    listInsertEnd(recommendList->bookList,recommendBook);
                                                    recommendList->count++;
                                                }
                                                if(recommendList->count > 0) // if recommend list is empty
                                                {
                                                    purchaselist = purchaseMain(recommendList,currentUser,purchaselist);
                                                }
                                                while(1)
                                                {
                                                    searchbook = 0;
                                                    //next action loop
                                                    drawLine();
                                                    printf("\n\t[1] Search for another book\n");
                                                    printf("\t[2] Checkout\n");
                                                    printf("\t[3] Logout\n\n");
                                                    printf("\tWhat would you like to do?: ");
                                                    fgets(input,sizeof(input),stdin);
                                                    sscanf(input,"%d", &searchbook);
                                                    if(searchbook == 3)
                                                    {
                                                        bOk = 1;
                                                        break; // break from next action loop
                                                    }
                                                    else if((purchaselist == NULL) && (searchbook == 2 )) 
                                                        printf("\tCan't checkout, haven't selected a book\n");
                                                    else if((searchbook > 3) || (searchbook < 1))
                                                        printf("\t-> Invalid - input 1-3\n");
                                                    else
                                                        break; // break from next action loop
                                                }
                                                break; // break from make another purchase loop
                                            }
                                            else if (strcasecmp(search,"N") == 0)   
                                            {
                                                bOk = 1;
                                                break; // break from make another purchase loop
                                            }
                                        }
                                        if(bOk == 1 || searchbook == 1)
                                            break; // break from checkout loop
                                    }
                                    if (bOk == 1)
                                        break; // break from searchsystem loop
                                }
                                else
                                {
                                    bOk = 1;
                                    break;
                                }
                            }
                        }
                        else if(strcasecmp(search,"N") == 0)
                            break;
                        else
                            printf("\t-> Invalid - input Y or N\n"); 
                        
                        if (bOk == 1)
                            break;
                    }
                }
                break;
            case 3:
                listReset(purchaselist->bookList);
                listDestroy(purchaselist->bookList);
                freeRecordAndBookList();
                printf("\n\t>>> Called free list\n");
                freeNode(pRootNode);
                printf("\t>>> Called free binary tree\n");
                hashTableFree();
                printf("\t>>> Called free hash table\n");
                
                printf("%s", CLEAR_ESCAPE);
                drawLine();
                printf("\n\tThank you for visited our engine :)\n");
                drawLine();
                printf("\n");
                exit(0);
            default:
                printf("\n\t[Invalid selection - choose 1 to 3]\n");
        }
    }
}