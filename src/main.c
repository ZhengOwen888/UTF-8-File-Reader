#include "str_helpers.h"

int main()
{
    char *oldstr = "Roses are red, Violets are blue. Sugar is sweet, And so are you.";
    char *newstr = ReplaceSubstr(oldstr, "are", "were");

    printf("Old String: %s\n", oldstr);
    printf("New String: %s\n", newstr);

    return 0;
}