/* 
*  disp.h -- include file for Display
*  USC csci 580 
*/

/* define general display pixel-type */
#include	"gz.h"

#ifndef GZ_PIXEL
typedef	struct {
  GzIntensity    red;	
  GzIntensity    green;
  GzIntensity    blue;
  GzIntensity    alpha;
  GzDepth	 z;
} GzPixel;
#define GZ_PIXEL
#endif;

 
/* define a display type */
#ifndef GZ_DISPLAY
typedef struct {
  unsigned short	xres;
  unsigned short	yres;
  GzPixel		*fbuf;		/* frame buffer array */
} GzDisplay;
#define GZ_DISPLAY
#endif;

#define	MAXXRES	1024	/* put some bounds on size in case of error */
#define	MAXYRES	1024

#define	ARRAY(x,y)	(x+(y*display->xres))	/* simplify fbuf indexing */

// Function declaration
int GzNewFrameBuffer(char** framebuffer, int width, int height);
int GzNewDisplay(GzDisplay **display, int xRes, int yRes);
int GzFreeDisplay(GzDisplay	*display);
int GzGetDisplayParams(GzDisplay *display, int *xRes, int *yRes);
int GzInitDisplay(GzDisplay	*display);
int GzPutDisplay(GzDisplay	*display, int i, int j, 
		GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z);
int GzGetDisplay(GzDisplay *display, int i, int j, 
		GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth	*z);
int GzFlushDisplay2File(FILE* outfile, GzDisplay *display);
int GzFlushDisplay2FrameBuffer(char* framebuffer, GzDisplay* display);
