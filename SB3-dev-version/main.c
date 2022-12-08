#include <sb3_dev.h>
#include <stdio.h>
#include <err.h>

int main(void)
{
    SB3_DEV_image_t* img = SB3_DEV_BMP_read_image("image_01_grayscale.bmp", SB3_DEV_MONO_COLOR_FORMAT);
    SB3_DEV_image_t* copy = SB3_DEV_gaussian_blur(img, 3.);
    SB3_DEV_BMP_write_image("img.bmp", img);
    SB3_DEV_FreeImage(img);
    SB3_DEV_BMP_write_image("copy.bmp", copy);
    SB3_DEV_FreeImage(copy);
    SB3_DEV_image_t* crash = SB3_DEV_BMP_read_image("crash.bmp", SB3_DEV_RGB_FORMAT);
    return 0;
}


