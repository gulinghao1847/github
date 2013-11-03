/*   CS580 HW   */
#include    "stdafx.h"  
#include	"Gz.h"
#include	"disp.h"
#include <stdlib.h>
#include <math.h>

int GzNewFrameBuffer(char** framebuffer, int width, int height)
{
/* create a framebuffer:
 -- allocate memory for framebuffer : (sizeof)GzPixel x width x height
 -- pass back pointer 
 -- NOTE: this function is optional and not part of the API, but you may want to use it within the display function.
*/
	if(framebuffer == NULL){
		return GZ_FAILURE;
	}
	
	if(!(*framebuffer = (char*)malloc(3*sizeof(char)*width*height)))
		return GZ_FAILURE;
		
	return GZ_SUCCESS;
}

int GzNewDisplay(GzDisplay	**display, int xRes, int yRes)
{
/* create a display:
  -- allocate memory for indicated resolution
  -- pass back pointer to GzDisplay object in display
*/
	
	if(!(*display = (GzDisplay*)malloc(sizeof(GzDisplay)))){
		return GZ_FAILURE;
	}
	
	GzPixel *fbuf;
	if(!(fbuf = (GzPixel*)malloc(xRes*yRes*sizeof(GzPixel)))){
		return GZ_FAILURE;
	}

	if(	xRes > MAXXRES){
		xRes = MAXXRES;
	}

	if(yRes > MAXYRES){
		yRes = MAXYRES;
	}

	(*display) -> xres = xRes;
	(*display) -> yres = yRes;

	//TRACE("XRES : %d, YRES : %d, sizeofGzPixel: %d\n", xRes, yRes, sizeof(GzPixel));
	(*display) -> fbuf = fbuf;
	return GZ_SUCCESS;
}


int GzFreeDisplay(GzDisplay	*display)
{
/* clean up, free memory */
	free(display -> fbuf);
	free(display);
	return GZ_SUCCESS;
}


int GzGetDisplayParams(GzDisplay *display, int *xRes, int *yRes)
{
/* pass back values for a display */
	*xRes = display -> xres;
	*yRes = display -> yres;
	return GZ_SUCCESS;
}


int GzInitDisplay(GzDisplay	*display)
{
/* set everything to some default values - start a new frame */
	int num;
	short x = display -> xres;
	short y = display -> yres;
	GzPixel* tempPixel;
	int max_int = (int)(pow(2.0,(int)(sizeof(int)*8-1))-1);
	for(num = 0; num<x*y ; num++){
		tempPixel = &(display->fbuf[num]);
		//TRACE("XRES : %d, YRES : %d, num:%d,  sizeofGzPixel: %d\n", x, y,num, sizeof(GzPixel));
		tempPixel->red = 2048;
		tempPixel->blue = 1536;
		tempPixel->green = 1792;
		tempPixel->alpha = 1;
		tempPixel->z = max_int;
	}
	return GZ_SUCCESS;
}

void checkBoundry(GzIntensity* x){
	if(*x>4095){
		*x = 4095;
	}
	if(*x<0){
		*x = 0;
	}
}

int GzPutDisplay(GzDisplay *display, int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z)
{
/* write pixel values into the display */
	//printf("~~~~~~~~~~~~~~~~~~%d~~~~~~~~~~~~~",ARRAY(i,j));
	int maxX = display->xres;
	int maxY = display->yres;

	if(i<0||i>maxX||j<0||j>maxY) 
		return GZ_SUCCESS;
	GzPixel *pixel = &(display->fbuf[ARRAY(i,j)]);
	checkBoundry(&r);
	checkBoundry(&g);
	checkBoundry(&b);


	//TRACE("XRES : %d, YRES : %d, num:%d,  sizeofGzPixel: %d\n", i, j,ARRAY(i,j), sizeof(GzPixel));
	pixel->red = r;
	pixel->green = g;
	pixel->blue = b;
	pixel->alpha = a;
	pixel->z = z;
	return GZ_SUCCESS;
}


int GzGetDisplay(GzDisplay *display, int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z)
{
	/* pass back pixel value in the display */
	int maxX = display->xres;
	int maxY = display->yres;
	
	if(i < 0||i >= maxX|| j < 0 || j >= maxY) 
		return GZ_FAILURE;
		
	GzPixel *pixel = &(display->fbuf[ARRAY(i,j)]);
	*r = pixel -> red;
	*g = pixel -> green ;
	*b = pixel -> blue ;
	*a = pixel -> alpha;
	*z = pixel -> z;
	
	return GZ_SUCCESS;
}



int GzFlushDisplay2File(FILE* outfile, GzDisplay *display)
{

	/* write pixels to ppm file -- "P6 %d %d 255\r" */
	unsigned short x = display -> xres;
	unsigned short y = display -> yres;
	GzPixel *fbuf = display -> fbuf;
	int num = 0;
	int count = 0;
	short r, g, b;
	unsigned char cr, cg, cb;

	fprintf(outfile, "P6 %d %d 255\r", x , y);
	
	for(num=0; num<x*y; num++){
		r = fbuf[num].red;
		g = fbuf[num].green;
		b = fbuf[num].blue;
		cr = (unsigned char)(r >> 4);
		cg = (unsigned char)(g >> 4);
		cb = (unsigned char)(b >> 4);
		
		fprintf(outfile, "%c%c%c",cr,cg,cb);
	}
	
	return GZ_SUCCESS;
}

int GzFlushDisplay2FrameBuffer(char* framebuffer, GzDisplay *display)
{

	/* write pixels to framebuffer: 
		- Put the pixels into the frame buffer
		- Caution: store the pixel to the frame buffer as the order of blue, green, and red 
		- Not red, green, and blue !!!
	*/
	unsigned short x = display->xres;
	unsigned short y = display->yres;
	
	GzPixel *fbuf = display->fbuf;
	
	int num = 0;
	int count = 0;
	short r, g, b, a, z;
	unsigned char cr, cg, cb;
	for(num = 0; num<x*y; num++){
		r = fbuf[num].red;
		g = fbuf[num].green;
		b = fbuf[num].blue;

		cr = (unsigned char)(r >> 4);
		cg = (unsigned char)(g >> 4);
		cb = (unsigned char)(b >> 4);

		framebuffer[count++] = cb;
		framebuffer[count++] = cg;
		framebuffer[count++] = cr;
	}
	
	return GZ_SUCCESS;
}