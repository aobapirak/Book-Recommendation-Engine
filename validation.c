/* 
 *  validation.c 
 *
 *  This file compiles a function for validating a user's registration.
 *
 *  Created by Kasikan Wisetkami (Mook) ID: 63070503403
 *      on 17 April 2021
 *      Created: checkAlpha(), checkSpecific(), lenghtUsername(),
 *                lenghtPassword(), checkSpace()              
 *
 *  Updated by Chayathit Rattanapokil (Peach) ID: 63070503405 
 *      on 18 April 2021
 *      Edit: checkUniqueUsername(), checkAllDigit(), checkAllAlpha()
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "declareFunction.h"

/* This function verifies that the data is all characters and 
 * verifies that the first character is uppercase. 
 * Arguments:
 *      input   - The data entered by the user
 * Return 0 when the data is not a letter, Return -1 when the first 
 * character is not uppercase, Return 1 when the data is a letter.
 */
int checkAlpha(char input[])
{
    int check = 1;        /* variables to return values ​​in a valid or invalid format */
    int i = 0;            /* counting of loop */
        
    for(i = 0; i < strlen(input); i++)
    {
        if(isspace(input[i]))
    		continue;

        if(!isalpha(input[i]))
            check = 0;    
        else if(!isupper(input[0]))
            check = -1;
    }
    return check;
}

/* This function checks if the data contains special characters in the data 
 * contain special characters.
 * Arguments:
 *      input   - The data entered by the user
 * Return 0 when the data has special characters, Return 1 when the data does not
 */
int checkSpecific(char input[])
{
    int check = 1;      /* variables to return values ​​in a valid or invalid format */
	int i = 0;          /* counting of loop */
	
	for(i = 0; i < strlen(input); i++)
	{
        if(isspace(input[i]))
            continue;
		if(ispunct(input[i]))
			check = 0;      
	}
	return check;
}

/* This function checks if the username has more than or less than determined.
 * Arguments:
 *      username   - The username entered by the user
 * Return 0 when the data is less than 6 or more than 16 characters, 
 * Return 1 when the data does not exceed the number of characters allowed.
 */
int lenghtUsername(char username[])
{
    int check = 1;      /* variables to return values ​​in a valid or invalid format */
	int i = 0;          /* counting of loop */
    int value;          /* keep the number of passwords */

    value = strlen(username);
    if((value > 16) || (value < 6))
        check = 0;

  return check;
}

/* This function checks if the password has more than or less than determined.
 * Arguments:
 *      password   - The password entered by the user
 * Return 0 when the data is less than 8 or more than 16 characters, 
 * Return 1 when the data does not exceed the number of characters allowed.
 */
int lenghtPassword(char password[])
{
    int check = 1;      /* variables to return values ​​in a valid or invalid format */
	int i = 0;          /* counting of loop */
    int value;          /* keep the number of passwords */

    value = strlen(password);
    if((value > 16) || (value < 8))
        check = 0;

    return check;
}

/* This function checks if the data has space.
 * Arguments:
 *      input   - The data entered by the user
 * Return 0 when the data has space, Return 1 when the data does not space.
 */
int checkSpace(char input[])
{
    int check = 1;      /* variables to return values ​​in a valid or invalid format */
	int i = 0;          /* counting of loop */
	
	for(i = 0; i < strlen(input); i++)
	{
		if(input[i] == ' ')
			check = 0;      
	}
	return check;
}

/* This function checks if username has found in the database.
 * Compare the information between the user entered and 
 * the information in the database, where data is read from the file.
 * If there is the same username in the database, it will send an error message to user.
 * Arguments:
 *      user   - The username entered by the user
 * Return 0 when the data has space, Return 1 when the data does not space.
 */
int checkUniqueUsername(char user[])
{
    int check = 1;            /* variables to return values ​​in a valid or invalid format */
    char name[MAX];           /* keep name from being read from file */
    char username[MAX];       /* keep username from being read from file */
    char password[MAX];       /* keep password from being read from file */
    char input[MAX];          /* variable for reading file data */

    FILE* pInfile = NULL;     /* pointer variable to read file */

    pInfile = fopen("account.txt", "r");
    if(pInfile == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    while((fgets(input,sizeof(input),pInfile) != NULL))
    {
        sscanf(input,"Name: %[^,],Username: %[^,],Password: %[^\n]",name,username,password);

        if(strcasecmp(username,user) == 0)
            check = 0;
    }
    return check;
}

/* This function checks if the data contains only numbers.
 * Arguments:
 *      password   - The password entered by the user
 * Return 0 when there are numbers in the data, 
 * Return 1 when there are no numbers in the data.
 */
int checkAllDigit(char password[])
{
    int check = 1;      /* variables to return values ​​in a valid or invalid format */
    int i = 0;          /* counting of loop */

    for(i = 0; i < strlen(password); i++)
    {
        if(isdigit(password[i]))
            check = 0;
        else
        {
            check = 1;
            break;
        }
    }
    return check;
}

/* This function checks if the data contains only alphabets. 
 * Arguments:
 *      input   - The input entered by the user
 * Return 0 when there are alphabets in the data,
 * Return 1 when there are no alphabets in the data.
 */
int checkAllAlpha(char input[])
{
    int check = 1;      /* variables to return values ​​in a valid or invalid format */
    int i = 0;          /* counting of loop */

    for(i = 0; i < strlen(input); i++)
    {      
        if(isalpha(input[i]))
            check = 0;
        else
        {
            check = 1;
            break;
        }
    }
    return check;
}