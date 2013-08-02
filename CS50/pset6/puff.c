/****************************************************************************
 * puff.c
 *
 * Harvard CS - fifty
 * Problem Set 6 
 *
 * De-compresses contents of a huff-compressed file in human-readable form.
 * Both compression and decompression should be run on 32-bit architecture.
 * 
 * This file was written by me, others in the makepath are provided.
 ***************************************************************************/
 
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "forest.h"
#include "huffile.h"
#include "tree.h"

#define FIRST 0
#define LAST 255


int main(int argc, char* argv[])        {
    // ensure proper usage
    if (argc != 3)                           {
        printf("Provide source and target files\nUsage: %s input\n", argv[0]);
        return 1;
    }
    
    char* outputfile = argv[2];
    FILE* outp = fopen(outputfile, "w");
    // errorcheck for valid file pointer
    if (outp == NULL) 
    {
        printf("couldn't open file for output");
        return 1;
    }

    // open input "huff" file format
    Huffile* input = hfopen(argv[1], "r");
    if (input == NULL)                        {
        printf("Could not open %s for reading.\n", argv[1]);
        return 1;
    }

    // read in header that provides encoding data
    Huffeader header;
    if (hread(&header, input) == false)        {
        hfclose(input);
        printf("Could not read header.\n");
        return 1;
    }

    // check for magic number
    if (header.magic != MAGIC)                {
        hfclose(input);
        printf("File was not huffed.\n");
        return 1;
    }

    // check checksum (this is the sum of the frequencies of all symbols in the huffed file)
    int checksum = header.checksum;
    for (int i = 0; i < SYMBOLS; i++)         {
        checksum -= header.frequencies[i];
    }
    if (checksum != 0)                        {
        hfclose(input);
        printf("File was not huffed.\n");
        return 1;
    }
    
    /*
    have to make forest then build trees for symbols in the file (based on freq in head)
    after picking two sibling trees, the first should be left child of parent, next right
    if only one character code it '0' 
    
    then: read in message by bit, starting at root. (if 1 go right if 0 go left) check
    after each read if you're at a leaf(null pt for both), if so, write character
    
    */
    
    // declare forest where binary tree will be build
    Forest* myforest = mkforest();                       
    
    // iterate over the header array looking for non-zero character frequencies
    // if one found, make a tree update its symbol and frequency from the array
    // and then plant the tree in the forest                                 
    for (int index = FIRST; index <= LAST; index++) {
        if (header.frequencies[index] != 0) {
           Tree* t = mktree();                            
           t->symbol = index;
           t->frequency = header.frequencies[index];                             
           plant(myforest, t);                          
        }
        
    }

 

    // need a special case for a single character huff file (one bit), if condition will check for it
    // first condition in "if" for a non-single bit, "else if" condiiton for single-bit
    if (myforest->first->tree != NULL && myforest->first->next != NULL) {
    
    // if not single-bit, iterate process of "pick-by-two" (two children) and plant one (a parent with sum frequency)
        while (myforest->first->next != NULL) 
        {
            Tree* parent_t = mktree();
            if (myforest->first->tree != NULL) 
            {
                parent_t->left = pick(myforest);
                parent_t->frequency = parent_t->left->frequency;
            }
            if (myforest->first->tree != NULL) // prevents segfault if no sibling to the right
            {
                parent_t->right = pick(myforest);
                parent_t->frequency += parent_t->right->frequency;
            }
            
            if (!(plant(myforest, parent_t)))   // this runs plant AND error checks if it fails
            {
                hfclose(input);
                rmforest(myforest);
                fprintf(stderr, "Error creating data structure");
                exit(1);
            }
               
        }    
    }
    // if next null AND something in first, do nothing, because your parent tree is already defined
    else if (myforest->first->tree != NULL && myforest->first->next == NULL)
    {
       
      
    }
    
    
    
    int bit;
    Tree* iterator = myforest->first->tree;
    while ((bit = bread(input)) != EOF)       {
        //  
        // read in bit see if it has nulls, if yes print if not, read in next keep moving the pointer
        // read in, check, if y - write and reset; if n - read check
        // 
        
        if (iterator->left != NULL || iterator->right != NULL) 
        {
            if (bit == 0) 
            {
                //go left......?
                iterator = iterator->left;
                //bit = bread(input);
            }
            
            else if (bit == 1) 
            {
                //go right  ?
                iterator = iterator->right;
                //bit = bread(input);
            }
        }
    
        if (iterator->left == NULL && iterator->right == NULL)
        {
            // now write characters to file
            fprintf(outp,"%c", iterator->symbol);
            iterator = myforest->first->tree;
        }
    }
    
    rmforest(myforest);  // frees memory
    hfclose(input);
    fclose(outp);
    
    
    return 0;
}

