# include <stdio.h>
/// dont need cs50 library if you use char * instead of string
/// s is already a pointer, its a char *, so its alread the address of a string, so you
/// dont have to preface s with &
/// conversely, s[0] is a character, so you need to specify that you ware looking to print
/// the address by adding & aread of it.

int main(void)
{
    char *s = "Hi!";
    printf("%c\n", *s);
    printf("%c\n", *(s + 1));
    // in this case, you are printing the string, but starting at the address one space ahead
    of the address s is pointing too.
    printf("%s\n", s + 1);
}
