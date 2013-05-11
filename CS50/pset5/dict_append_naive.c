/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "dictionary.h"

#define LENGTH 45
#define HASHTABLE_SIZE 27


typedef struct node {
    char word[LENGTH + 1];   // ideally dynamically allocate syze for given input word
    struct node* next;
}
node;

node* HASH_TABLE[HASHTABLE_SIZE];  // hash table is an array of pointers (to linked lists)

int count = 0; // counter for load to help implementation of size()

// hash function returns an integer that represents the proper index of HASH_TABLE pointer array
int hash(const char* word_in) {
    int index = 0;
    if (isalpha(word_in[0]))
        index = word_in[0] - 97;
    else if (word_in[0] == 39)
        index = 27;
        
    return index;
}

// create node function
node* create_node(void) {
    node* new = malloc(sizeof(node));
    if (new == NULL) {
       fprintf(stderr, "Issue allocating memory\n");
       return false; 
    }
   
    new->next = NULL;
    return new;
}



/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    
    /**
    * check reads in words from text then sees if it is in linked list at proper HASH_TABLE address
    * so, hash the word then linear probe with strcomp at each node along the list
    *
    */
   
   // had to copy const char word to editable char 
    char work[LENGTH+1];
    strcpy(work, word);
    
    // to lower - CAN I MAKE THIS MORE EFFICIENT WITH BITWISE OPERATION?
    for (int a = 0; work[a]; a++)
            work[a] = tolower(work[a]);

    /* creates node pointer toward same address as appropriate hash_table pointer, 
     * inserts word into hashtable addressed linked list        
    */
    node* cursor = HASH_TABLE[(hash(work))];
    if (cursor != NULL)  {
        while (true)  {
            if (strcmp(work, cursor->word) == 0) {
                return true;
            }
            else if (cursor->next == NULL)  {
                return false;
            }    
            cursor = cursor->next;
        }
     }
    
    else {
        return false;
    }
   
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    
    FILE* fp = fopen(dictionary, "r");
     if (fp == NULL) {
        printf("The file could not be opened.");
        return false;
     }
     // read entire dictionary
     while (feof(fp) == 0) {
        /*load individual \n delimited words into fixed size buffer char array word[LENGTH+1], when word ends load from buffer to hashtable
         * load using fscanf - stop at \n, copy to proper node->word pointed to by correct pointer based on check of first letter
         * ideally dynamically allocate buffer size then load that array into hash
        */
        node* new_ptr = create_node();
        
        if (fscanf(fp, "%s", new_ptr->word) < 1) {
            free(new_ptr);
            fclose(fp);
            return true;
        }
        
        
        // append node containing to linked list pointed to by HASH_TABLE[hash(new_ptr->word)]
        
        node* tmpr = HASH_TABLE[hash(new_ptr->word)]; // declares temp pointer to point at hashtable pointer at proper address
        
        while (true) {
            //head insertion
            if (tmpr == NULL) {
                HASH_TABLE[hash(new_ptr->word)] = new_ptr;
                free(tmpr);
                break;
            }
            // appending to end of linked list
            else if (tmpr->next == NULL) {
                 tmpr->next = new_ptr;
                 break;
            }
            tmpr = tmpr->next;
        }
     
     count++;   
     }
     
    
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    if (count > 0)
        return count;
    else
        return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
       node* cursor = HASH_TABLE[i];
       while (cursor != NULL) {
            node* tmp = cursor;
            cursor = cursor->next;
            free(tmp);
       }
       
    }
    
    return true;
}
