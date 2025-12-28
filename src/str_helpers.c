#include "str_helpers.h"
#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char *ToUpper(char *src)
{
    char *temp_src = src;

    if (src == NULL)
    {
        perror("ToUpper failed to uppercase NULL");
        exit(1);
    }

    while ((*temp_src) != '\0')
    {
        *temp_src = toupper((unsigned char)(*temp_src));
        temp_src++;
    }

    return src;
}

char *ToLower(char *src)
{
    char *temp_src = src;

    if (src == NULL)
    {
        perror("ToLower failed to lowercase NULL");
        exit(1);
    }

    while ((*temp_src) != '\0')
    {
        *temp_src = tolower((unsigned char)(*temp_src));
        temp_src++;
    }

    return src;
}

const char** FindAllOccurrence(const char *text, const char *substr, int *count_occurrence)
{
    if (!text || !substr || !count_occurrence)
    {
        return NULL;
    }

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
    if (!src || !old_substr || !new_substr)
    {
        return NULL;
    }

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
    if (!src || !substr)
    {
        return NULL;
    }

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

bool IsDelimeter(const char* delimeters, int delimeter_count, char character)
{
    for (int i = 0; i < delimeter_count; i++)
    {
        if (character == delimeters[i])
        {
            return true;
        }
    }

    return false;
}

int WordCount(const char* src)
{
    if (!src)
    {
        return 0;
    }

    const char *delimeters = " .,;:'\"(){}[]!@#$%^&*=-_~<>?\\/\t\n";
    int delimeter_count = strlen(delimeters);

    int word_count = 0;
    int str_len = strlen(src);
    int i = 0;

    while (i < str_len)
    {
        if (!IsDelimeter(delimeters, delimeter_count, src[i]))
        {
            word_count++;
        }

        while (i < str_len && !IsDelimeter(delimeters, delimeter_count, src[i]))
        {
            i++;
        }

        while (i < str_len && IsDelimeter(delimeters, delimeter_count, src[i]))
        {
            i++;
        }
    }

    return word_count;
}

int CharacterCount(const char* src)
{
    if (!src)
    {
        return 0;
    }

    return strlen(src);
}

Map *WordFreq(const char *src)
{
    const char *delimeters = " .,;:'\"(){}[]!@#$%^&*=-_~<>?\\/\t\n";
    int delimeter_count = strlen(delimeters);

    char *temp_src = malloc(sizeof(char) * (strlen(src) + 1));
    if (temp_src == NULL)
    {
        perror("Calloc failed to allocate for WordFreq Temp String.");
        exit(1);
    }
    strcpy(temp_src, src);

    char *words = strtok(temp_src, delimeters);
    Map *word_freq = CreateMap();

    while (words != NULL)
    {
        MapEntry *entry = FindMapEntry(word_freq, words);

        if (entry != NULL)
        {
            entry->value_++;
        }
        else
        {
            InsertMapEntry(&word_freq, ToLower(words), 1);
        }

        words = strtok(NULL, delimeters);
    }

    free(temp_src);
    return word_freq;
}