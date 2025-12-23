#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace(char *before, char *old_sub, char *new_sub);

int main(int argc, char* argv[])
{

    char string[] = "Hate the sin, love the sinner.";
    char *result = replace(string, "the", "a");

    printf("before: %s\n", string);
    printf(" after: %s\n", result);

    free(result);
    return 0;
}

char *replace(char *before, char *old_sub, char *new_sub)
{
    int old_len = strlen(old_sub);
    int new_len = strlen(new_sub);
    int before_len = strlen(before);

    char *after;

    if (old_len == new_len)
    {
        after = malloc((before_len + 1) * sizeof(char));
    }
    else
    {
        int occurrences = 0;
        int i = 0;
        while (i < before_len)
        {
            if (strstr(&before[i], old_sub) == &before[i])
            {
                occurrences++;
                i += old_len;
            }
            else
            {
                i++;
            }
        }

        int sub_diff = new_len - old_len;
        int after_len = before_len;
        after_len += occurrences * sub_diff;

        after = malloc((after_len + 1) * sizeof(char));
    }

    int i = 0;
    int j = 0;

    while (i < before_len)
    {
        if (strstr(&before[i], old_sub) == &before[i])
        {
            strcpy(&after[j], new_sub);
            i += old_len;
            j += new_len;
        }
        else
        {
            after[j] = before[i];
            i++;
            j++;
        }
    }

    after[j] = '\0';

    return after;
}