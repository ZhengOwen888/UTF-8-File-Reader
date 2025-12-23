#include <stdlib.h>
#include <stdio.h>
#include <string.h>



void ComputeLPSArray(char *pattern, int lps_size, int *lps)
{
    // track the current number of indexes
    int prefix_idx= 0;

    // The first character is only one letter so the prefix is always 0
    lps[0] = 0;

    // index 0 is skipped to detect prefixes after the first character.
    int pattern_idx = 1;

    while (pattern_idx < lps_size)
    {
        if (pattern[prefix_idx] == pattern[pattern_idx])
        {
            prefix_idx++;
            lps[pattern_idx] = prefix_idx;
            pattern_idx++;
        }
        else if (prefix_idx > 0)
        {
            prefix_idx = lps[prefix_idx - 1];
        }
        else
        {
            lps[pattern_idx] = 0;
            pattern_idx++;
        }
    }
}

int* FindAllOcurrences(char *text, char *pattern, int *count_occurence)
{
    int text_len = strlen(text);
    int pattern_len = strlen(pattern);

    int *lps = malloc(sizeof(int) * pattern_len);
    int *result_indices = malloc(sizeof(int) * text_len);
    *count_occurence = 0;

    ComputeLPSArray(pattern, pattern_len, lps);

    int text_idx = 0;
    int pattern_idx = 0;

    while (text_idx < text_len)
    {
        if (pattern[pattern_idx] == text[text_idx])
        {
            pattern_idx++;
            text_idx++;

            if (pattern_idx == pattern_len)
            {
                result_indices[*count_occurence] = text_idx - pattern_idx;
                pattern_idx = lps[pattern_idx - 1];
                (*count_occurence)++;
            }
        }
        else
        {
            if (pattern_idx != 0)
            {
                pattern_idx = lps[pattern_idx - 1];
            }
            else
            {
                text_idx++;
            }
        }
    }

    free(lps);
    return result_indices;
}

int main()
{
    char *text = "ababababab";
    char *pattern = "abab";
    int count_occurence = 0;
    int *all_occurence = FindAllOcurrences(text, pattern, &count_occurence);

    printf("Occurences: %d\n", count_occurence);
    for (int i = 0; i < count_occurence; i++)
    {
        printf("Index: %d\n", all_occurence[i]);
    }

    free(all_occurence);

    return 0;
}