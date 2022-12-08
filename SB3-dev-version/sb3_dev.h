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


#ifndef __SB3_DEV_H__
#define __SB3_DEV_H__

#include <stdlib.h>
#include <stdint.h>

#define SB3_DEV_VERSION "2.20"

// ENUMS

typedef enum {
    SB3_DEV_RGB_FORMAT,
    SB3_DEV_MONO_COLOR_FORMAT,
    SB3_DEV_BINARY_COLOR_FORMAT, // only white and black
} SB3_DEV_image_format_t;

typedef enum {
    SB3_DEV_SUCCESS_EXIT,
    SB3_DEV_CANNOT_OPEN_FILE_ERROR,
    SB3_DEV_CORRUPTED_FILE_ERROR,
    SB3_DEV_BAD_FORMAT_ERROR,
    SB3_DEV_BAD_EXTENSION_ERROR,
    SB3_DEV_NULL_IMAGE_ERROR,
    SB3_DEV_UNSUPORTED_BMP_FORMAT_ERROR,
    SB3_DEV_NULL_PATH_ERROR,
} SB3_DEV_errors_t;

// STRUCTS

typedef struct {
    uint8_t r, g, b;
} SB3_DEV_RGBColor_t;

typedef struct {
    uint8_t color;
} SB3_DEV_monoColor_t;

typedef struct {
    union {int w; int width;};
    union {int h; int height;};
    SB3_DEV_image_format_t format;
    SB3_DEV_RGBColor_t** rgb_pixels;
    SB3_DEV_monoColor_t** mono_pixels;
} SB3_DEV_image_t;

typedef struct {
    unsigned int dim;
    double* kernel;
} SB3_DEV_kernel_t;

// FUNCTIONS

// last error message (don't reset it)
char* SB3_DEV_GetError(void);
// read and write bitmap files
SB3_DEV_errors_t SB3_DEV_BMP_write_image(const char* path, SB3_DEV_image_t* image);
SB3_DEV_image_t* SB3_DEV_BMP_read_image(const char* path, SB3_DEV_image_format_t format);
// utils (create color, image / free color, image / get color in image / change color in image by a new one)
SB3_DEV_RGBColor_t* SB3_DEV_NewRGB(uint8_t r, uint8_t g, uint8_t b);
SB3_DEV_monoColor_t* SB3_DEV_NewMonoColor(uint8_t color);
SB3_DEV_image_t* SB3_DEV_NewImage(int width, int height, SB3_DEV_image_format_t format);
void SB3_DEV_FreeImage(SB3_DEV_image_t* image);
void* SB3_DEV_GetPixel(SB3_DEV_image_t* image, int index);
void* SB3_DEV_GetPixelPos(SB3_DEV_image_t* image, int x, int y);
void SB3_DEV_SetPixel(SB3_DEV_image_t* image, void* pixel, int index);
void SB3_DEV_SetPixelPos(SB3_DEV_image_t* image, void* pixel, int x, int y);
// image processing
void SB3_DEV_FreeKernel(SB3_DEV_kernel_t* kernel);
int* SB3_DEV_convolution(SB3_DEV_image_t* image, SB3_DEV_kernel_t* kernel);
void SB3_DEV_apply_convolution(SB3_DEV_image_t* image, SB3_DEV_kernel_t* kernel);
SB3_DEV_image_t* SB3_DEV_grayscale(SB3_DEV_image_t* image, double boost);
SB3_DEV_errors_t SB3_DEV_image_to_grayscale(SB3_DEV_image_t* image, double boost);
SB3_DEV_kernel_t* SB3_DEV_gaussian_kernel(unsigned int kernel_radius);
SB3_DEV_image_t* SB3_DEV_gaussian_blur(SB3_DEV_image_t* image, unsigned int kernel_radius);
void SB3_DEV_apply_gaussian_blur(SB3_DEV_image_t* image, unsigned int kernel_radius);
// TODO

#endif // __SB3_DEV_H__
