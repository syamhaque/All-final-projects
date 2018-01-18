#include "DIPs.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/* Example of DIP */
/* make the picture color black & white */
IMAGE *BlackNWhite(IMAGE *image){
    assert(image);
    int             x, y, tmp;
	int W = ImageWidth(image), H = ImageHeight(image);

    for (y = 0; y < H; y++)
    {
        for (x = 0; x < W; x++)
        {
            tmp = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3;
            SetPixelR(image, x, y, tmp);
            SetPixelG(image, x, y, tmp);
            SetPixelB(image, x, y, tmp);
        }
    }
    return image;
}

/* reverse image color */
IMAGE *Negative(IMAGE *image) {
    assert(image);
    int x, y, tmpR, tmpG, tmpB;
	int W = ImageWidth(image), H = ImageHeight(image);
    for (y = 0; y < H; y++) {
        for (x = 0; x < W; x++) {
            tmpR = MAX_PIXEL - GetPixelR(image, x, y);
            tmpG = MAX_PIXEL - GetPixelG(image, x, y);
            tmpB = MAX_PIXEL - GetPixelB(image, x, y);
            SetPixelR(image, x, y, tmpR);
            SetPixelG(image, x, y, tmpG);
            SetPixelB(image, x, y, tmpB);

        }
    }
    return image;
}

/*colorfiler */
IMAGE *ColorFilter(IMAGE *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b){
    assert(image);
    replace_r = (replace_r > MAX_PIXEL)? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
    replace_g = (replace_g > MAX_PIXEL)? MAX_PIXEL : (replace_g < 0) ? 0 : replace_g;
    replace_b = (replace_b > MAX_PIXEL)? MAX_PIXEL : (replace_b < 0) ? 0 : replace_b;
    int x, y;
	int W = ImageWidth(image), H = ImageHeight(image);
    for (y = 0; y < H; y++){
        for (x = 0; x < W; x++){
            if (abs(GetPixelR(image, x, y) - target_r) <= threshold
                    && abs(GetPixelG(image, x, y) - target_g) <= threshold
                    && abs(GetPixelB(image, x, y) - target_b) <= threshold) {
                SetPixelR(image, x, y, replace_r);
                SetPixelG(image, x, y, replace_g);
                SetPixelB(image, x, y, replace_b);
            }
        }
    }
    return image;
}

/* Add edge to the image*/
IMAGE *Edge(IMAGE *image) {
	int W = ImageWidth(image), H = ImageHeight(image);
    int             x, y, m, n, a, b;

	IMAGE *edge = NULL;
	edge = CreateImage(W, H);	

    for (y = 0; y < H; y++){
        for (x = 0; x < W; x++) {
            SetPixelR(edge, x, y, GetPixelR(image, x, y));
            SetPixelG(edge, x, y, GetPixelG(image, x, y));
            SetPixelB(edge, x, y, GetPixelB(image, x, y));
			
        }
    }

    int sumR = 0;   /* sum of the intensity differences with neighbors */
    int sumG = 0;
    int sumB = 0;

    for (y = 1; y < H - 1; y++){
        for (x = 1; x < W - 1; x++){
            for (n = -1; n <= 1; n++){
                for (m = -1; m <= 1; m++) {
                    a = (x + m >= W) ? W - 1 : (x + m < 0) ? 0 : x + m;
                    b = (y + n >= H) ? H - 1 : (y + n < 0) ? 0 : y + n;
                    sumR += (GetPixelR(edge, x, y) - GetPixelR(edge, a, b));
                    sumG += (GetPixelG(edge, x, y) - GetPixelG(edge, a, b));
                    sumB += (GetPixelB(edge, x, y) - GetPixelB(edge, a, b));

                }
            }
            SetPixelR(image, x, y, (sumR > MAX_PIXEL) ? MAX_PIXEL: (sumR < 0) ? 0: sumR);
            SetPixelG(image, x, y, (sumG > MAX_PIXEL) ? MAX_PIXEL: (sumG < 0) ? 0: sumG);
            SetPixelB(image, x, y, (sumB > MAX_PIXEL) ? MAX_PIXEL: (sumB < 0) ? 0: sumB);

            sumR = sumG = sumB = 0;
			
        }
    }
	DeleteImage(edge);
	edge = NULL;
    return image;
}


