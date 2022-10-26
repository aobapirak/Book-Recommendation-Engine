/* 
 * chainedHashTable.c
 *
 * Implementation of abstractHashTable.h that uses a chained
 * hash table. The calling program supplies the hashing function
 * as part of the initialization.
 *
 * Limitation: this implementation will not work well for duplicate
 * keys. It will store both but the returned data is unpredictable.
 *
 * Limitation: this implementation assumes keys are strings 
 * less than 128 chars long
 *
 *   Created by Sally Goldin on 5 March 2012 for CPE 113
 *   Updated to explicity keep track of list head and tail on
 *       26 March 2013
 * 
 *   Modified with permission by [Apirak Senarak (Aob)] on [17 April 2021]
 *      Edit: init, free, insert, lookup to hold more table For example, [attribute][data]
 *  
 *   Modified with permission by [Poonyavee Wongwisetsuk (Pup)] on [23 May 2021]   
 *      Additional: freeRecordAndBookList() to free LIST HANDLE in structure
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "abstractHashTable.h"
#include "linkedListUtil.h"
#include "structure.h"

//#define KEYLEN 128

/* Structure for table elements */
typedef struct _hashItem
{
    char key[KEYLEN];              /* copy of the key */
    void* data;                    /* data */
    struct _hashItem * next;       /* next item in the bucket if any */
} HASH_ITEM_T;

/* Structure for list with head and tail */
typedef struct _linkedList
{
    HASH_ITEM_T* head;             /* first item in list - null if list empty*/
    HASH_ITEM_T* tail;             /* last item in the list */
} LINKED_LIST_T;

/* Hash function - set by hashTableInit  */
unsigned int (*hashFn)(char* key) = NULL;

static LINKED_LIST_T ** table = NULL;  /* we will allocate our table based on
                                       * initialization arguments and store it
                                       * here 
                                       */     
static int tableSize = 0;     /* size of the table */
static int itemCount = 0;     /* keep track of current number of stored items */

/* Based on code by Sally Goldin from [Lab8: hashDictionary.c]
 * - Used with permission.
 * Robust hash function that uses bitwise operations to
 * modify string values. Adapted from Kyle Loudon,
 * "Mastering Algorithms with C"
 */
unsigned int bitwiseOpHash(char* key)
{
    unsigned int result = 0;
    unsigned int tmp = 0;
    int size = hashTableSize();
    int i = 0;
    for (i = 0; i < strlen(key); i++)
    {
        /* shift up four bits then add in next char */ 
        result = (result << 4) + key[i];
        if (tmp = (result & 0xf0000000))  /* if high bit is set */
        {
            /* XOR result with down shifted tmp */
            result = result ^ (tmp >> 24);
            /* then XOR with tmp itself */
            result = result ^ tmp;
        }
    }
    result = result % size;   /* make it fit in the table size */ 
    return result;
}


/* Return the number of slots in the hash table.
 */
int hashTableSize()
{
    return tableSize;
}


/* Return the number of items currently stored in the hash table.
 */
int hashTableItemCount()
{
    return itemCount;
}
 
/* Initialize the hash table.
 * Arguments
 *    size                - How many slots in the table
 *                          Must be 1 or greater. We assume the caller
 *                          has checked this.
 *    hashFunction        - Function that takes a string and returns an int
 *                          which will be the index into the table.
 * Return 1 if successful, 0 if some error occurred.
 *
 * Modified with permission by [Apirak Senarak (Aob)] on [17-Apr-2021].
 *      Additional: allocate the table 2 elements [attribute][data]
 *                  first element (attribute) allocation size = 5
 *                  and second element (data)
 */
int hashTableInit(int size, unsigned int (*hashFunction)(char* key))
{
    int bOk = 1;
    int i = 0;
    /* free the old table, if any */
    hashTableFree();
    hashFn = hashFunction;
    tableSize = size;
    /* try to allocate the table, which will store pointers
     * to LINKED_LIST_T elements.
     */
    table = (LINKED_LIST_T**) calloc(5, sizeof(LINKED_LIST_T*));
    if (table == NULL)
    {
        printf("Error - allocation\n");
        exit(1);
    }

    /* allocation each attribute */
    for (i = 0; i < 5; i++)
    {
        table[i] = (LINKED_LIST_T*) calloc(size,sizeof(LINKED_LIST_T));
        if (table[i] == NULL)
        {
            printf("Error - allocation\n");
            exit(1);
        }
    }
    
    if (table == NULL)
    {
       bOk = 0;
    }
    return bOk;
}


/* Free the hash table.
 * Modified with permission by [Apirak Senarak (Aob)] on [17-Apr-2021].
 *      Additional: free 2 elements which are [attribute][infomation]
 */
void hashTableFree()
{
    int i = 0;
    int j = 0;
    HASH_ITEM_T * pItem = NULL;
    HASH_ITEM_T * pNextItem = NULL;
    if (table != NULL) 
    {
        for (j = 0; j < 5; j++)
        {
            for (i = 0; i < tableSize; i++)
            {
                if (table[j][i].head != NULL)  /* something stored in this slot */
                {
                    pItem = table[j][i].head;
                    /* walk the linked list, freeing each item */
                    while (pItem != NULL)
                    {
                        pNextItem = pItem->next;
                        free(pItem);
                        pItem = pNextItem;
                    }
                    table[j][i].head = NULL;
                    table[j][i].tail = NULL;
                }
            }
        }
        free(table);
        table = NULL;
        tableSize = 0;
        itemCount = 0;
    }
}


