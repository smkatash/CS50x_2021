#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


int main(void)
{
    //Prompt userinput for a text
    string text = get_string("Text: ");
    int count_letter = 0;
    int count_word = 1;
    int count_sent = 0;


    for (int i = 0; i < strlen(text); i++)
    {
        //Count letters
        if (isalpha(text[i]))
        {
            count_letter += 1;
        }
        //Count words
        else if (isspace(text[i]) && isalpha(text[i + 1]))
        {
            count_word += 1;
        }
        // Count sentences
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?' || text[i] == ':')
        {
            count_sent += 1;
        }
    }

    //Count averages
    float L = 100 * (float) count_letter / (float) count_word;
    float S = 100 * (float) count_sent / (float) count_word;

    //Apply formula
    float index = (0.0588 * L) - (0.296 * S) - 15.8;
    float grade = round(index);

    //Print grade results
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (1 <= grade && grade <= 16)
    {
        printf("Grade %i\n", (int) grade);
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }

}




