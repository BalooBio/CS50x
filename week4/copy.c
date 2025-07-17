#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main void
{
    string s = get_string("s: ");

    string t = s;

    t[0] = toupper(t[0]);

    /// This results in uppercased first leter in both s and t. Why? Hint: both s and t are char *'s. Thus they are pointing
    /// to an address. In this case, the same address.


}