/* Insert a value into the hash table.
 * Arguments 
 *    category            - attribute (0, 1, 2, 3)
 *    key                 - character string key
 *    data                - data to store in the table
 *    pCollision          - set to true if there was a collision storing
 *                          the data, else false 
 * Returns true (1) unless hash table has not been initialized or
 * we can't allocate memory, in which case returns false (0)
 * 
 * Modified with permission by [Apirak Senarak (Aob)] on [17-Apr-2021].
 *      Additional: Insert more category into the table
 */
int hashTableInsert(int category, char* key, void* data, int* pCollision)
{
    int bOk = 1;
    int hashval = 0;
    HASH_ITEM_T * pItem = NULL;
    HASH_ITEM_T * pTemp = NULL;
    if (table == NULL)  /* not initialized */
    {
      printf("Error - not initialized\n");
      return 0;
    }
    pItem = (HASH_ITEM_T*) calloc(1,sizeof(HASH_ITEM_T));
    if (pItem == NULL)
    {
        bOk = 0;  /* can't allocate memory */
    }
    else
    {
        strncpy(pItem->key,key,KEYLEN-1);
        pItem->data = data;
        hashval = hashFn(key); // bitwise
        //printf("Hash function for |%s| returns: %d\n",key,hashval);
        //printf("Added in table %d\n",category);
        if (table[category][hashval].head == NULL)
        {
            table[category][hashval].head = pItem;  /* bucket was empty */
            *pCollision = 0;              /* no collision */
        }
        else
        {
            *pCollision = 1;              /* We have a collision */
            /* put the new item at the end of the bucket list */
            table[category][hashval].tail->next = pItem;
        }
        table[category][hashval].tail = pItem;
        itemCount++;
    }
    return bOk;
}

/* Look up a value in the hash table.
 * Arguments
 *    category            - category of each book
 *    key                 - character string key
 * Returns the data associated with the key, or NULL if 
 * data associated with the key is not found.
 * 
 * Modified with permission by [Apirak Senarak (Aob)] on [17-Apr-2021].
 *      Additional: we will lookup the values both of category and 
 *                  information in the hash table
 */
void* hashTableLookup(int category, char* key)
{
    /* This function is similar to remove but we do not
     * change anything in the hashtable structure 
     */
    void* foundData = NULL;
    HASH_ITEM_T* pPrev = NULL;
    HASH_ITEM_T* pTemp = NULL;
    
    if (table != NULL)    /* initialized */
    {
        int hashval = hashFn(key);
        //printf("hashval = %d\n", hashval);
        if (table[category][hashval].head != NULL)   /* in the table */
        {    
            pTemp = table[category][hashval].head;
            while (pTemp != NULL)
            {                    
                if (strncmp(pTemp->key,key,KEYLEN-1) == 0)  /* match */
                {
                    foundData = pTemp->data;
                    pTemp = NULL;  /* this will make us exit loop */
                }
                else
                {
                    pPrev = pTemp;
                    pTemp = pTemp->next;  /* check next item */	  
                }
            } /* end loop through items in the bucket */
        } /* end if the key is in the table */
    } /* end if the hash table is initialized */      
    return foundData;
}

/*  Free LIST_HANDLE in structure of BOOK_T, BOOKLIST_T to free
*   all list in there, used with listDestroy()
*/
void freeRecordAndBookList()
{
    BOOK_T* pTempBook = NULL;   /* receive books that have been traverse in list */
    BOOKLIST_T* pTemp = NULL;   /* list - pointer to structure */
    HASH_ITEM_T * pItem = NULL; /* item to hold data */
    int j = 0;                  /* counter the loop */
    int i = 0;                  /* counter the loop */

    if (table != NULL) 
    {
        for (j = 0; j < 5; j++)
        {
            for (i = 0; i < tableSize; i++)
            {
                if (table[j][i].head != NULL)  /* something stored in this slot */
                {
                    pItem = table[j][i].head;
                    if(pItem != NULL)
                    {
                        pTemp = pItem->data;
                        if(pTemp != NULL)
                        {
                            listReset(pTemp->bookList);
                            pTempBook = listGetNext(pTemp->bookList);
                            while (pTempBook != NULL)
                            {              
                                if(pTempBook->record != NULL)
                                {
                                    listReset(pTempBook->record);
                                    listDestroy(pTempBook->record);
                                    pTempBook->record = NULL;
                                    //printf("Removed %s's record\n",pTempBook->titleBook);
                                }
                                pTempBook = listGetNext(pTemp->bookList);
                            } 

                            if(pTemp->bookList != NULL)
                            {
                                listDestroy(pTemp->bookList);
                                //printf("Removed a booklist [%d][%d]\n",j,i);
                            }
                        }
                    }
                }
            }
        }
    }
}