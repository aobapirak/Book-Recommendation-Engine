/* 
 * register.c 
 *
 * This file is main of registration user's.
 * The user is required to enter three pieces of 
 * information: name, username and password.
 *
 * Created by Kasikan Wisetkami (Mook) ID: 63070503403
 *      on 17 April 2021
 *      Created: registor system
 * 
 * Created by Apirak Senarak (Aob) ID: 63070503458
 *      on 18 April 2021
 *      Created: write the information's account to database
 * 
 * Updated by Kasikan Wisetkami (Mook) ID: 63070503403
 *      on 6 May 2021
 *      Update: allowed user can space between the name
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "declareFunction.h"

/* This function is the main part of the registration operation.
 * If the file cannot be opened successfully, it will be closed.
 * When validating each item entered from a user has been successfully 
 * verified, the program will write all the information to the database.
 */
void regist(USER_T* pRootNode)
{
    int addData;                                /* variable for keep value return from password function */

    FILE* pInfile = NULL;                       /* pointer variable to read file */
    USER_T* user = calloc(1,sizeof(USER_T));    /* pointer variable for keeping information from registration of user */

    pInfile = fopen("account.txt", "a+");
    if(pInfile == NULL)
    {
        printf("Error opening file \n");
        exit(1);
    }
    drawLine();
    printf("\n\t\t  [Register system]\n");
    drawLine();
    printf("\n\tPlease fill the information\n");
    enterName();
    enterUsername();
    addData = enterPassword();
    printf("%s", CLEAR_ESCAPE);    
    if(addData == 1)
    {
        fprintf(pInfile,"Name:%s,Username:%s,Password:%s\n",data.name,data.username, data.password);

        strcpy(user->name, data.name);
        strcpy(user->username, data.username);
        strcpy(user->password, data.password);

        insertNode(pRootNode, user);

        printf("\n\t[Successfully created!]\n");
        printf("\t  Name: %s\n\t  Username: %s\n\t  Password: %s\n\n", data.name, data.username, data.password);
        printf("\tThanks for regist our engine :)\n\n");
        printf("\tPress any key to continue...");
        getchar();
    }
    fclose(pInfile);
}

/* This function checks the name from the user's enter.
 * If the name format is incorrect, an error message will be sent.
 * If the name entered is correct, the system will save.
 */
void enterName()
{
    int check = 1;          /* variable for checking the status */
    char input[MAX];        /* variable for reading data from user */

    printf("\n\tName rules:\n");
	printf("\t\t=> Only characters are allow in the name\n");
	printf("\t\t=> The first character must begin with only uppercase letter\n");
    printf("\t\t=> No specials character are allow in the name\n");
    while(1)
    {
        printf("\n\tEnter your name: ");
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%[^\n]",data.name);  
        
        if(checkSpecific(data.name) == 0)
        {
            printf("\t=> Invalid: Do not enter a special character\n");
            check = 0; 
        }    
        else if(checkAlpha(data.name) == 0)
        {
            printf("\t=> Invalid: Please enter only characters\n");
            check = 0;
        }
        else if(checkAlpha(data.name) == -1)
        {
            printf("\t=> Invalid: The first character must begin an uppercase letter\n");
            check = 0;
        }   
        else
        {
            printf("\t>>> Name '%s' can be used",data.name);
            check = 1;
        }   

        if(check == 1)
            break; 
    }
}

/* This function checks the username from the user's enter.
 * If the username format is incorrect, it will send an error message.
 * The username must be unique to any other user. If a username is 
 * detected same other, it will send a error message.
 * If the username entered is correct, the system will save.
 */
void enterUsername()
{
    int check = 1;          /* variable for checking the status */
    char input[MAX];        /* variable for reading data from user */        

    printf("\n\n\tUsername rules:\n");
	printf("\t\t=> Characters and number are allowed in the username\n");
	printf("\t\t=> Username must contain 6-16 characters\n");
    printf("\t\t=> No space are allow in the username\n");
    printf("\t\t=> No specials character are allow in the username\n");
    while(1)
    {
        printf("\n\tEnter your username: ");
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%[^\n]",data.username);

        if(checkSpace(data.username) == 0)
        {
            printf("\t=> Invalid - Must not include spaces\n");
            check = 0;
        }
        else if(checkSpecific(data.username) == 0)
        {
            printf("\t=> Invalid - Do not enter a special character\n");
            check = 0;
        }
        else if(lenghtUsername(data.username) == 0)
        {
            printf("\t=> Invalid - Must contain 6-16 characters\n");
            check = 0;
        }   
        else if(checkUniqueUsername(data.username) == 0)
        {
            printf("\t=> Invalid - This username already exists in the system\n");
            check = 0;
        }
        else
        {
            printf("\t>>> Username '%s' can be used",data.username);
            check = 1;
        }
        
        if(check == 1)
            break;
    }
}

/* This function checks the password from the user's enter.
 * If the password format is incorrect, it will send an error message.
 * The password must be entered both letters and numbers.
 * If the password entered is correct, the system will save.
 * Return: return 0 when the data has wrong format, return 1 when the data correctly.
 */
int enterPassword()
{
    int check = 1;          /* variable for checking the status */
    char input[MAX];        /* variable for reading data from user */

    printf("\n\n\tPassword rules:\n");
	printf("\t\t=> Characters and numeric are allowed in the password\n");
	printf("\t\t=> Password must contain a combination of numbers and characters\n");
	printf("\t\t=> Password must contain 8-16 characters\n");
	printf("\t\t=> No spaces are allow in the password\n");
    printf("\t\t=> No specials character are allow in the password\n");
    while(1)
    {
        printf("\n\tEnter your password: ");
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%[^\n]",data.password);

        if(checkSpace(data.password) == 0)
        {
            printf("\t=> Invalid - Must not include spaces\n");
            check = 0;
        }
        else if(checkSpecific(data.password) == 0)
        {
            printf("\t=> Invalid - Do not enter a special character\n");
            check = 0;   
        }
        else if(lenghtPassword(data.password) == 0)
        {
            printf("\t=> Invalid - Must contain 8-16 characters\n");
            check = 0;
        }
        else if(checkAllDigit(data.password) == 0)
        {
            printf("\t=> Invalid - Must have some character\n");
            check = 0;
        }
        else if(checkAllAlpha(data.password) == 0)
        {
            printf("\t=> Invalid - Must have some digit\n");
            check = 0;
        }
        else
        {
            printf("\t>>> This password can be used");
            check = 1;
        }
            
        if(check == 1)
            break;
    }
    return check;   
}