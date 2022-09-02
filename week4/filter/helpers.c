#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //iterate through the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //get pixel values of colors from image
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;
            float red = image[i][j].rgbtRed;
            
            //average of all pixel values
            float average = (blue + green + red) / 3;
            average = round(average);
            
            //update pixel values of colors
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //iterate through the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //get pixel values of colors from image
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;
            
            
            //apply sepia formula 
            int sepiaBlue = round(.272 * red + .534 * green + .131 * blue);
            int sepiaGreen = round(.349 * red + .686 * green + .168 * blue);
            int sepiaRed = round(.393 * red + .769 * green + .189 * blue);
        
            
            //set the top pixel value and update the rest
            if (sepiaBlue < 255)
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }
            
            if (sepiaGreen < 255)
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }
            
            if (sepiaRed < 255)
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }
            
        }
    }
    return;
}
    
  

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //iterate through the image
    for (int i = 0; i < height; i++)
    {
        //divide width by half to loop the iteration from side to side
        for (int j = 0; j < round(width / 2); j++)
        {
            //swap the pixel values along the width
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp; 
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img_copy[height][width];

    for (int i = 0; i < height; i++)
    {
        //Copy the original image to a new one
        for (int j = 0; j < width; j++)
        {
            img_copy[i][j] = image[i][j];
        }
    }
        
        
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue_sum = 0;
            int green_sum = 0;
            int red_sum = 0;
            int total = 0;
            
            //add current pixel value
            blue_sum += img_copy[i][j].rgbtBlue;
            green_sum += img_copy[i][j].rgbtGreen;
            red_sum += img_copy[i][j].rgbtRed;
            total++;
            
            //Check & add the pixel values bottom left corner
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                blue_sum += img_copy[i - 1][j - 1].rgbtBlue;
                green_sum += img_copy[i - 1][j - 1].rgbtGreen;
                red_sum += img_copy[i - 1][j - 1].rgbtRed;
                total++;
            }
            
            //Check and add the pixel value at the bottom of centered pixel
            if (i - 1 >= 0 && j >= 0)
            {
                blue_sum += img_copy[i - 1][j].rgbtBlue;
                green_sum += img_copy[i - 1][j].rgbtGreen;
                red_sum += img_copy[i - 1][j].rgbtRed;
                total++;
            }
            
            //Check and add the pixel value of bottom right corner
            if (i - 1 >= 0 && j + 1 < width)
            {
                blue_sum += img_copy[i - 1][j + 1].rgbtBlue;
                green_sum += img_copy[i - 1][j + 1].rgbtGreen;
                red_sum += img_copy[i - 1][j + 1].rgbtRed;
                total++;
            }
            
            //Check and add the pixel value to the left
            if (j - 1 >= 0)
            {
                blue_sum += img_copy[i][j - 1].rgbtBlue;
                green_sum += img_copy[i][j - 1].rgbtGreen;
                red_sum += img_copy[i][j - 1].rgbtRed;
                total++;
            }
             
            //Check and add the pixel value to the right
            if (j + 1 < width)
            {
                blue_sum += img_copy[i][j + 1].rgbtBlue;
                green_sum += img_copy[i][j + 1].rgbtGreen;
                red_sum += img_copy[i][j + 1].rgbtRed;
                total++;
            }
             
            //Check and add the pixel value of top left corner
            if (j - 1 >= 0 && i + 1 < height)
            {
                blue_sum += img_copy[i + 1][j - 1].rgbtBlue;
                green_sum += img_copy[i + 1][j - 1].rgbtGreen;
                red_sum += img_copy[i + 1][j - 1].rgbtRed;
                total++;
            }
             
            //Check and add the pixel value on the top of centered pixel ???
            if (i + 1 < height && j >= 0)
            {
                blue_sum += img_copy[i + 1][j].rgbtBlue;
                green_sum += img_copy[i + 1][j].rgbtGreen;
                red_sum += img_copy[i + 1][j].rgbtRed;
                total++;
            }
             
             
            //Check and add the pixel value on the top right
            if (i + 1 < height && j + 1 < width)
            {
                blue_sum += img_copy[i + 1][j + 1].rgbtBlue;
                green_sum += img_copy[i + 1][j + 1].rgbtGreen;
                red_sum += img_copy[i + 1][j + 1].rgbtRed;
                total++;
            }
             
             
            //Round an average and return pixel values to original image
            image[i][j].rgbtBlue = round(blue_sum / (total * 1.0));
            image[i][j].rgbtGreen = round(green_sum / (total * 1.0));
            image[i][j].rgbtRed = round(red_sum / (total * 1.0)); 
        }
    }
    return;
}
