#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;
 
int main(int argc, char *argv[])
{
    //Check the input usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    //Open and read the input file through pointer
    char *file = argv[1];
    FILE *input = fopen(file, "r");
    //Handle the response in case of an input file error 
    if (input == NULL)
    {
        printf("Invalid image\n");
        return 2;
    }
    
    //Create buffer with array bytes
    BYTE buffer[512];
    //Initialize the counter to count number of images
    int count = 0; 
    FILE *output = NULL;
    //Save the name of JPEGs
    char filename[8]; 
    
    //Loop until the end
    while (fread(&buffer, 512, 1, input) == 1)
    {
        //Search for a start of a new JPEG
        if (buffer[0] == 0xff & buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //Close previous JPEG, if not first one
            if (!(count == 0))
            {
                fclose(output);
            }
            //Initilaize file
            sprintf(filename, "%03i.jpg", count);
            output = fopen(filename, "w");
            count++;
        }
        //If JPEG found, write to file
        if (!(count == 0))
        {
            fwrite(&buffer, 512, 1, output);
        }
    }
    //Close all files
    fclose(input);
    fclose(output);
    return 0;

}