/* flip image vertically */
IMAGE *VFlip(IMAGE *image){
    assert(image);
	int W = ImageWidth(image), H = ImageHeight(image);
    int             x, y;
    unsigned char   r, g, b;
	unsigned char tmpR, tmpG, tmpB;

	for (y = 0; y < H/2; y ++){
        for (x = 0; x < W; x ++){
            r = GetPixelR(image, x, (H - y - 1));
            g = GetPixelG(image, x, (H - y - 1));
            b = GetPixelB(image, x, (H - y - 1));

			tmpR = GetPixelR(image, x, y);
			tmpG = GetPixelG(image, x, y);
			tmpB = GetPixelB(image, x, y);
			
			SetPixelR(image, x, (H - y - 1), tmpR);
			SetPixelG(image, x, (H - y - 1), tmpG);
			SetPixelB(image, x, (H - y - 1), tmpB);

            SetPixelR(image, x, y, r);
			SetPixelG(image, x, y, g);
			SetPixelB(image, x, y, b);
        }
    }
    return image;
}

/* mirror image vertically */
IMAGE *VMirror(IMAGE *image) {
    assert(image);
    int x, y, tmpR, tmpG, tmpB;
	int W = ImageWidth(image), H = ImageHeight(image);
    for (y = 0; y < H / 2; y ++) {
        for (x = 0; x < W; x ++) {
            tmpR = GetPixelR(image, x, (H - y - 1));
            tmpG = GetPixelG(image, x, (H - y - 1));
            tmpB = GetPixelB(image, x, (H - y - 1));
            SetPixelR(image, x, y, tmpR);
            SetPixelG(image, x, y, tmpG);
            SetPixelB(image, x, y, tmpB);
        }
    }
    return image;
}

/* Shuffle the image */
IMAGE *Shuffle(IMAGE *image){
	int W = ImageWidth(image), H = ImageHeight(image);
    int block_cnt = SHUFF_HEIGHT_DIV * SHUFF_WIDTH_DIV;
    int block_width = W/SHUFF_WIDTH_DIV;
    int block_height = H/SHUFF_HEIGHT_DIV;
    int block[SHUFF_WIDTH_DIV][SHUFF_HEIGHT_DIV];
    int i, j;
    

    srand(time(NULL));
    /* Initialize block markers to not done (-1) */
    for (i = 0; i < SHUFF_WIDTH_DIV; i++) {
        for (j = 0; j< SHUFF_HEIGHT_DIV; j++) {
            block[i][j] = -1;
        }
    }

    while (block_cnt > 0) {
        /* Generate a random pair of blocks */
        int dest_height = rand() % SHUFF_HEIGHT_DIV;
        int dest_width = rand() % SHUFF_WIDTH_DIV;
        int src_height = rand() % SHUFF_HEIGHT_DIV;
        int src_width = rand() % SHUFF_WIDTH_DIV;

        /* Check if these blocks are already swaped, if not swap blocks */
        if ((block[dest_width][dest_height] == -1) && (block[src_width][src_height] == -1)) {
            /* Swap blocks */
            for (i = 0; i < block_height; i++) {
                /* Init src and dest height offset */
                int h_dest = ((dest_height * block_height) + i) % H;
                int h_src  = ((src_height * block_height) + i) % H; 
                for (j = 0; j < block_width; j++) {
                    int temp, temps;
                    /* Init src and dest width offset */
                    int w_src  = ((src_width * block_width) + j) % W; 
                    int w_dest = ((dest_width * block_width) + j) % W;

                    temp = GetPixelR(image, w_dest, h_dest);
                    temps = GetPixelR(image, w_src, h_src);
					SetPixelR(image, w_dest, h_dest, temps);
					SetPixelR(image, w_src, h_src, temp);

                    temp = GetPixelG(image, w_dest, h_dest);
                    temps = GetPixelG(image, w_src, h_src);
                    SetPixelG(image, w_dest, h_dest, temps);
                    SetPixelG(image, w_src, h_src, temp);

                    temp = GetPixelB(image, w_dest, h_dest);
                    temps = GetPixelB(image, w_src, h_src);
                    SetPixelB(image, w_dest, h_dest, temps);
                    SetPixelB(image, w_src, h_src, temp);
                }
            }
            /* Set marker as done */
            block[dest_width][dest_height] = 1;
            block[src_width][src_height] = 1;
            /* Decrease block count */
            block_cnt -= 2; /* Two blocks are swapped */
		}
        
    }
	return image;
}


/* vim: set tabstop=4 softtabstop=4 shiftwidth=4 noexpandtab : */
