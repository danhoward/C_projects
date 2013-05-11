/****************************************************************************
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 ***************************************************************************/
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: resize infile to outfile\n");
        return 1;
    }

    // remember filenames
    char* multiplier = argv[1];
    int size_param = atoi(multiplier);
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //resize outfile header bfSize, biHeight, biWidth, biSizeImage (size_param^2 * previous size)
    // need biSizeImage - padding * size_param^2 then check if padding needed and write back
    
    int in_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    bi.biWidth = bi.biWidth * size_param;
    bi.biHeight = bi.biHeight * size_param;
    
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    bf.bfSize = ((bi.biSizeImage - (in_padding)) * size_param * size_param) + (padding) + 54;
    bi.biSizeImage = bf.bfSize - 54;
    
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // this will be the padding on the expanded image
    // determine padding for scanlines
    

    // iterate over infile's scanlines
    for (int i = 0, biHeight = (abs(bi.biHeight) / size_param); i < biHeight; i++)
    {
      for (int x = 0; x < size_param; x++) {
        // iterate over pixels in scanline
        for (int j = 0; j < (bi.biWidth / size_param); j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            for (int m = 0; m < size_param; m++) {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
            
        }
         for (int k = 0; k < padding; k++)
            fputc(0x00, outptr);
            
         fseek(inptr, (-(bi.biWidth / size_param) * sizeof(RGBTRIPLE)), SEEK_CUR);
       
       }
        fseek(inptr, ((bi.biWidth / size_param) * sizeof(RGBTRIPLE)), SEEK_CUR);
        // skip over padding, if any
        fseek(inptr, in_padding, SEEK_CUR);
        
        // then add it back (to demonstrate how)
        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
