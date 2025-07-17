// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Counter to keep track of size of dictionary
int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash word to get table index of linked list
    int index = hash(word);

    // Use for-loop to search linked list for word with temp pointer called cursor
    for (node *cursor = table[index]; cursor != NULL; cursor = cursor->next)
    {
        // Return true if word is at that index in table
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
    }
    // Return false if not found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    // Open dictionary file and assign to pointer, dict
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // Create character array in memory to use for each word in dictionary, using fscanf
    char dictword[LENGTH + 1];

    // While loop to call fscanf on dictionary over and over until no words remaining
    // fscanf returns EOF when no strings remaining
    while (fscanf(dict, "%s", dictword) != EOF)
    {
        // Get hash # of dictword
        int index = hash(dictword);

        // Allocate memory for next node
        node *n = malloc(sizeof(node));

        // Track number of nodes in dict
        dict_size ++;

        // Copy dictword into word portion of the node
        strcpy(n->word, dictword);

        // If no other nodes at index
        if (table[index] == NULL)
        {
            table[index] = n;
        }

        // If other words at index
        else
        {
            n->next = table[index];
            table[index] = n;
        }
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (!&load)
    {
        return 0;
    }

    else;
    {
        return dict_size;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Counter to keep track of number of freed nodes
    int freed= 0;

    // Free all nodes in each linked list in table
    // For-loop to loop through table
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = table[i];

        // WHile-loop to loop through linked list
        while (tmp != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
            freed ++;
        }
    }

    if (freed == dict_size)
    {
        return true;
    }
    else
    {
        return false;
    }
}
