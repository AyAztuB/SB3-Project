.TH sb3 3 "december 09, 2022" "version 1.20" "SB3 lib man page"

.SH NAME
sb3 \- SB3, image library (SDL BUT BETTER BITMAP)

.SH SYNOPSIS
.B #include <sb3.h>

.SH DESCRIPTION
The SB3 library is an image library. It can actually read bitmap (.bmp) images from differents modern format or write bmp images.
Enums, structs and functions are listed below.

.PP
.B List of enums

.RS

.IP SB3_error_t
contains error code return, 0 is SB3_SUCCESS_EXIT

.IP SB3_image_format_t
contains the 3 formats availables for the image struct: SB3_RGB_FORMAT, SB3_MONO_COLOR_FORMAT, SB3_BINARY_COLOR_FORMAT (only black and white)

.RE

.PP
.B List of structs

.RS

.IP SB3_RGBColor_t
used for RGB image format. It contains 3 attributs r, g and b (uint8_t)

.IP SB3_monoColor_t
used for mono color and binary color image format. It contains one attribut color (uint8_t)

.IP SB3_image_t
the image type: contening w (int: image width), h (int: image height), format (SB3_image_format_t: image format) and 2 pixels array (only one can be used)
[rgb_pixels (SB3_RGBColor_t**) and mono_pixels (SB3_monoColor_t**)]

.RE

.PP
.B List of functions

.RS

.TP
\fBchar*\fR SB3_GetError (\fBvoid\fR)
return an error message for the last error occured. Don't resset this last error.

.TP
\fBSB3_error_t\fR SB3_BMP_write_image (\fBconst char*\fR \fIpath\fR, \fBSB3_image_t*\fR \fIimage\fR)
write \fIimage\fR in file specified at \fIpath\fR. return error_code if an error occured (the error can also be catch by \fBSB3_GetError\fR), else 0 or SB3_SUCCESS_EXIT. If \f(BIimage\fB\->format\fR is RGB then write each color on 24bits, if it's monoColor, write each on 8bits, else write each on 1bit (not supported by feh).

.TP
\fBSB3_image_t*\fR SB3_BMP_read_image (\fBconst char*\fR \fIpath\fR, \fBSB3_image_format_t\fR \fIformat\fR)
read image at \fIpath\fR and return it in the given \fIformat\fR. return \fBNULL\fR if an error occured and set it at the last error. Error occured if the file or the format isn't correct or if the file format isn't supported.

.TP
\fBSB3_RGBColor_t*\fR SB3_NewRGB (\fBuint8_t\fR \fIr\fR, \fBuint8_t\fR \fIg\fR, \fBuint8_t\fR \fIb\fR)
create and return a new rgb color with the given \fIr\fR, \fIg\fR, \fIb\fR values (between 0 and 255)

.TP
\fBSB3_monoColor_t*\fR SB3_NewMonoColor (\fBuint8_t\fR \fIcolor\fR)
create and return a new mono color using the given \fIcolor\fR value (between 0 and 255)

.TP
\fBSB3_image_t*\fR SB3_NewImage (\fBint\fR \fIwidth\fR, \fBint\fR \fIheight\fR, \fBSB3_image_format_t\fR \fIformat\fR)
create and return a new image with \fIformat\fR color type. The image size is \fIwidth\fR * \fIheight\fR and is initially fill with black color pixels

.TP
\fBvoid\fR SB3_FreeImage (\fBSB3_image_t*\fR \fIimage\fR)
free the \fIimage\fR, the pixel array and all colors containing in it

.TP
\fBvoid*\fR SB3_GetPixel (\fBSB3_image_t*\fR \fIimage\fR, \fBint\fR \fIindex\fR)
return pixel at position \fIindex\fR (in row\-major) in \fIimage\fR. Pixel returned is a \fBSB3_RGBColor_t*\fR or \fBSB3_monoColor_t*\fR

.TP
\fBvoid*\fR SB3_GetPixelPos (\fBSB3_image_t*\fR \fIimage\fR, \fBint\fR \fIx\fR, \fBint\fR \fIy\fR)
return pixel (\fBSB3_RGBColor_t*\fR or \fBSB3_monoColor_t*\fR) in \fIimage\fR at position (\fIx\fR, \fIy\fR) in (row, col)

.TP
\fBvoid\fR SB3_SetPixel (\fBSB3_image_t*\fR \fIimage\fR, \fBvoid*\fR \fIpixel\fR, \fBint\fR \fIindex\fR)
set \fIpixel\fR (\fBSB3_RGBColor_t*\fR or \fBSB3_monoColor_t*\fR) in \fIimage\fR at \fIindex\fR (in row-major)

.TP
\fBvoid\fR SB3_SetPixelPos (\fBSB3_image_t*\fR \fIimage\fR, \fBvoid*\fR \fIpixel\fR, \fBint\fR \fIx\fR, \fBint\fR \fIy\fR)
set \fIpixel\fR (\fBSB3_RGBColor_t*\fR or \fBSB3_monoColor_t*\fR) in \fIimage\fR at position (\fIx\fR, \fIy\fR) in (row, col)

.RE

.SH AUTHOR
created by \fBAyAztuB\fR (\fIayaztub@gmail.com\fR) from \fIhttps://github.com/AyAztuB/SB3\-Project\fR


