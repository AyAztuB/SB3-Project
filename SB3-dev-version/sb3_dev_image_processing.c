/*
 *
 * MIT License
 *
 * Copyright (c) 2022 AyAztuB
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *
 * AUTHOR
 *
 * AyAztuB (ayaztub@gmail.com) from https://github.com/AyAztuB/C_libs
 *
 */

#include "sb3_dev.h"
#include <err.h>
#include <math.h>

void SB3_DEV_SetError(SB3_DEV_errors_t error);

void SB3_DEV_FreeKernel(SB3_DEV_kernel_t* kernel)
{
    free(kernel->kernel);
    free(kernel);
}

int* SB3_DEV_convolution(SB3_DEV_image_t* image, SB3_DEV_kernel_t* kernel)
{
    char is_rgb = image->format == SB3_DEV_RGB_FORMAT;
    int max_coordonate = (kernel->dim - 1) / 2;
    int size_of_pixels = is_rgb ? 3 : 1;
    int* res = malloc(image->h * image->w * sizeof(*res) * size_of_pixels);

    for(int i = 0; i < image->h; i++)
    {
        for(int j = 0; j < image->w; j++)
        {
            double nr = 0, ng = 0, nb = 0;

            for(int n = -max_coordonate; n <= max_coordonate; n++)
            {
                for(int m = -max_coordonate; m <= max_coordonate; m++)
                {
                    int _h = i+n, _w = j+m;
                    
                    if(_h < 0) _h = 0;
                    else if(_h >= image->h)
                        _h = image->h - 1;
                    if(_w < 0) _w = 0;
                    else if(_w >= image->w)
                        _w = image->w - 1;

                    void* color = SB3_DEV_GetPixelPos(image, _w, _h);
                    double mult = kernel->kernel[(n + max_coordonate) *
                        kernel->dim + (m + max_coordonate)];

                    if(is_rgb)
                    {
                        nr += (double)((SB3_DEV_RGBColor_t*)color)->r * mult;
                        ng += (double)((SB3_DEV_RGBColor_t*)color)->g * mult;
                        nb += (double)((SB3_DEV_RGBColor_t*)color)->b * mult;
                    }
                    else
                        nr += (double)((SB3_DEV_monoColor_t*)color)->color * mult;
                }
            }

            if(is_rgb)
            {
                res[(i * image->w + j) * 3] = (int)nr;
                res[(i * image->w + j) * 3 + 1] = (int)ng;
                res[(i * image->w + j) * 3 + 2] = (int)nb;
            }
            else
                res[i * image->w + j] = (int)nr;
        }
    }

    return res;
}

void SB3_DEV_apply_convolution(SB3_DEV_image_t* image, SB3_DEV_kernel_t* kernel)
{
    int* c = SB3_DEV_convolution(image, kernel);
    for(int i = 0; i < image->w * image->h; i++)
    {
        if(image->format == SB3_DEV_RGB_FORMAT)
        {
            SB3_DEV_RGBColor_t* color = SB3_DEV_NewRGB(c[i*3], c[i*3+1], c[i*3+2]);
            SB3_DEV_SetPixel(image, (void*)color, i);
        }
        else
            SB3_DEV_SetPixel(image, (void*)SB3_DEV_NewMonoColor(c[i]), i);
    }
    free(c);
}

uint8_t __SB3_DEV_grayscale_boost(uint8_t color, double num)
{
    if(color <= 255/2)
        return (uint8_t) ((255./2.) * pow((double)2*color/255, num));
    return 255 - __SB3_DEV_grayscale_boost(255 - color, num);
}

SB3_DEV_monoColor_t* __SB3_DEV_pixel_to_grayscale(SB3_DEV_RGBColor_t* color, double boost)
{
    uint8_t average = (uint8_t)(0.3 * (double)color->r + 0.59 * (double)color->g + 0.11 * (double)color->b);
    if(boost) average = __SB3_DEV_grayscale_boost(average, boost);
    return SB3_DEV_NewMonoColor(average);
}

SB3_DEV_image_t* SB3_DEV_grayscale(SB3_DEV_image_t* image, double boost)
{
    if(image->format != SB3_DEV_RGB_FORMAT)
    {
        #ifdef SB3_DEV_CRASH_WHEN_ERROR
            errx(EXIT_FAILURE, "GRAYSCALE: invalid image format (expected rgb image)");
        #else
            SB3_DEV_SetError(SB3_DEV_BAD_FORMAT_ERROR);
            return NULL;
        #endif
    }

    SB3_DEV_image_t* res = SB3_DEV_NewImage(image->w, image->h, SB3_DEV_MONO_COLOR_FORMAT);

    for(int i = 0; i < image->w * image->h; i++)
    {
        SB3_DEV_SetPixel(res, (void*)__SB3_DEV_pixel_to_grayscale(
            (SB3_DEV_RGBColor_t*)SB3_DEV_GetPixel(image, i), boost), i);
    }

    return res;
}

