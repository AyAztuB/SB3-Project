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
 * AyAztuB (ayaztub@gmail.com) from https://github.com/AyAztuB/SB3-Project
 *
 */


#include "sb3.h"


SB3_errors_t last_error = SB3_SUCCESS_EXIT;

char* SB3_GetError(void)
{
    switch (last_error)
    {
        case SB3_NULL_PATH_ERROR:
            return "image path was NULL";
        case SB3_UNSUPORTED_BMP_FORMAT_ERROR:
            return "the bmp image passed in parameter has an unsuported format";
        case SB3_NULL_IMAGE_ERROR:
            return "image passed in parameter was NULL";
        case SB3_BAD_EXTENSION_ERROR:
            return "the path given in parameter hasn't '.bmp' extension";
        case SB3_BAD_FORMAT_ERROR:
            return "the format precised wasn't correct";
        case SB3_CORRUPTED_FILE_ERROR:
            return "try to read bmp image who doesn't have 'BM' signature at first 2 bytes";
        case SB3_CANNOT_OPEN_FILE_ERROR:
            return "cannot open given file";
        default:
            return "THERE IS NO FUCKING ERROR: WHY DO YOU WANT A MESSAGE ERROR WHEN THERE IS NO ERROR ?";
    }
}

void SB3_SetError(SB3_errors_t error)
{
    last_error = error;
}

SB3_RGBColor_t* SB3_NewRGB(uint8_t r, uint8_t g, uint8_t b)
{
    SB3_RGBColor_t* color = malloc(sizeof(*color));
    *color = (SB3_RGBColor_t) {
        .r = r,
        .g = g,
        .b = b,
    };
    return color;
}

SB3_monoColor_t* SB3_NewMonoColor(uint8_t color)
{
    SB3_monoColor_t* res = malloc(sizeof(*res));
    *res = (SB3_monoColor_t) {
        .color = color,
    };
    return res;
}

void SB3_RGBFreeColor(SB3_RGBColor_t* color)
{
    free(color);
}

void SB3_MonoFreeColor(SB3_monoColor_t* color)
{
    free(color);
}

SB3_image_t* SB3_NewImage(int width, int height, SB3_image_format_t format)
{
    SB3_image_t* image = malloc(sizeof(*image));
    *image = (SB3_image_t) {
        .w = width,
        .h = height,
        .format = format,
        .mono_pixels = NULL,
        .rgb_pixels = NULL,
    };
    if(format == SB3_RGB_FORMAT)
    {
        SB3_RGBColor_t** pixels = malloc(width * height * sizeof(SB3_RGBColor_t*));
        for(int i = 0; i < width*height; i++)
            pixels[i] = SB3_NewRGB(0,0,0);
        image->rgb_pixels = pixels;
    }
    else
    {
        SB3_monoColor_t** pixels = malloc(width * height * sizeof(SB3_monoColor_t*));
        for(int i = 0; i < width*height; i++)
            pixels[i] = SB3_NewMonoColor(0);
        image->mono_pixels = pixels;
    }
    return image;
}

void SB3_FreeImage(SB3_image_t* image)
{
    if(image->format == SB3_RGB_FORMAT)
    {
        for(int i = 0; i < image->w * image->h; i++)
            SB3_RGBFreeColor(image->rgb_pixels[i]);
        free(image->rgb_pixels);
    }
    else
    {
        for(int i = 0; i < image->w * image->h; i++)
            SB3_MonoFreeColor(image->mono_pixels[i]);
        free(image->mono_pixels);
    }
    free(image);
}

/* to cast in SB3_RGBColor_t* or in SB3_monoColor_t* */
void* SB3_GetPixel(SB3_image_t* image, int index)
{
    if(image->format == SB3_RGB_FORMAT)
        return (void*)(image->rgb_pixels[index]);
    return (void*)(image->mono_pixels[index]);
}

void* SB3_GetPixelPos(SB3_image_t* image, int x, int y)
{
    return SB3_GetPixel(image, y * image->w + x);
}

void SB3_SetPixel(SB3_image_t* image, void* pixel, int index)
{
    if(image->format == SB3_RGB_FORMAT)
    {
        SB3_RGBFreeColor(image->rgb_pixels[index]);
        image->rgb_pixels[index] = (SB3_RGBColor_t*)pixel;
    }
    else
    {
        SB3_MonoFreeColor(image->mono_pixels[index]);
        image->mono_pixels[index] = (SB3_monoColor_t*)pixel;
    }
}

void SB3_SetPixelPos(SB3_image_t* image, void* pixel, int x, int y)
{
    SB3_SetPixel(image, pixel, y * image->w + x);
}


