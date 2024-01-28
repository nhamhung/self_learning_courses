// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hash_index = hash(word);

    if (table[hash_index] == NULL)
    {
        return false;
    }
    else
    {
        struct node *node_ptr = table[hash_index];

        while (node_ptr != NULL)
        {
            if (strcasecmp(word, node_ptr->word) == 0)
            {
                return true;
            }

            node_ptr = node_ptr->next;
        }

        return false;
    }
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
    FILE *fp;

    fp = fopen(dictionary, "r");

    if (fp == NULL)
    {
        printf("Failed to open the file.\n");
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(fp, "%s", word) != EOF)
    {
        struct node *node_ptr = (struct node *)malloc(sizeof(struct node));

        if (node_ptr == NULL)
        {
            printf("Memory allocation failed.\n");
            return false;
        }

        strcpy(node_ptr->word, word);
        int hash_index = hash(node_ptr->word);

        if (table[hash_index] == NULL)
        {
            table[hash_index] = node_ptr;
        }
        else
        {
            node_ptr->next = table[hash_index]->next;
            table[hash_index]->next = node_ptr;
        }
    }

    fclose(fp);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int count = 0;

    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            struct node *node_ptr = table[i];

            while (node_ptr != NULL)
            {
                count += 1;
                node_ptr = node_ptr->next;
            }
        }
    }

    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            struct node *node_ptr = table[i];
            struct node *next_node_ptr;

            while (node_ptr != NULL)
            {
                next_node_ptr = node_ptr->next;
                free(node_ptr);
                node_ptr = next_node_ptr;
            }

            if (i == N - 1 && node_ptr == NULL)
            {
                return true;
            }
        }
        else
        {
            if (i == N - 1)
            {
                return true;
            }
        }
    }

    return false;
}