SB3_DEV_errors_t SB3_DEV_image_to_grayscale(SB3_DEV_image_t* image, double boost)
{
    if(image->format != SB3_DEV_RGB_FORMAT)
    {
        #ifdef SB3_DEV_CRASH_WHEN_ERROR
            errx(EXIT_FAILURE, "GRAYSCALE: invalid image format (expected rgb image)");
        #else
            SB3_DEV_SetError(SB3_DEV_BAD_FORMAT_ERROR);
            return SB3_DEV_BAD_FORMAT_ERROR;
        #endif
    }

    image->format = SB3_DEV_MONO_COLOR_FORMAT;
    image->mono_pixels = malloc(image->w * image->h * sizeof(SB3_DEV_monoColor_t*));
    for(int i = 0; i < image->w * image->h; i++)
    {
        image->mono_pixels[i] = __SB3_DEV_pixel_to_grayscale(image->rgb_pixels[i], boost);
        free(image->rgb_pixels[i]);
    }
    free(image->rgb_pixels);
    image->rgb_pixels = NULL;

    return SB3_DEV_SUCCESS_EXIT;
}

double __SB3_DEV_gaussian_value(double x, double mu, double sigma)
{
    double a = (x - mu) / sigma;
    return exp(-0.5 * a * a);
}

SB3_DEV_kernel_t* SB3_DEV_gaussian_kernel(unsigned int kernel_radius)
{
    double sigma = kernel_radius / 2.;
    int size = 2 * kernel_radius + 1;
    double* m = malloc(size * size * sizeof(double));
    double sum = 0;

    for(int row = 0; row < size; row++)
    {
        for(int col = 0; col < size; col++)
        {
            double x = __SB3_DEV_gaussian_value(row, kernel_radius, sigma) *
                __SB3_DEV_gaussian_value(col, kernel_radius, sigma);
            *(m + row * size + col) = x;
            sum += x;
        }
    }
    for(int row = 0; row < size; row++)
    {
        for(int col = 0; col < size; col++)
        {
            *(m + row * size + col) /= sum;
        }
    }
    SB3_DEV_kernel_t* res = malloc(sizeof(*res));
    *res = (SB3_DEV_kernel_t) {
        .dim = size,
        .kernel = m,
    };

    return res;
}

SB3_DEV_image_t* SB3_DEV_gaussian_blur(SB3_DEV_image_t* image, unsigned int kernel_radius)
{
    SB3_DEV_kernel_t* kernel = SB3_DEV_gaussian_kernel(kernel_radius);
    SB3_DEV_image_t* res = SB3_DEV_NewImage(image->w, image->h, image->format);
    int* c = SB3_DEV_convolution(image, kernel);
    char is_rgb = image->format == SB3_DEV_RGB_FORMAT;
    for(int i = 0; i < image->w * image->h; i++)
    {
        if(is_rgb)
        {
            SB3_DEV_RGBColor_t* color = SB3_DEV_NewRGB(c[i*3]%256, c[i*3+1]%256, c[i*3+2]%256);
            SB3_DEV_SetPixel(res, (void*)color, i);
        }
        else SB3_DEV_SetPixel(res, (void*)SB3_DEV_NewMonoColor(c[i]%256), i);
    }
    free(c);
    SB3_DEV_FreeKernel(kernel);
    return res;
}

void SB3_DEV_apply_gaussian_blur(SB3_DEV_image_t* image, unsigned int kernel_radius)
{
    // BASICALLY :
    // SB3_DEV_image_t* res = SB3_DEV_gaussian_blur(image, kernel_radius);
    // for(int i=0;i<image->w*image->h;i++)
    //     SB3_DEV_SetPixel(image, SB3_DEV_GetPixel(res, i), i);
    // SB3_DEV_FreeImage(res);
    SB3_DEV_kernel_t* kernel = SB3_DEV_gaussian_kernel(kernel_radius);
    int* c = SB3_DEV_convolution(image, kernel);
    char is_rgb = image->format == SB3_DEV_RGB_FORMAT;
    for(int i = 0; i < image->w * image->h; i++)
    {
        if(is_rgb)
        {
            SB3_DEV_RGBColor_t* color = SB3_DEV_NewRGB(c[i*3]%256, c[i*3+1]%256, c[i*3+2]%256);
            SB3_DEV_SetPixel(image, (void*)color, i);
        }
        else SB3_DEV_SetPixel(image, (void*)SB3_DEV_NewMonoColor(c[i]%256), i);
    }
    free(c);
    SB3_DEV_FreeKernel(kernel);
}




