#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototype functions
bool only_digits(string p);

int main(int argc, string argv[])
{
    // Make sure argv[1] is a single digit 0 - 9
    if (argc != 2 || only_digits(argv[1]) == false)
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }

    // Convert argv[1] from a string to an integer
    int key_int = atoi(argv[1]);

    // prompt user for plaintext
    string p = get_string("Plaintext:  ");

    // Rotate the character if its a letter. If not a letter, return unchanged
    int p_length = strlen(p);

    printf("Ciphertext: ");

    for (int i = 0; i < p_length; i++)
    {
        if (isupper(p[i]))
        {
            printf("%c", ((p[i] - 65 + key_int) % 26) + 65);
        }

        else if (islower(p[i]))
        {
            printf("%c", ((p[i] - 97 + key_int) % 26) + 97);
        }

        else
        {
            printf("%c", p[i]);
        }
    }

    printf("\n");
    return 0;
}

// Make sure argv[1] is a single digit 0 - 9
bool only_digits(string key)
{
    int length = strlen(key);
    int char_number = 0;
    for (int i = 0; i < length; i++)
    {
        if (isdigit(key[i]))
        {
            char_number++;
            ;
        }

        else
        {
            return false;
        }
    }

    return true;
}
