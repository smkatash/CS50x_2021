#include <cs50.h>
#include <stdio.h>


//Define function
int get_positive_int(string prompt);

//Get value
int main(void)
{
    int n = get_positive_int("Height: "); //user input of height
    
    for (int h = 0; h < n; h++) //height and lines
    {
        for (int w = n - h - 2; w >= 0; w--) //spaces
        {
            printf(" ");
        }
        for (int l = 0; l <= h; l++) //left pyramid
        {
            printf("#");
        }
        printf(" ");
        printf(" ");
        for (int r = 0; r <= h; r++) //right pyramid
        {
            printf("#");
        }
        printf("\n");
        
    }
}


//Prompts user to give a positive value
int get_positive_int(string prompt)
{
    int n;
    do
    {
        n = get_int("%s", prompt);
    }
    while (n < 1 || n > 8); //checking the range between 1 and 8
    return n;
}





