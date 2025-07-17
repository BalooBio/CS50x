#include <cs50.h>
#include <stdio.h>

//copy paste the first line of functions defined below main
int get_size(void);
void print_grid(int size);

int main(void)
{
    //get size of grid
    int n = get_size();

    //print the specified sized grid
    print_grid(n);
}

//funtion gives int output but doesnt take inputs(hints the (void)
int get_size(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1);
    return n; //return is needed to hand back the value to any function using this function
}

// funtion does not return output (hints void) but does take input int size
void print_grid(int size)
{
    for (int i = 1; i <= size; i++)
    {
        //print spaces
        for (int j = 0; j < size - i; j++)
        {
            printf(" ");
        }

        //print first set of bricks
        for (int k = size; k < size + i; k++)
        {
            printf("#");
        }

        //print 2 spaces
        printf("  ");

        //print second set of bricks
        for (int k = size; k < size + i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
