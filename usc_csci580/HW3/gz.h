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
#define GZ_NULL_TOKEN           0	/* triangle vert attributes */
#define GZ_POSITION             1
#define GZ_NORMAL               2
#define GZ_TEXTURE_INDEX        3

/* renderer-state color values for default (flat) shading */
#define GZ_RGB_COLOR            99	/* we use RGB color space */


#define GZ_SHADER			96	/* define the shade mode */

 /*
 * flags fields for value list attributes
 */

/* shade mode flags combine the bit fields below */
#define	GZ_NONE			0	/* flat shading only */
#define	GZ_AMBIENT			1	/* can be selected or not */
#define	GZ_DIFFUSE			2	/* can be selected or not */
#define 	GZ_SPECULAR		4	/* can be selected or not */

#define GZ_DIRECTIONAL_LIGHT	79	/* directional light */
#define GZ_AMBIENT_LIGHT		78	/* ambient light type */

#define GZ_AMBIENT_COEFFICIENT		1001	/* Ka material property */
#define GZ_DIFFUSE_COEFFICIENT		1002	/* Kd material property */
#define GZ_SPECULAR_COEFFICIENT		1003	/* Ks material property */
#define GZ_DISTRIBUTION_COEFFICIENT	1004	/* specular power of material */

#define	GZ_TEXTURE_MAP			1010	/* pointer to texture routine */

/* select interpolation mode of the shader (either one - not both) */
#define	GZ_COLOR		1	/* interpolate vertex color */
#define	GZ_NORMALS		2	/* interpolate normals */

/*
 * As far as the application is concerned, the renderer
 * and the display are of type void *.
 * Naturally the rendering and display routines will define
 * them however they wish.
 */

#ifndef GZDATA
#define GZDATA
typedef int     GzToken;
typedef void    *GzPointer;
typedef float   GzColor[3];
typedef short   GzIntensity;	/* 0 - 4095 in lower 12-bits */
typedef float   GzCoord[3];
typedef float	GzTextureIndex[2];
typedef float	GzMatrix[4][4];
typedef int		GzDepth;	/* z is signed for clipping */
typedef int		(*GzTexture)();	/* pointer to texture sampling method */
#endif

/*
 * Gz camera definition - for making Xiw with rotations, scaling, translations.  
 * Perspective projection is separate Xpi. 
 */
#ifndef GZCAMERA
#define GZCAMERA
typedef struct  GzCamera
{
        GzMatrix        Xiw;  		  /* xform from world to image space */
        GzMatrix        Xpi;            /* perspective projection xform */
        GzCoord         position;       /* position of image plane origin */
        GzCoord         lookat;         /* position of look-at-point */
        GzCoord         worldup;        /* world up-vector (almost screen up) */
        float           FOV;            /* horizontal field of view */
} GzCamera;
#endif

/*
 * User input data definition 
 * If you want to add more user input data, use this stucture
 */
#ifndef GZINPUT
#define GZINPUT
typedef struct  GzInput
{
        GzCoord         rotation;       /* object rotation */
		GzCoord			translation;	/* object translation */
		GzCoord			scale;			/* object scaling */
		GzCamera		camera;			/* camera */
} GzInput;
#endif

#define RED     0         /* array indicies for color vector */
#define GREEN   1
#define BLUE    2

#define X       0        /* array indicies for position vector */
#define Y       1
#define Z       2

#define U       0        /* array indicies for texture coords */
#define V       1

