#include <cs50.h>
#include <stdio.h>

////// YAY I did it!

int main(void)
{
    int numbers[] = {20, 500, 10, 5, 100, 1, 50};

    for (int i = 0; i < 7; i++)
    {
        int lowest;

        for (int j = i; j < 7; j++)
        {

            if (j == i)
            {
                lowest = numbers[j];
            }

            if (numbers[j] < numbers[lowest])
            {
                lowest = j;
            }
        }

        int temp = numbers[i];

        numbers[i] = numbers[lowest];

        numbers[lowest] = temp;
    }

    for (int i = 0; i < 7; i++)
    {
        printf("%d\n", numbers[i]);
    }

    printf("\n");
}
