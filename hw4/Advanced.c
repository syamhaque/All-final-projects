#include "Advanced.h"
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/* Add noise to an image */
IMAGE *Noise(int percentage, IMAGE *image){
    assert(image);
	int WIDTH = ImageWidth(image), HEIGHT = ImageHeight(image);
    int x, y, i;
    int num; /* number of noise added */
    num = ( percentage*HEIGHT*WIDTH )/100;
    srand(time(NULL));

    for ( i = 0; i < num; i++ ) {
        x = ( (double)rand()/RAND_MAX )*(WIDTH-1);
        y = ( (double)rand()/RAND_MAX )*(HEIGHT-1);
        SetPixelR(image, x, y, 255);
        SetPixelG(image, x, y, 255);
        SetPixelB(image, x, y, 255);
    }
    return image;
}


/* sharpen the image */
IMAGE *Sharpen(IMAGE *image){
	assert(image);
	int WIDTH = ImageWidth(image), HEIGHT = ImageHeight(image);
	int		x, y, m, n, a, b;
	int		tmpR = 0;
	int		tmpG = 0;
	int		tmpB = 0;
	
	IMAGE *sharpen = NULL;
	sharpen = CreateImage(WIDTH, HEIGHT);	

	for (y = 0; y < HEIGHT; y++){
		for (x = 0; x < WIDTH; x++) {
			SetPixelR(sharpen, x, y, GetPixelR(image, x, y));
			SetPixelG(sharpen, x, y, GetPixelG(image, x, y));
			SetPixelB(sharpen, x, y, GetPixelB(image, x, y));
			
		}
	}

	for (y = 0; y < HEIGHT; y++){
		for (x = 0; x < WIDTH; x++){
			for (n = -1; n <= 1; n++){
				for (m = -1; m <= 1; m++) {
					a = x + m;
					b = y + n;
					if (a > WIDTH - 1)
						a = WIDTH - 1;
					if (a < 0)
						a = 0;
					if (b > HEIGHT - 1)
						b = HEIGHT - 1;
					if (b < 0)
						b = 0;
					
					if ((n==0)&&(m==0))
					{
						tmpR += 9*GetPixelR(sharpen, a, b); 
						tmpG += 9*GetPixelG(sharpen, a, b); 
						tmpB += 9*GetPixelB(sharpen, a, b); 
					}
					else
					{
						tmpR -= GetPixelR(sharpen, a, b) ; 
						tmpG -= GetPixelG(sharpen, a, b) ; 
						tmpB -= GetPixelB(sharpen, a, b) ; 
					}
				}
			}
			SetPixelR(image, x, y, (tmpR>255)? 255: (tmpR<0)? 0: tmpR);
			SetPixelG(image, x, y, (tmpG>255)? 255: (tmpG<0)? 0: tmpG);
			SetPixelB(image, x, y, (tmpB>255)? 255: (tmpB<0)? 0: tmpB);			
		  	tmpR = tmpG = tmpB = 0; 	
		}
	}
	DeleteImage(sharpen);
	sharpen = NULL;
	return image;
}


/* make the image posterized */
IMAGE *Posterize(IMAGE *image, unsigned int rbits, unsigned int gbits, unsigned int bbits){
    assert(image);
    assert(rbits >= 1 && rbits <= 8 && gbits >= 1 && gbits <= 8 && bbits >= 1 && bbits <= 8);
    int WIDTH = ImageWidth(image), HEIGHT = ImageHeight(image);
	int x, y, tmpR, tmpG, tmpB;
    for(x=0; x<WIDTH; x++) {
        for(y=0; y<HEIGHT; y++) {
            tmpR = GetPixelR(image, x, y);
            tmpG = GetPixelG(image, x, y);
            tmpB = GetPixelB(image, x, y);
            unsigned char one = 1;
            int i;
            for(i=0; i<rbits-1; i++) {
                tmpR |= one;
                one <<= 1;
            }
            one = ~one;
            tmpR &= one;
            SetPixelR(image, x, y, tmpR);

            one = 1;
            for(i=0; i<gbits-1; i++) {
                tmpG |= one;
                one <<= 1;
            }
            one = ~one;
            tmpG &= one;
            SetPixelG(image, x, y, tmpG);

            one = 1;
            for(i=0; i<bbits-1; i++) {
                tmpB |= one;
                one <<= 1;
            }
            one = ~one;
            tmpB &= one;
            SetPixelB(image, x, y, tmpB);

        }
    }
    return image;
}

IMAGE *Crop(IMAGE *image, unsigned int x, unsigned int y, unsigned int W, unsigned int H){
    assert(x < image->W && y < image->H);
    assert(image);
    int i, j;
    int WIDTH = ImageWidth(image), HEIGHT = ImageHeight(image);
    int tmpR[WIDTH*HEIGHT], tmpG[WIDTH*HEIGHT], tmpB[WIDTH*HEIGHT];
    int k = 0;
    for(i = x; i <= W + x && i < WIDTH; i++){
        for(j = y; j <= H + y && j < HEIGHT; j++){
            tmpR[k] = GetPixelR(image, i, j);
            tmpG[k] = GetPixelG(image, i, j);
            tmpB[k] = GetPixelB(image, i, j);
            k++;
        }
    }
    IMAGE *newimage = NULL;
    newimage = CreateImage(W, H);
    k = 0;
    for(i = 0; i < W; i++){
        for(j = 0; j < H; j++){

            SetPixelR(newimage, i, j, tmpR[k]);
            SetPixelG(newimage, i, j, tmpG[k]);
            SetPixelB(newimage, i, j, tmpB[k]);
            k++;
        }
    }
    DeleteImage(image);
    image = NULL;
    return newimage;
}

