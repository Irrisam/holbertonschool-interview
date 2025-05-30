#include <stdlib.h>
#include <string.h>
#include "substring.h"

/**
 * hash_string - Simple hash function for strings
 * @str: String to hash
 * @len: Length of the string
 * Return: Hash value
 */
static unsigned int hash_string(const char *str, int len)
{
    unsigned int hash = 5381;
    int i;
    
    for (i = 0; i < len; i++)
        hash = ((hash << 5) + hash) + str[i];
    
    return hash;
}

/**
 * compare_strings - Compare two strings of given length
 * @s1: First string
 * @s2: Second string
 * @len: Length to compare
 * Return: 1 if equal, 0 otherwise
 */
static int compare_strings(const char *s1, const char *s2, int len)
{
    int i;
    
    for (i = 0; i < len; i++)
        if (s1[i] != s2[i])
            return 0;
    return 1;
}

/**
 * find_substring - Finds all starting indices of substrings in s that are
 *                  concatenations of all words in the words array
 * @s: The string to scan
 * @words: Array of words to find (all same length)
 * @nb_words: Number of words in the words array
 * @n: Pointer to store the number of indices found
 *
 * Return: Dynamically allocated array of indices, or NULL if none found
 */
int *find_substring(char const *s, char const **words, int nb_words, int *n)
{
    int s_len, word_len, total_len;
    int *result = NULL;
    int result_size = 0;
    int result_capacity = 10;
    int i, j, k;
    int *word_count = NULL;
    int *word_used = NULL;
    unsigned int *word_hashes = NULL;
    
    /* Initialize return count */
    *n = 0;
    
    /* Handle edge cases */
    if (!s || !words || nb_words == 0 || !words[0])
        return NULL;
    
    s_len = strlen(s);
    word_len = strlen(words[0]);
    total_len = word_len * nb_words;
    
    /* If total length exceeds string length, no solution */
    if (total_len > s_len)
        return NULL;
    
    /* Allocate initial result array */
    result = malloc(result_capacity * sizeof(int));
    if (!result)
        return NULL;
    
    /* Allocate word tracking arrays */
    word_count = calloc(nb_words, sizeof(int));
    word_used = calloc(nb_words, sizeof(int));
    word_hashes = malloc(nb_words * sizeof(unsigned int));
    
    if (!word_count || !word_used || !word_hashes)
    {
        free(result);
        free(word_count);
        free(word_used);
        free(word_hashes);
        return NULL;
    }
    
    /* Calculate hashes for all words and count occurrences */
    for (i = 0; i < nb_words; i++)
    {
        word_hashes[i] = hash_string(words[i], word_len);
        /* Count occurrences of each unique word */
        for (j = 0; j <= i; j++)
        {
            if (compare_strings(words[i], words[j], word_len))
                word_count[j]++;
        }
    }
    
    /* Check each possible starting position */
    for (i = 0; i <= s_len - total_len; i++)
    {
        /* Reset word usage counter */
        memset(word_used, 0, nb_words * sizeof(int));
        
        /* Try to match all words starting from position i */
        for (j = 0; j < nb_words; j++)
        {
            const char *substr = s + i + j * word_len;
            unsigned int substr_hash = hash_string(substr, word_len);
            int found = 0;
            
            /* Check if this substring matches any word */
            for (k = 0; k < nb_words; k++)
            {
                if (substr_hash == word_hashes[k] && 
                    compare_strings(substr, words[k], word_len))
                {
                    /* Check if we haven't used this word too many times */
                    if (word_used[k] < word_count[k])
                    {
                        word_used[k]++;
                        found = 1;
                        break;
                    }
                }
            }
            
            /* If no matching word found, break */
            if (!found)
                break;
        }
        
        /* Check if all words were used */
        if (j == nb_words)
        {
            /* Expand result array if needed */
            if (result_size >= result_capacity)
            {
                result_capacity *= 2;
                int *new_result = realloc(result, result_capacity * sizeof(int));
                if (!new_result)
                {
                    free(result);
                    free(word_count);
                    free(word_used);
                    free(word_hashes);
                    return NULL;
                }
                result = new_result;
            }
            
            /* Add current index to result */
            result[result_size++] = i;
        }
    }
    
    /* Clean up */
    free(word_count);
    free(word_used);
    free(word_hashes);
    
    /* Set output count */
    *n = result_size;
    
    /* Return NULL if no results found */
    if (result_size == 0)
    {
        free(result);
        return NULL;
    }
    
    /* Resize result array to exact size */
    result = realloc(result, result_size * sizeof(int));
    
    return result;
}
