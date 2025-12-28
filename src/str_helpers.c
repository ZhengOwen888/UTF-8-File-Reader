#include "str_helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const char** FindAllOccurrence(const char *text, const char *substr, int *count_occurrence)
{
    int text_len = strlen(text);
    int substr_len = strlen(substr);

    const char **matches = malloc(text_len * sizeof(char*));
    if (matches == NULL)
    {
        return NULL;
    }

    *count_occurrence = 0;

    const char *current = text;
    while((current = strstr(current, substr)) != NULL)
    {
        matches[*count_occurrence] = current;
        (*count_occurrence)++;
        current += substr_len;
    }

    return matches;
}

char* ReplaceSubstr(const char *src, const char *old_substr, const char *new_substr)
{
    int count_occurrence = 0;
    const char **all_occurrences = FindAllOccurrence(src, old_substr, &count_occurrence);
    if (all_occurrences == NULL)
    {
        perror("Malloc failed to allocate space to store all occurences.");
        exit(EXIT_FAILURE);
    }

    int old_substr_len = strlen(old_substr);
    int new_substr_len = strlen(new_substr);
    int src_len = strlen(src);
    int dest_len = src_len + count_occurrence * (new_substr_len - old_substr_len) + 1;

    char *dest = malloc(dest_len * sizeof(char));
    if (dest == NULL)
    {
        perror("Malloc failed to allocate space for destination.");
        exit(EXIT_FAILURE);
    }

    int dest_idx = 0;
    int src_idx = 0;
    int occur_idx = 0;

    while (src_idx < src_len)
    {
        if (occur_idx < count_occurrence && &src[src_idx] == all_occurrences[occur_idx])
        {
            strcpy(&dest[dest_idx], new_substr);
            src_idx += old_substr_len;
            dest_idx += new_substr_len;
            occur_idx++;
        }
        else
        {
            dest[dest_idx++] = src[src_idx++];
        }
    }
    dest[dest_idx] = '\0';

    free(all_occurrences);
    return dest;
}

char* DeleteSubstr(const char *src, const char *substr)
{
    return ReplaceSubstr(src, substr, "");
}

void RemoveConsecutiveSpaces(char *src)
{
    if (!src)
    {
        return;
    }

    char *read = src;
    char *write = src;
    bool prev_char_is_space = false;

    while (*read != '\0')
    {
        if (*read != ' ' || prev_char_is_space == false)
        {
            *write++ = *read;
        }

        prev_char_is_space = (*read == ' ') ? true : false;
        read++;
    }

   *write = '\0';
}