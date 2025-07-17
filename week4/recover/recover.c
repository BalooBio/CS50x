#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    // Open image for reading an return 1 if not able to do so
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Creat buffer for a block of data
    // Buffer is to temporarily store data
    uint8_t buffer[512];

    // While there's still data left to read from the memory card, creat JPEG's from the data
    int image_numb = 0;
    bool first_jpg = true;
    // Read 512 bytes into the buffer
    while (fread(&buffer, 1, 512, card) == 512)
    {
        // If the first 4 bytes indicate a new JPEG, begin writing to a new file
        // If not, continue writing to the previous file
        if (buffer[0] == 0xff & buffer[1] == 0xd8 & buffer[2] == 0xff & (buffer[3] & 0xf0) == 0xe0)
        {
            if (first_jpg)
            {
                char *filename = malloc(8);
                sprintf(filename, "%03i.jpg", image_numb);
                FILE *new_image = fopen(filename, "w");
                fwrite(&buffer, sizeof(buffer), 1, new_image);
                first_jpg = false;
                fclose(new_image);
                free(filename);
            }

            else
            {
                image_numb++;
                char *filename = malloc(8);
                sprintf(filename, "%03i.jpg", image_numb);
                FILE *new_image = fopen(filename, "w");
                fwrite(&buffer, sizeof(buffer), 1, new_image);
                fclose(new_image);
                free(filename);
            }
        }

        else
        {
            char *filename = malloc(8);
            sprintf(filename, "%03i.jpg", image_numb);
            FILE *new_image = fopen(filename, "a");
            fwrite(&buffer, sizeof(buffer), 1, new_image);
            fclose(new_image);
            free(filename);
        }
    }
    fclose(card);
}
