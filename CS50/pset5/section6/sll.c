/*************************************************************************
 * sll.c
 *
 * Implements a simple singly-linked list structure for ints.
 ************************************************************************/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// the size of our test list: feel free to adjust as you wish!
#define TEST_SIZE 10

typedef struct node
{
    // the value to store in this node
    int i;

    // the link to the next node in the list
    struct node* next;
}
node;

// declare the first node of our list (as a global variable)
node* first = NULL;

//method to declare new node

node* create_node(int i) {
    node* new = malloc(sizeof(node));
    if (new == NULL) {
       fprintf(stderr, "Issue allocating memory\n");
       exit(1); 
    }
    
    new->i = i;
    new->next = NULL;
    return new;
}


/**
 * Returns the length of the list.
 */
int length(void)
{
    // TODO
    int length = 0;
    for (node* tmp = first; tmp != NULL; tmp = tmp->next) {
        
        length++;
    }
    return length;
    return 0;
}

/**
 * Returns true if a node in the list contains the value i and false
 * otherwise.
 */
bool contains(int i)
{
    // TODO
    for (node* tmp = first; tmp != NULL; tmp = tmp->next) {
        if (tmp->next->i == i)
            return true;
    }
    return false;
}

/**
 * Puts a new node containing i at the front (head) of the list.
 */
 
void prepend(int i)
{
    // TODO
    // should attempt to call create_node method
   /* node* new = malloc(sizeof(node));
    if (new == NULL) {
       fprintf(stderr, "Issue allocating memory\n");
       exit(1); 
    }
    */
    node* new = create_node(i);
    
    //new->i = i;
    new->next = first;
    first = new;
}

/**
 * Puts a new node containing i at the end (tail) of the list.
 */
void append(int i)
{
    // TODO
    node* new = malloc(sizeof(node));
    if (new == NULL) {
       fprintf(stderr, "Issue allocating memory\n");
       exit(1); 
    }
    
    new->i = i;
    new->next = NULL;

    node* tmpr = first;
    while (true) {
        
        if (tmpr == NULL) {
            first = new;
            free(tmpr);
            break;
        }
        else if (tmpr->next == NULL) {
             tmpr->next = new;
             break;
        }
        tmpr = tmpr->next;
    }
    
}

/**
 * Puts a new node containing i at the appropriate position in a list
 * sorted in ascending order.
 */
void insert_sorted(int i)
{
    
    
    // TODO
    node* new = malloc(sizeof(node));
    if (new == NULL) {
       fprintf(stderr, "Issue allocating memory\n");
       exit(1); 
    }
    
    new->i = i;
    new->next = NULL;
    
    
    // check list empty, instert head -> next traverse and check for end and middle
    
    //empty
    if (first == NULL) {
        first = new;
    }
    
    //head
    else if (new->i < first->i) {
        new->next = first;
        first = new;
    }
    
    else {
        node* tmpr = first;
        while(true) {
         
        //avoid duplicates
                if (tmpr->i == new->i) {
                    new->next = tmpr->next;
                    tmpr->next = new;
                    
                    break;
                }
           
                else if (tmpr->next == NULL) {
                    tmpr->next = new;
                    
                    break;
                }
            
            //check middle
                else if (tmpr->next->i > new->i) {
                    new->next = tmpr->next;
                    tmpr->next = new;
                    
                    break;
                }
            //update pointer position
                tmpr = tmpr->next;
         }   
    
    }
     
     
}

/**
 * Implements some simple test code for our singly-linked list.
 */
int main(void)
{
    printf("Prepending ints 0-%d onto the list...", TEST_SIZE);
    for (int i = 0; i < TEST_SIZE; i++)
    {
        prepend(i);
    }
    printf("done!\n");

    printf("Making sure that the list length is indeed %d...", TEST_SIZE);
    assert(length() == TEST_SIZE);
    printf("good!\n");

    printf("Making sure that values are arranged in descending order...");
    node* n = first;
    for (int i = 0; i < TEST_SIZE; i++)
    {
        assert(n != NULL);
        assert(n->i == TEST_SIZE - i - 1);
        n = n->next;
    }
    printf("good!\n");

    printf("Freeing the list...");
    while (first != NULL)
    {
        node* next = first->next;
        free(first);
        first = next;
    }
    printf("done!\n");

    printf("Appending ints 0-%d to the list...", TEST_SIZE);
    for (int i = 0; i < TEST_SIZE; i++)
    {
        append(i);
    }
    printf("done!\n");

    printf("Making sure that the list length is indeed %d...", TEST_SIZE);
    assert(length() == TEST_SIZE);
    printf("good!\n");

    printf("Making sure that values are arranged in ascending order...");
    n = first;
    for (int i = 0; i < TEST_SIZE; i++)
    {
        assert(n != NULL);
        assert(n->i == i);
        n = n->next;
    }
    printf("good!\n");

    printf("Freeing the list...");
    while (first != NULL)
    {
        node* next = first->next;
        free(first);
        first = next;
    }
    printf("done!\n");

    printf("Inserting %d random ints to the list...", TEST_SIZE);
    for (int i = 0; i < TEST_SIZE; i++)
    {
        insert_sorted(rand() % TEST_SIZE);
    }
    printf("done!\n");

    printf("Making sure that the list length is indeed %d...", TEST_SIZE);
    assert(length() == TEST_SIZE);
    printf("good!\n");

    printf("Making sure that values are arranged in sorted order...");
    n = first;
    int prev = 0;
    for (int i = 0; i < TEST_SIZE; i++)
    {
        assert(n != NULL);
        assert(n->i >= prev);
        prev = n->i;
        n = n->next;
    }
    printf("good!\n");

    printf("Freeing the list...");
    while (first != NULL)
    {
        node* next = first->next;
        free(first);
        first = next;
    }
    printf("done!\n");

    printf("\n********\nSuccess!\n********\n");

    return 0;
}





