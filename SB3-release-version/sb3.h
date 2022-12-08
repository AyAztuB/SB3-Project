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


#ifndef __SB3_H__
#define __SB3_H__

#include <stdlib.h>
#include <stdint.h>

#define SB3_VERSION "1.20"

// ENUMS

typedef enum {
    SB3_RGB_FORMAT,
    SB3_MONO_COLOR_FORMAT,
    SB3_BINARY_COLOR_FORMAT, // only white and black
} SB3_image_format_t;

typedef enum {
    SB3_SUCCESS_EXIT,
    SB3_CANNOT_OPEN_FILE_ERROR,
    SB3_CORRUPTED_FILE_ERROR,
    SB3_BAD_FORMAT_ERROR,
    SB3_BAD_EXTENSION_ERROR,
    SB3_NULL_IMAGE_ERROR,
    SB3_UNSUPORTED_BMP_FORMAT_ERROR,
    SB3_NULL_PATH_ERROR,
} SB3_errors_t;

// STRUCTS

typedef struct {
    uint8_t r, g, b;
} SB3_RGBColor_t;

typedef struct {
    uint8_t color;
} SB3_monoColor_t;

typedef struct {
    int w, h;
    SB3_image_format_t format;
    SB3_RGBColor_t** rgb_pixels;
    SB3_monoColor_t** mono_pixels;
} SB3_image_t;

// FUNCTIONS

// last error message (don't reset it)
char* SB3_GetError(void);
// read and write bitmap files
SB3_errors_t SB3_BMP_write_image(const char* path, SB3_image_t* image);
SB3_image_t* SB3_BMP_read_image(const char* path, SB3_image_format_t format);
// utils (create color, image / free color, image / get color in image / change color in image by a new one)
SB3_RGBColor_t* SB3_NewRGB(uint8_t r, uint8_t g, uint8_t b);
SB3_monoColor_t* SB3_NewMonoColor(uint8_t color);
SB3_image_t* SB3_NewImage(int width, int height, SB3_image_format_t format);
void SB3_FreeImage(SB3_image_t* image);
void* SB3_GetPixel(SB3_image_t* image, int index);
void* SB3_GetPixelPos(SB3_image_t* image, int x, int y);
void SB3_SetPixel(SB3_image_t* image, void* pixel, int index);
void SB3_SetPixelPos(SB3_image_t* image, void* pixel, int x, int y);
// TODO

#endif // __SB3_H__
