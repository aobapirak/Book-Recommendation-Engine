/*****************************************************************************
 *      This file using to create all structure that we using in our project
 *****************************************************************************/

#include "linkedListUtil.h"

#define MAX 256
#define KEYLEN 256
#define BOOKID 0
#define NAME 1
#define AUTHOR 2
#define GENRE 3
#define KEYWORD 4

typedef struct _user
{
    char username[MAX];         /* username's user */
    char password[MAX];         /* password's user */
    char name[MAX];             /* name's user */
    LIST_HANDLE record;         /* record purchase history */
    int bookcount;              /* count how many book bought */
    struct _user * leftChild;   /* ptr to left child of node */
    struct _user * rightChild;  /* ptr to right child of node */
} USER_T;

typedef struct _registor
{
    char name[MAX];         /* name of user in the database */
    char username[MAX];     /* username of user in the database */
    char password[MAX];     /* password of user in the database */
} REGIST_T;
REGIST_T data;

typedef struct _bookInfo
{
    char bookID[MAX];        /* unique id of book */
	char titleBook[MAX];     /* Name of book */
	char authorBook[MAX];    /* Author of book */
	char pageLength[MAX];    /* Length of book */
	char genre[MAX];         /* Genre of book */
	char keyword[MAX];       /* Keywords of book */
    int usercount;           /* count how many user bought */
    LIST_HANDLE record;      /* record purchase history */
	int similarityScore;     /* For counting similar book in Content-based */
}BOOK_T;

typedef struct _listbook
{
    int attribute;          /* just so we know which attribute/table is the key */
    char key[MAX];          /* the appropriate key - title, author, etc. */
    int count;              /* count */
    LIST_HANDLE bookList;   /* use linkedListUtil to simplify */
    struct _listbook* next; /* Next item on the list */            
}BOOKLIST_T;