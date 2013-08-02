/*
*  One off program to create a single character file
*  This will be huffman coded by ~cs50/huff, and result in a single bit huffman binary file
*  This file can then be used for error checking the case of a single bit input to the puff program
*/



#include <stdio.h>

int main (void)
{
    int c = 97;
    FILE* fp = fopen("single.txt", "w");
    fputc(c, fp);
    return 0;
}
