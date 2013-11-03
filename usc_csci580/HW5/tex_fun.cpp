/* Texture functions for cs580 GzLib	*/
#include    "stdafx.h" 
#include	"stdio.h"
#include	"Gz.h"
#include  "math.h"
#define	IMG_ARRAY(x,y,xs)	(x+(y*xs))
#define NUM 200

GzColor	*image=NULL;
int xs, ys;
int reset = 1;

/* Image texture function */

int tex_fun(float u, float v, GzColor color)
{
  unsigned char		pixel[3];
  unsigned char     dummy;
  char  		foo[8];
  int   		i, j;
  FILE			*fd;

  if (reset) {          /* open and load texture file */
    fd = fopen ("texture", "rb");
    if (fd == NULL) {
      fprintf (stderr, "texture file not found\n");
      exit(-1);
    }
    fscanf (fd, "%s %d %d %c", foo, &xs, &ys, &dummy);
    image = (GzColor*)malloc(sizeof(GzColor)*(xs+1)*(ys+1));
    if (image == NULL) {
      fprintf (stderr, "malloc for texture image failed\n");
      exit(-1);
    }

    for (i = 0; i < xs*ys; i++) {	/* create array of GzColor values */
      fread(pixel, sizeof(pixel), 1, fd);
      image[i][RED] = (float)((int)pixel[RED]) * (1.0 / 255.0);
      image[i][GREEN] = (float)((int)pixel[GREEN]) * (1.0 / 255.0);
      image[i][BLUE] = (float)((int)pixel[BLUE]) * (1.0 / 255.0);
      }

    reset = 0;          /* init is done */
	fclose(fd);
  }

/* bounds-test u,v to make sure nothing will overflow image array bounds */
/* determine texture cell corner values and perform bilinear interpolation */
/* set color to interpolated GzColor value and return */
  
  float s, t;
  //bounds check
  if(u > 1) u = 1.0;
  if(u < 0) u = 0.0;
  if(v > 1) v = 1.0;
  if(v < 0) v = 0.0;
  
  //scale u and v;
  u = u * (xs - 1);
  v = v * (ys - 1);
  
  //get s and t
  s = u - (int)u;
  t = v - (int)v;
  
  //get four neary-by nodes
  int pixelA, pixelB;
  pixelA = (int)u;
  pixelB = (int)v;
  //TRACE("%d,%d\n",pixelA, pixelB);
  int a_max = pixelA == (xs - 1) ? (xs - 1) : pixelA + 1;
  int b_max = pixelB == (ys - 1) ? (ys - 1) : pixelB + 1;
  GzCoord& A = image[pixelA + pixelB * xs];
  GzCoord& B = image[(a_max) + pixelB * xs];
  GzCoord& D = image[pixelA + (b_max) * xs];
  GzCoord& C = image[(a_max) + (b_max) * xs];
  
  //calculate color
  for(int idx = 0; idx < 3; idx++){
	  color[idx] = s*t*C[idx] + (1 - s) * t * D[idx] + s * (1 - t) * B[idx] + (1 - s) * (1 - t) * A[idx];
  }
}

class complexNumber
{
public:
        float r;
        float i;
        complexNumber() {};
        ~complexNumber() {};
};

class CLUT
{
private:
	float color[256][3];
public:
	void init();
	void getColor(float lengthX, int scale, GzColor color);
};

void CLUT::init(){
}

void CLUT::getColor(float lengthX, int scale, GzColor color){
}

/* Procedural texture function */
int ptex_fun(float u, float v, GzColor color)
{
        int N = NUM;
		CLUT lookUp;
        complexNumber x;
        complexNumber c;
        //C
        c.r = -0.74543;
        c.i = 0.11301;
        //X = u + vi
        x.r = u;
		x.i = v;
        int i;
        float clr;
    for(i = 0; i < N; i++)
        {
                //X ^ 2 + C
                //(XrYr - XiYi)r + Cr
        float xr = x.r * x.r - x.i * x.i + c.r;
                //(XrYi + XiYr)i + Ci
        float xi = x.r * x.i + x.i * x.r + c.i;
                if ((x.r * x.r + x.i * x.i) > 4.0)
                {
                        break;
                }
        x.r = xr;
        x.i = xi;
    }
    float lengthX = sqrt(x.r * x.r + x.i * x.i);
	lookUp.getColor(lengthX, 2, color);
    return GZ_SUCCESS;
}

/* Free texture memory */
int GzFreeTexture()
{
	if(image!=NULL)
		free(image);
	return GZ_SUCCESS;
}

