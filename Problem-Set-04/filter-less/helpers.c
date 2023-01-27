#include "helpers.h"
#include <math.h>

#define RED_COLOR 0
#define GREEN_COLOR 1
#define BLUE_COLOR 2

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            // pegar cada valor de red, green e blue de cada pixel e conseguir a média deles;
            int rgbGray = round((image[row][column].rgbtBlue + image[row][column].rgbtGreen + image[row][column].rgbtRed) / 3.0);
            // aplicar a média pra cada pixer da image;
            image[row][column].rgbtBlue = rgbGray;
            image[row][column].rgbtGreen = rgbGray;
            image[row][column].rgbtRed = rgbGray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
          // pega o valor de cada pixel da image e coloca na variável;
          int originalRed = image[row][column].rgbtRed;
          int originalGreen = image[row][column].rgbtGreen;
          int originalBlue = image[row][column].rgbtBlue;

          // atualiza cada pixel pro menor valor entre 255 e o novo valor de cada pixel com base na fórmula do sepia dado já;
          image[row][column].rgbtRed = fmin(255, round((.393 * originalRed) + (.769 * originalGreen) + (.189 * originalBlue)));
          image[row][column].rgbtGreen = fmin(255, round((.349 * originalRed) + (.686 * originalGreen) + (.168 * originalBlue)));
          image[row][column].rgbtBlue = fmin(255, round((.272 * originalRed) + (.534 * originalGreen) + (.131 * originalBlue)));
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    // any pixel on the left side of the image should end up on the right and vice-versa;
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width / 2; column++)
        {
            temp = image[row][column]; // 'salva' os pixels que ta a esquerda na variavel temp;
            image[row][column] = image[row][width - column -1]; // coloca os pixels que ta na direita da imagem para o lado esquerdo;
            image[row][width - column - 1] = temp; // coloca agora os pixels que estava originalmente no lado esquerdo (salvo na variável) para o lado direito da imagem;
        }
    }
    return;
}


int getBlur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color_position)
{
    float count = 0;
    int sum = 0;
    for (int row = i - 1; row <= (1 + 1); row++)
    {
        for (int column = j - 1; column <= (j + 1); column++ )
        {
            if (row < 0 || row >= height || column < 0 || column >=height)
            {
                continue;
            }
            if(color_position == RED_COLOR)
            {
                sum += image[row][column].rgbtRed;
            }
            else if(color_position == GREEN_COLOR)
            {
                sum += image[row][column].rgbtGreen;
            }
            else
            {
                sum += image[row][column].rgbtBlue;
            }
            count ++
        }
    }
    return round(sum / count)
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width]; // criando uma nova array 2d pra salvar os pixels originais da imagem;
     for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            copy[row][column] = image[row][column];

        }
    }

     for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            image[row][column].rgbtRed = getBlur(row, column, height, width, RGBTRIPLE copy, RED_COLOR);
            image[row][column].rgbtGreen = getBlur(row, column, height, width, RGBTRIPLE copy, GREEN_COLOR);
            image[row][column].rgbtBlue = getBlur(row, column, height, width, RGBTRIPLE copy, BLUE_COLOR);
        }
    }
    return;
}
