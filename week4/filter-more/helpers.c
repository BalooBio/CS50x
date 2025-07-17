#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sum = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            int average = (round) (sum / 3);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = average;
        }
    }
    return;
}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width) / 2; j++)
        {
            temp[i][j] = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            float sumBlue = 0.0, sumGreen = 0.0, sumRed = 0.0;
            for (int k = (i - 1); k <= (i + 1); k++)
            {
                for (int l = (j - 1); l <= (j + 1); l++)
                {
                    if ((k >= 0 && k <= height - 1) && (l >= 0 && l <= width - 1))
                    {
                        sumBlue += image[k][l].rgbtBlue;
                        sumGreen += image[k][l].rgbtGreen;
                        sumRed += image[k][l].rgbtRed;
                        count++;
                    }
                }
            }
            temp[i][j].rgbtBlue = round(sumBlue / count);
            temp[i][j].rgbtGreen = round(sumGreen / count);
            temp[i][j].rgbtRed = round(sumRed / count);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // used in final step where image.rgbt values are set equal to a double. Note that image.rgbt
    // values are bytes, not integers but c does not have a byte type. A byte equivalent in c is
    // unsigned char or uint8_t.
    typedef unsigned char byte;
    // Need to make temp image file that can be modified, since moidifying each pixel iteratively
    // will disrupt calculations for later pixels
    RGBTRIPLE temp[height][width];
    // My code first initialized all 3x3 arrays using array[2][2], but this resulted in an error..
    // Why?
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double GxB = 0, GxG = 0, GxR = 0;
            double GyB = 0, GyG = 0, GyR = 0;
            double newB = 0, newG = 0, newR = 0;

            // Must use different approach to identify edge cases, compared to the k and l for loops
            // used in blur Recreating the k and l loops using 2 matricies, Row[2][2] and
            // Column[2][2]

            int Row[3][3] = {{i - 1, i - 1, i - 1}, {i, i, i}, {i + 1, i + 1, i + 1}};

            int Column[3][3] = {{j - 1, j, j + 1}, {j - 1, j, j + 1}, {j - 1, j, j + 1}};

            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    if ((Row[x][y] >= 0 && Row[x][y] <= height - 1) &&
                        (Column[x][y] >= 0 && Column[x][y] <= width - 1))
                    {
                        GxB += (image[Row[x][y]][Column[x][y]].rgbtBlue * Gx[x][y]);
                        GxG += (image[Row[x][y]][Column[x][y]].rgbtGreen * Gx[x][y]);
                        GxR += (image[Row[x][y]][Column[x][y]].rgbtRed * Gx[x][y]);

                        GyB += (image[Row[x][y]][Column[x][y]].rgbtBlue * Gy[x][y]);
                        GyG += (image[Row[x][y]][Column[x][y]].rgbtGreen * Gy[x][y]);
                        GyR += (image[Row[x][y]][Column[x][y]].rgbtRed * Gy[x][y]);
                    }
                }
            }
            newB = round(sqrt(pow(GxB, 2) + pow(GyB, 2)));
            if (newB > 255)
            {
                newB = 255;
            }
            if (newB < 0)
            {
                newB = 0;
            }
            newG = round(sqrt(pow(GxG, 2) + pow(GyG, 2)));
            if (newG > 255)
            {
                newG = 255;
            }
            if (newG < 0)
            {
                newG = 0;
            }
            newR = round(sqrt(pow(GxR, 2) + pow(GyR, 2)));
            if (newR > 255)
            {
                newR = 255;
            }
            if (newR < 0)
            {
                newR = 0;
            }

            temp[i][j].rgbtBlue = (byte) round(newB);
            temp[i][j].rgbtGreen = (byte) round(newG);
            temp[i][j].rgbtRed = (byte) round(newR);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
