#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <cs50.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;
unsigned int hash_v;
unsigned int word_count; 
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    //Get a hash value
    hash_v = hash(word);
    //Set cursor and keep moving
    node *cursor = table[hash_v];
    while (cursor != NULL)
    {
        //Find matching word
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        //otherwise go to next
        cursor = cursor->next; 
    }
    return false;
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    //Source http://www.cse.yorku.ca/~oz/hash.html 
    //Hash each word to number 
    unsigned long hash = 5381;
    int c;
    
    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //Open file and read
    FILE *file = fopen(dictionary, "r");

    //Check for correctness
    if (file == NULL)
    {
        return false;
    }
    //Word space
    char word[LENGTH + 1];

    //Loop until EOF
    while (fscanf(file, "%s", word) != EOF)
    {
        //Allocate memory for new node
        node *n = malloc(sizeof(node));

        ////Check for correctness
        if (n == NULL)
        {
            return false;
        }

        //Copy the word into the node.word
        strcpy(n->word, word);

        //Hash function
        hash_v = hash(word);
        //New pointer
        n->next = table[hash_v];
        //Head to pointer
        table[hash_v] = n;
        word_count++;
    }


    //Close and return if success
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    //Check and return number of words
    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    //Itirate through each bucket and set cursor
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
   
        //Check cursor
        while (cursor != NULL)
        {
            //Create tmp and move it to next node
            node *tmp = cursor; 
            cursor = cursor->next;
            
            //free tmp
            free(tmp);
        }
        //If empty & end of tables return
        if (cursor == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
