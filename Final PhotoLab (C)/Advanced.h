#ifndef ADVANCED_H_INCLUDED_
#define ADVANCED_H_INCLUDED_
#include "Image.h"
#include "Constants.h"

/* add noise to an image */
IMAGE *Noise(int percentage, IMAGE *image);

/* sharpen the image */
IMAGE *Sharpen(IMAGE *image);

/* posterize the image */
IMAGE *Posterize(IMAGE *image, unsigned int rbits, unsigned int gbits, unsigned int bbits);

IMAGE *Crop(IMAGE *image, unsigned int x, unsigned int y, unsigned int W, unsigned int H);

IMAGE *Resize(IMAGE *image, int percentage);

IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast);

IMAGE *Watermark(IMAGE *image, const IMAGE *watermark_Image);

#endif /* ADVANCED_H_INCLUDED_ */

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
