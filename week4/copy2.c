#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
/// to use malloc
#include <stdlib.h>

int main(void)
{
    char *s = get_string("s: ");

    /// + 1 below is for the null character.
    /// In cases of error, where there is no memory available, malloc returns NULL, which is the address 0
    /// Which is not the same as NUL, which is the pointer to 0
    /// anyway, this means we should check for error
    char *t = malloc(strlen(s) + 1);
    // Error checking
    if (t == NULL)
    {
        return 1;
    }

    /// using i <= n here because we want to capture the null character as well
    for (int i = 0, n = strlen(s); i <= n; i++)
    {
        t[i] = s[i];
    }


    // Error checking in case the user enters 0 for s
    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    printf("s: %s\n", s);
    printf("t: %s\n", t);

    free(t);

}
