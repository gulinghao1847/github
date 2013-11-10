/* Texture functions for cs580 GzLib	*/
#include    "stdafx.h" 
#include	"stdio.h"
#include	"Gz.h"
#include  "math.h"
#define	IMG_ARRAY(x,y,xs)	(x+(y*xs))
#define NUM 200
#define COLORFUL 0
extern void numMulVector(GzCoord* vec, float num, GzCoord*);
extern void vecAdd(GzCoord* first, GzCoord* second, GzCoord* result);
extern void putVertValue(GzCoord coord, GzCoord* newCoord);


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
		int colorNum;
		GzColor color[7];
public:
	void init();
	void getColor(float lengthX, int scale, GzColor color);
};

void CLUT::init(){
	float fact = (float)1 / (float)255;
	//TRACE("FACT: %f", fact);
	//000
	color[0][0] = 0 * fact;
	color[0][1] = 0 * fact;
	color[0][2] = 0 * fact;
	//001
	color[1][0] = (float)0 * fact;
	color[1][1] = (float)0 * fact;
	color[1][2] = (float)255 * fact;
	//010
	color[2][0] = (float)0 * fact;
	color[2][1] = (float)255 * fact;
	color[2][2] = (float)0 * fact;
	//100
	color[3][0] = (float)0 * fact;
	color[3][1] = (float)255 * fact;
	color[3][2] = (float)255 * fact;
	//101
	color[4][0] = (float)255 * fact;
	color[4][1] = (float)0 * fact;
	color[4][2] = (float)0 * fact;
	//110:
	color[5][0] = (float)255 * fact;
	color[5][1] = (float)255 * fact;
	color[5][2] = (float)0 * fact;
	//111:
	color[6][0] = (float)255 * fact;
	color[6][1] = (float)255 * fact;
	color[6][2] = (float)255 * fact;
	
	colorNum = 7;
}

void CLUT::getColor(float lengthX, int scale, GzColor result){
	float input = lengthX * ((colorNum - 1) / scale);
	int Si = input;
	//TRACE("lengthX: %f\n", lengthX);
	//TRACE("input: %f\n", input);
	//TRACE("Si: %d\n", Si);
	int Si_1 = (Si == colorNum - 1) ? Si : Si + 1;
	if(Si != Si_1){
		float a = ((float)Si_1 - input) / ((float)Si_1 - (float)Si);
		float b = (input - (float)Si) / ((float)Si_1 - (float)Si);
		//C = aCi + bCi+1
		GzColor Ci;
		GzColor Ci_1;
		//putVertValue(color[Si], &Ci);
		//putVertValue(color[Si_1], &Ci_1);
		numMulVector(&color[Si], a, &Ci);
		numMulVector(&color[Si_1], b, &Ci_1);
		result[0] = (Ci[0] + Ci_1[0]) / 2;
		result[1] = (Ci[1] + Ci_1[1]) / 2;
		result[2] = (Ci[2] + Ci_1[2]) / 2;
		//TRACE("R: %f, G: %f, B: %f\n", color[Si][0], color[Si][1], color[Si][2]);
		//TRACE("R: %f, G: %f, B: %f\n", result[0], result[1], result[2]);
	}
	else{
		result[0] = color[colorNum - 1][0];
		result[1] = color[colorNum - 1][1];
		result[2] = color[colorNum - 1][2];
	}
}

/* Procedural texture function */
int ptex_fun(float u, float v, GzColor color)
{
        int N = NUM;
		CLUT lookUp;
		lookUp.init();
        complexNumber x;
        complexNumber c;
        //C
        c.r = -0.642133;
        c.i = 0.4232323;

        x.r = 2*u - 0.9;
		x.i = v - 0.7;
        int i;
        float clr;
		for(i = 0; i < N; i++)
		{
			float xr = x.r * x.r - x.i * x.i + c.r;
			float xi = x.r * x.i + x.i * x.r + c.i;
			if ((xr * xr + xi * xi) > 4.0)
			{
				break;
			}
			x.r = xr;
			x.i = xi;
		}
	
		float lengthX = sqrt(x.r * x.r + x.i * x.i);
		if (i == N)
		{
#if 0
			color[0] = color[1] = color[2] = lengthX / 4;
#else
			lookUp.getColor(lengthX, 1, color);
#endif
		}
		else
		{	
			color[2] = (float)i / (float)N  * 15;
			color[0] = (float)i / (float)N  * 14;
			color[1] = (float)i / (float)N  * 7;
		}
		 return GZ_SUCCESS;
}

/* Free texture memory */
int GzFreeTexture()
{
	if(image!=NULL)
		free(image);
	return GZ_SUCCESS;
}

