/* 
 *  login.c
 *
 *  This program is the main part of logging in to 
 *  the system to use, use the system to search for the desired book.
 *
 *  Created by Chayathit Rattanapokil (Peach) ID: 63070503405 
 *      on 18 April 2021
 *      Created: login(), checkFormat() 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "declareFunction.h"

/*  This function will login to program from user.
 *  Users are required to enter a username and password to login.
 *  If the username or password of the user cannot be found in the 
 *  database, will send message error.
 *  Arguments:
 *    pRootNode -  First node of tree 
 */
USER_T* login(USER_T* pRootNode)
{
    int countPassword = 0;      /* how many times the password was entered */
    int check = 0;              /* keeps values ​​returned from username pattern auditing */
    char input[MAX];            /* for getting input from user */
    char usernameSearch[MAX];   /* input username from user */
    char passwordSearch[MAX];   /* input password from user */
    int backToMenu = 0;         /* set to 1 when user back from search */

    USER_T* pUsername = NULL;   /* the user who has in the database */
    
    drawLine();
    printf("\n\t\t    [Login system]\n");
    drawLine();
    while(1)
    {
        memset(usernameSearch,0,sizeof(usernameSearch));
        printf("\n\tEnter your username [DONE to back]: ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%[^\n]", usernameSearch);
        
        if(strcasecmp(usernameSearch,"DONE") == 0)
            break;
    
        if(checkSpace(usernameSearch) == 0)
        {
            printf("\t\t=> Must not include spaces\n");
            continue;
        }
        else if(checkFormat(usernameSearch) == 0)
        {
            printf("\t\t=> Please enter only characters or numbers\n");
            continue;
        }  

        pUsername = findUser(usernameSearch, pRootNode);
        if (pUsername == NULL)
        {
            printf("\t\t=> Not found '%s' in system, please try again\n", usernameSearch);
            continue;
        }
        else
        {
            countPassword = 0;
            while(1)
            {
                printf("\n\tEnter your password [DONE to back]: ");
                fgets(input, sizeof(input), stdin);
                sscanf(input, "%[^\n]", passwordSearch);
                if(strcasecmp(passwordSearch,"DONE") == 0)
                    break;

                if(checkSpace(passwordSearch) == 0)
                {
                    printf("\t\t=> Must not include spaces\n");
                    continue;
                }
                else if(checkFormat(passwordSearch) == 0)
                {
                    printf("\t\t=> Please enter only characters or numbers\n");
                    continue;
                } 
                countPassword++;

                if(countPassword == 3)
                {
                    printf("\t\t=> You enter the wrong password too much\n");
                    printf("\t\t   Please login again\n");
                    drawLine();
                    break; 
                }

                if (strcmp(pUsername->password, passwordSearch) == 0)
                {
                    printf("%s", CLEAR_ESCAPE);
                    drawLine();
                    printf("\n\tHello, %s \n\tWelcome to Book Recommendation Engine :)\n",pUsername->name);
                    return pUsername;
                }
                else
                    printf("\t\t=> Wrong password, please try again\n");
            }
        }   
    }
    
}

/* This function checks for the format of the username, 
 * whether there are special characters or not.
 * Arguments:
 *      username   - The username entered by the user
 * Return 0 when the data has special characters, 
 * Return 1 when the data does not contain special characters.
 */
int checkFormat(char username[])
{
    int check = 1;        /* variables to return values ​​in a valid or invalid format */
    int i = 0;            /* counting of loop */
	
	for(i = 0; i < strlen(username); i++)
	{
		if(!isalnum(username[i]))
			check = 0;
	}
	return check;
}