/*
 * Gz.h - include file for the cs580 rendering library
 */

/*
 * universal constants
 */
#define GZ_SUCCESS      0
#define GZ_FAILURE      1

/*
 * name list tokens
 */
#define GZ_NULL_TOKEN         0	/* triangle vert attributes */
#define GZ_POSITION           1
#define GZ_NORMAL             2
#define GZ_TEXTURE_INDEX      3

#define GZ_RGB_COLOR     99		/* renderer-state pixel color */

#define GZ_INTERPOLATE		95	/* interpolation mode */

#define GZ_DIRECTIONAL_LIGHT	79	/* directional light */
#define GZ_AMBIENT_LIGHT		78	/* ambient light type */

#define GZ_AMBIENT_COEFFICIENT	1001	/* Ka material property */
#define GZ_DIFFUSE_COEFFICIENT	1002	/* Kd material property */
#define GZ_SPECULAR_COEFFICIENT	1003	/* Ks material property */
#define GZ_DISTRIBUTION_COEFFICIENT  1004	/* specular power */

/*
 * flags fields for value list attributes
 */

/* select interpolation mode of the shader (select one) */
#define	GZ_FLAT  		0	/* flat shading with GZ_RBG_COLOR */
#define	GZ_COLOR		1	/* interpolate vertex color */
#define	GZ_NORMALS		2	/* interpolate normals */

typedef int     GzToken;
typedef void    *GzPointer;
typedef float   GzColor[3];
typedef short   GzIntensity;	/* 0 - 4095 in lower 12-bits */
typedef float   GzCoord[3];
typedef float   GzTextureIndex[2];
typedef float   GzMatrix[4][4];
typedef int	GzDepth;		/* z is signed for clipping */

/*
 * Gz camera definition
 */
#ifndef GZCAMERA
#define GZCAMERA
typedef struct  GzCamera
{
   GzMatrix        Xiw;  	/* xform from world to image space */
   GzMatrix        Xpi;    /* perspective projection xform */
   GzCoord         position; /* position of image plane origin */
   GzCoord         lookat;   /* position of look-at-point */
   GzCoord         worldup;  /* world up-vector */
   float           FOV;      /* horizontal field of view */
} GzCamera;
#endif

#ifndef GZLIGHT
#define GZLIGHT
typedef struct  GzLight
{
    GzCoord   direction;	/* vector from surface to light */
    GzColor      color;	/* light color intensity */
} GzLight;
#endif

#ifndef GZINPUT
#define GZINPUT
typedef struct  GzInput
{
 	GzCoord 	rotation;       /* object rotation */
	GzCoord	translation;	/* object translation */
	GzCoord	scale;		/* object scaling */
	GzCamera		camera;			/* camera */
	GzLight		light;			/* light */
} GzInput;

#endif

#define RED     0        /* array indicies for color vector */
#define GREEN   1
#define BLUE    2

#define X       0        /* array indicies for position vector */
#define Y       1
#define Z       2

#define U       0        /* array indicies for texture coords */
#define V       1
