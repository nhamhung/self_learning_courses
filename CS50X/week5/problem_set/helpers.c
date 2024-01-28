#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = 0;
            int green = 0;
            int blue = 0;
            int counter = 0;

            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (k >= 0 && j >= 0 && k < height && j < width)
                    {
                        red += image[k][j].rgbtRed;
                        green += image[k][j].rgbtGreen;
                        blue += image[k][j].rgbtBlue;
                        counter += 1;
                    }
                }
            }

            tmp[i][j].rgbtRed = red / counter;
            tmp[i][j].rgbtGreen = green / counter;
            tmp[i][j].rgbtBlue = blue / counter;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    RGBTRIPLE tmp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redGx = 0;
            int redGy = 0;
            int blueGx = 0;
            int blueGy = 0;
            int greenGx = 0;
            int greenGy = 0;

            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    int neighbor_x = i + k - 1;
                    int neighbor_y = j + l - 1;

                    if (neighbor_x >= 0 && neighbor_y >= 0 && neighbor_x < height && neighbor_y < width)
                    {
                        redGx += image[neighbor_x][neighbor_y].rgbtRed * Gx[k][l];
                        redGy += image[neighbor_x][neighbor_y].rgbtRed * Gy[k][l];
                        blueGx += image[neighbor_x][neighbor_y].rgbtBlue * Gx[k][l];
                        blueGy += image[neighbor_x][neighbor_y].rgbtBlue * Gy[k][l];
                        greenGx += image[neighbor_x][neighbor_y].rgbtGreen * Gx[k][l];
                        greenGy += image[neighbor_x][neighbor_y].rgbtGreen * Gy[k][l];
                    }
                }
            }

            tmp[i][j].rgbtRed = fmin(255, round(sqrt(pow(redGx, 2) + pow(redGy, 2))));
            tmp[i][j].rgbtBlue = fmin(255, round(sqrt(pow(blueGx, 2) + pow(blueGy, 2))));
            tmp[i][j].rgbtGreen = fmin(255, round(sqrt(pow(greenGx, 2) + pow(greenGx, 2))));
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }

    return;
}
