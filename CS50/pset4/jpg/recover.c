/****************************************************************************
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 ***************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
 
typedef uint8_t BYTE;

 
int main(void) {
 
  FILE* fp = fopen("card.raw", "r");
   if (fp == NULL)
    {
        printf("Could not open file");
        return 2;
    }


  
  FILE* outptr = NULL;
  char title[8];
  int file_num = 0;

  
  BYTE signature1[4] = {0xff,0xd8,0xff,0xe0};
  BYTE signature2[4] = {0xff,0xd8,0xff,0xe1};
  BYTE bloc_buffer[512] = {0};

 

  
  while (feof(fp) == 0) {

             
       if ((memcmp(bloc_buffer, signature1, 4) == 0 || memcmp(bloc_buffer, signature2, 4) == 0)) {
          
          if (outptr != NULL)
             fclose(outptr);
             
          // make title
          sprintf(title, "%03d.jpg", file_num);
          file_num++;
          // make outfile and check if valid
          outptr = fopen(title, "w");
              if (outptr == NULL)  {
                   fclose(fp);
                   fprintf(stderr, "Could not create outfile");
                   return 3;
              }
       }
   
       if (file_num > 0) {
            fwrite(&bloc_buffer, sizeof(BYTE) * 512, 1, outptr);       
       }   
      fread(&bloc_buffer, sizeof(BYTE) * 512, 1, fp);
    }
    
    fclose(fp);
    fclose(outptr);
    
    return 0;
  


}
