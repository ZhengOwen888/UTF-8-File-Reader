#include "str_helpers.h"

int main()
{
    char *oldstr = "Roses are red, Violets are blue. Sugar is sweet, And so are you.";
    char *newstr = ReplaceSubstr(oldstr, "are", "were");

    printf("Old String: %s\n", oldstr);
    printf("New String: %s\n", newstr);

    char *deletedstr = DeleteSubstr(oldstr, "are");
    printf("Deleted String: %s\n", deletedstr);

    char spaces[] = "a   b   c   d";
    RemoveConsecutiveSpaces(spaces);
    printf("No Consec Space: %s\n", spaces);

    free(newstr);
    return 0;
}