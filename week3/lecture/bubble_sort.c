#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int numbers[] = {20, 500, 10, 5, 100, 1, 50};

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6 - i; j++)
        {
            if (numbers[j] > numbers[j+1])
            {
                int temp = numbers[j];

                numbers[j] = numbers[j + 1];

                numbers[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < 7; i++)
    {
        printf("%d\n", numbers[i]);
    }

}
