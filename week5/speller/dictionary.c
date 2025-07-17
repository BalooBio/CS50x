// Implements a dictionary's functionality
#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26;

// Hash table
node *table[N];

// Counter to keep track of size of dictionary
int dict_size = 0;

// Returns true if word is in dictionary, else false
/////////////////////////////////////////////////////////////////////////////// inspected
bool check(const char *word)
{
    // Hash word to get table index of linked list
    int index = hash(word);

    // Use for-loop to search linked list for word with temp pointer called cursor
    for (node *cursor = table[index]; cursor != NULL; cursor = cursor->next)
    {
        // Return true if word is at that index in table
        if (strcasecmp(cursor->word, word) == 0)
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
    // Improved using first two letters of each word, rather than only the first
    // This raises N from 26 to 26^2
    // At first I thought I could just do the following ((word[0]-'A')  + (word[1]-'A'))
    // But this doesnt work, because AB produces the same hash value as same as BA. And BC produces
    // the same hash value as CB. etc. To account for this, use the following:
    // ((word[0]-'A') * 26  + (word[1]-'A'))
    // Also need to account for the single letter word "a"

    // Account for edge case of 'A' and 'I'
    if (word[1] == '\0')
    {
        return toupper(word[0]) - 'A';
    }

    else
    {
        return ((toupper(word[0]) - 'A') * 26) + ((toupper(word[0]) - 'A'));
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Returns true if all words from dictionary are loaded into hash table. Returns false if there
    // is an error.
    // Open dictionary file and assign to pointer, dict
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // Create character array, dictword, as buffer for fscanf to load each word in dictionary
    char dictword[LENGTH + 1];

    // Loop calling fscanf on dictionary over and over until no words remaining
    // fscanf returns EOF when no strings remaining
    while (fscanf(dict, "%s", dictword) != EOF)
    {
        // Allocate memory for next node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }

        // Copy dictword into node->word
        strcpy(n->word, dictword);

        // Get hash # of dictword
        int index = hash(dictword);

        // Set n->next to Null
        n->next = NULL;

        // Add node to hash table
        // If no other nodes at index, set table[index] to equal the new node, n
        if (table[index] == NULL)
        {
            table[index] = n;
        }

        // If other words at index, point new node, n, to the first node, and set table[index] to
        // equal new node, n
        else
        {
            n->next = table[index];
            table[index] = n;
        }

        // Track number of nodes in dict
        dict_size++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Free all nodes in each linked list in the hash table
    // loop to loop through each linked list in has table
    node *cursor = NULL;
    node *tmp = NULL;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        // Loop through linked list
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