IMAGE *Resize(IMAGE *image, int percentage){
    assert(image);
    assert(percentage >= 1 && percentage <= 500);
    int W = ImageWidth(image), H = ImageHeight(image), newW, newH;
    int x, y, newx1, newy1, newx2, newy2, avgx, avgy;

    newW = W * (percentage/100.00);
    newH = H * (percentage/100.00);

	if (percentage > 100){
		IMAGE *bigresize = NULL;
		bigresize = CreateImage(newW, newH);
		for (x = 0; x < newW; x++){
			for(y = 0; y < newH; y++){
				newx1 = (x * (100.00/percentage));
                newy1 = (y * (100.00/percentage));
				SetPixelR(bigresize, x, y, GetPixelR(image, newx1, newy1));
                SetPixelG(bigresize, x, y, GetPixelG(image, newx1, newy1));
                SetPixelB(bigresize, x, y, GetPixelB(image, newx1, newy1));
				
			}
		}

        DeleteImage(image);
		image = NULL;
		return bigresize;
    }
    else if (percentage < 100){
		IMAGE *smallresize = NULL;
		smallresize = CreateImage(newW, newH);
		for (x = 0; x < newW; x++){
            for(y = 0; y < newH; y++){
				newx1 = (x * (100.00/percentage));
                newy1 = (y * (100.00/percentage));
				newx2 = ((x+1) * (100.00/percentage));
                newy2 = ((y+1) * (100.00/percentage));
				avgx = (newx1 + newx2) / 2;
				avgy = (newy1 + newy2) / 2;
                SetPixelR(smallresize, x, y, GetPixelR(image, avgx, avgy));
                SetPixelG(smallresize, x, y, GetPixelG(image, avgx, avgy));
                SetPixelB(smallresize, x, y, GetPixelB(image, avgx, avgy));
			}
		}

		DeleteImage(image);
        image = NULL;
        return smallresize;
    }
    else{
        return image;
    }

}

IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast){
    assert(image);
    assert(brightness >= -255 && brightness <= 255);
    assert(contrast >= -255 && contrast <= 255);

    int x, y;
    int W = ImageWidth(image), H = ImageHeight(image);
    int tmpR, tmpG, tmpB;
    double factor = (double)(259 * (contrast + 255)) / (double)(255 * (259 - contrast));

    for (x = 0; x < W; x++){
        for (y = 0; y < H; y++){

            tmpR = (int)(factor * (GetPixelR(image, x, y) - 128) + 128) + brightness;
            tmpG = (int)(factor * (GetPixelG(image, x, y) - 128) + 128) + brightness;
            tmpB = (int)(factor * (GetPixelB(image, x, y) - 128) + 128) + brightness;

            SetPixelR(image, x, y, ((tmpR > 255) ? 255: (tmpR < 0) ? 0: tmpR));
            SetPixelG(image, x, y, ((tmpG > 255) ? 255: (tmpG < 0) ? 0: tmpG));
            SetPixelB(image, x, y, ((tmpB > 255) ? 255: (tmpB < 0) ? 0: tmpB));
			
        }
    }
    return image;
}

IMAGE *Watermark(IMAGE *image, const IMAGE *watermark_Image){
	assert(image);
	assert(watermark_Image);
	int HEIGHT = ImageHeight(image);
	int W = watermark_Image->W, H = watermark_Image->H;
	int x,y;
	int tmpR, tmpG, tmpB;

	for (x = 0; x < W; x++){
		for (y = 0; y < H; y++){
			if (GetPixelR(watermark_Image, x, y) == 0 && GetPixelG(watermark_Image, x, y) == 0 && GetPixelB(watermark_Image, x, y) == 0){
			
				tmpR = GetPixelR(image, x, y) * 1.45;
				tmpG = GetPixelG(image, x, y) * 1.45;
				tmpB = GetPixelB(image, x, y) * 1.45;
				SetPixelR(image, x, y, ((tmpR > 255) ? 255: (tmpR < 0) ? 0: tmpR));
				SetPixelG(image, x, y, ((tmpG > 255) ? 255: (tmpG < 0) ? 0: tmpG));
				SetPixelB(image, x, y, ((tmpB > 255) ? 255: (tmpB < 0) ? 0: tmpB));
	
			}
		}
	}

	for (x = 0; x < W; x++){
		for (y = 0; y < H && (y + H) < HEIGHT; y++){
			if (GetPixelR(watermark_Image, x, y) == 0 && GetPixelG(watermark_Image, x, y) == 0 && GetPixelB(watermark_Image, x, y) == 0){
			
				tmpR = GetPixelR(image, x, (y + H)) * 1.45;
                tmpG = GetPixelG(image, x, (y + H)) * 1.45;
                tmpB = GetPixelB(image, x, (y + H)) * 1.45;
                SetPixelR(image, x, (y + H), ((tmpR > 255) ? 255: (tmpR < 0) ? 0: tmpR));
                SetPixelG(image, x, (y + H), ((tmpG > 255) ? 255: (tmpG < 0) ? 0: tmpG));
                SetPixelB(image, x, (y + H), ((tmpB > 255) ? 255: (tmpB < 0) ? 0: tmpB));		
	
			}
		}
	}
	return image;
}
/* vim: set tabstop=4 softtabstop=4 shiftwidth=4 noexpandtab : */
 
