#ifndef STRING_HELPERS_HPP
#define STRING_HELPERS_HPP

#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

char *ToUpper(char *src);

char *ToLower(char *src);

const char** FindAllOccurrence(const char *text, const char *substr, int *count_occurrence);

char* ReplaceSubstr(const char *src, const char *old_substr, const char *new_substr);

char* DeleteSubstr(const char *src, const char *substr);

void RemoveConsecutiveSpaces(char *src);

bool IsDelimeter(const char *delimeters, int delimeter_count, char character);

int WordCount(const char *src);

int CharacterCount(const char *src);

Map* WordFreq(const char *src);

#endif