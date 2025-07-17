
#include <cs50.h>
#include <math.h>
#include <stdio.h>

// function prototypes
int card_length(long card_numb);
int checksum(long ccnumb, int length);
string card_type(long ccnumb, int length);

int main(void)
{
    // Get credit card number from user
    long card_number;
    int length;
    string cc_type;

    card_number = get_long("Credit card #: ");
    length = card_length(card_number);

    // Check if length is valid based on card type
    if (length != 13 && length != 15 && length != 16)
    {
        printf("INVALID\n");
    }

    // Checksum
    else if (checksum(card_number, length) == false)
    {
        printf("INVALID\n");
    }

    // Determine card type
    else
    {
        cc_type = card_type(card_number, length);
        printf("%s\n", cc_type);
    }
}

int card_length(long card_numb)
{
    int count = 0;

    while (card_numb > 0)
    {
        card_numb /= 10;
        count++;
    }

    return count;
}

// funtion gives bool output and takes credit card number as input
int checksum(long ccnumb, int length)
{
    long divide_by;
    int last_numb;
    int new_numb;
    int starts_with;
    int group1 = 0;
    int group2 = 0;
    int that_number;

    // Loop through each digit of the credit card, from back to front
    for (int i = 0; i < length; i++)
    {
        // define number to divide ccnumb by based on i
        divide_by = pow(10, i);
        last_numb = (ccnumb / divide_by) % 10;

        if (i % 2 != 0)
        {
            new_numb = last_numb * 2;

            if (new_numb >= 10)
            {
                group1 += (new_numb % 10) + ((new_numb / 10) % 10);
            }

            else
            {
                group1 += new_numb;
            }
        }

        else if (i % 2 == 0)
        {
            group2 += last_numb;
        }

        if (i == length - 1)
        {
            that_number = group1 + group2;
        }
    }

    if (that_number % 10 == 0)
    {
        return true;
    }

    else
    {
        return false;
    }
}

// AMEX - 15 digits - Starts with 34 or 37
// Mastercard - 16 digits - Starts with 51, 52, 53, 54, or 55
// Visa - 13 or 16 digits - Starts with 4
string card_type(long ccnumb, int length)
{
    int first_digit;
    int second_digits;
    long divide_by1;
    long divide_by2;

    divide_by1 = pow(10, length - 1);
    divide_by2 = pow(10, length - 2);

    first_digit = (ccnumb / divide_by1) % 10;
    second_digits = (ccnumb / divide_by2);

    if (length == 15 && (second_digits == 34 || second_digits == 37))
    {
        return "AMEX";
    }

    else if ((length == 13 || length == 16) && first_digit == 4)
    {
        return "VISA";
    }

    else if (length == 16 && (second_digits == 51 || second_digits == 52 || second_digits == 53 ||
                              second_digits == 54 || second_digits == 55))
    {
        return "MASTERCARD";
    }

    else
    {
        return "INVALID";
    }
}
