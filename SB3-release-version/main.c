#include "sb3.h"
#include <stdio.h>
#include <err.h>

int main(void)
{
    /* GENERATE IMAGE
    SB3_image_t* image = malloc(sizeof(*image));
    image->format = SB3_RGB_FORMAT;
    image->h = 480;
    image->w = 640;
    image->mono_pixels = NULL;
    image->rgb_pixels = malloc(image->h * image->w * sizeof(SB3_RGBColor_t*));

    for(int y = 0; y < image->h; y++)
    {
        for(int x = 0; x < image->w; x++)
        {
            SB3_RGBColor_t* color = malloc(sizeof(*color));
            *color = (SB3_RGBColor_t) {
                .r = ((float)x / (float)image->w) * 255.,
                .g = (1. - ((float)x / (float)image->w)) * 255.,
                .b = ((float)y / (float)image->h) * 255,
            };
            image->rgb_pixels[y * image->w + x] = color;
        }
    }
    return SB3_BMP_write_image("test.bmp", image);
    */
    SB3_BMP_write_image("copy.bmp", SB3_BMP_read_image("test.bmp", SB3_RGB_FORMAT));
    return EXIT_SUCCESS;
}



