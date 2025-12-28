#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char** FindAllOccurrence(const char *text, const char *substr, int *count_occurrence);

char* ReplaceSubstr(const char *src, const char *old_substr, const char *new_substr);

char* DeleteSubstr(const char *src, const char *substr);

void RemoveConsecutiveSpaces(char *src);