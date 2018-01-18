#ifndef DIPS_H_INCLUDED_
#define DIPS_H_INCLUDED_
#include "Image.h"
#include "Constants.h"
/* change color image to black & white */
IMAGE *BlackNWhite(IMAGE *image);

/* reverse image color */
IMAGE *Negative(IMAGE *image);

/* color filter */
IMAGE *ColorFilter(IMAGE *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b);

/* edge detection */
IMAGE *Edge(IMAGE *image);

/* Shuffle the image */
IMAGE *Shuffle(IMAGE *image);

/* mirror image vertically */
IMAGE *VFlip(IMAGE *image);

/* flip image vertically */
IMAGE *VMirror(IMAGE *image);

#endif /* DIPS_H_INCLUDED_ */

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
