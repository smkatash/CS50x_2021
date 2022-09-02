#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


// Main function
int main(int argc, string argv[])
{
    //Check the key
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //Check the length of the key
    string key = argv[1];
    int n = strlen(key);
    if (n != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    //Check the letters
    for (int i = 0; i < n; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }

    //Check for repeated characters
    int match = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (tolower(key[j]) == tolower(key[i]))
            {
                match++;
            }
        }
    }
    if (match != 26)
    {
        printf("Key must contain no repeated characters!\n");
        return 1;
    }


    //Get plaintext
    string plain = get_string("plaintext: ");
    int plain_len = strlen(plain);

    //Assign ABC
    string abc = "abcdefghijklmnopqrstuvwxyz";
    int abc_len = strlen(abc);
    
    //Assign empty space for character arrays, + ending \0
    char cipher[plain_len + 1];
    cipher[plain_len] = '\0';
    for (int i = 0; i < plain_len; i++)
    {
        if (islower(plain[i]) != 0)
        {
            for (int j = 0; j < abc_len; j++)
            {
                if (abc[j] == plain[i])
                {
                    cipher[i] = tolower(key[j]);
                    break;
                }
            }
        }
        else if (isupper(plain[i]) != 0)
        {
            for (int j = 0; j < abc_len; j++)
            {
                if (abc[j] == tolower(plain[i]))
                {
                    cipher[i] = toupper(key[j]);
                    break;
                }
            }
        }
        else
        {
            cipher[i] = plain[i];
        }

    }

    //Print ciphertext
    printf("ciphertext: %s\n", cipher);
    return 0;
}