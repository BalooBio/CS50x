#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// prototype functions
int count_letters(string text);

int count_words(string text);

int count_sentences(string text);

int main(void)
{
    // Prompt user for text
    string text = get_string("Text: ");
    float letters = count_letters(text);
    float words = count_words(text);
    float sentences = count_sentences(text);
    int index = round((0.0588 * (letters / words) * 100 - 0.296 * (sentences / words) * 100) - 15.8);
    // print grade level of text
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// Function to count letters in text
int count_letters(string text)
{
    int letters = 0;
    int length = strlen(text);
    // Get number of letters in string
    for (int i = 0; i < length; i++)
    {
        if (isupper(text[i]) || islower(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text)
{
    int words = 1;
    int length = strlen(text);
    //Get number of words in a string
    for(int i = 0; i < length; i++)
    {
        if ((text[i]) == ' ')
        {
            words++;
        }
    }
    return words;
}

int count_sentences(string text)
{
    int sentences = 0;
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if ((text[i]) == '.' || (text[i]) == '!' || (text[i]) == '?')
        {
            sentences++;
        }
    }

    return sentences;
}