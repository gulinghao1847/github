/* CS580 Homework 3 */

#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
#include	"Gz.h"
#include	"rend.h"

#define LEFT 1
#define RIGHT 2
#define TOP 1
#define BOTTOM 3
#define MID 2
#define LINE_TOP 2
#define LINE_BOTTOM 1
#define	RENDARRAY(x,y)	(x+(y*render->display->xres))
#define PI 3.14159265
#define DEG_TO_RAD(x) (x)*(PI/180)

typedef struct tagEdge{
	GzCoord startVert;
	GzCoord endVert;
	float a, b, c; 
	int position;	
}edge;

typedef struct tagPlane{
	float a;
	float b;
	float c;
	float d;
}plane;

typedef struct tagVert{
	GzCoord coord;
	int postion;
}vert;

typedef struct tagCheckBound{
	float minX;
	float maxX;
	float minY;
	float maxY;
}checkBound;

typedef struct tagVector{
	float x;
	float y;
	float z;
}vector;


//-------------------------------------------------DEBUG FUNCTIONS----------------------------------------------------------------------
void printMatrix(GzMatrix matrix){
	TRACE("---------------------------------------MATRIX------------------------------------------\n");
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			TRACE("%f        ", matrix[i][j]);
		}
		TRACE("\n");
	}
	TRACE("----------------------------------------END--------------------------------------------\n");
}

//--------------------------------------------------END---------------------------------------------------------------------------------------



//----------------------------------------HW3 FUNCTION HEADERS-----------------------------------------------------

int GzPushMatrix(GzRender *render, GzMatrix	matrix);
void errorCall(char* funcName, char* error);
short	ctoi(float color);
void normalize(GzCoord* vec);
void matrixCopy(const GzMatrix a, GzMatrix* b, int x, int y);
float dotProFun(GzCoord a, GzCoord b);
void matrixMul(GzMatrix a, GzMatrix b, GzMatrix* result, int row, int column, int same);
int checkValidToScreen(GzRender *render, GzCoord *verts, GzCoord *cVerts);
bool triangleOutsideImagePlane( GzRender * render, GzCoord * verts );
void initCamera(GzCamera& camera);
void computeXpi(GzRender* render);
void computeXsp(GzRender* render);
void computeXiw(GzRender* render);
void initMatrix(GzMatrix* matrix, int num);

//----------------------------------------HW2 FUNCTION HEADERS------------------------------
void putVertValue(GzCoord coord, GzCoord* newCoord);
void exchangeValue(float* x, float* y);
void sort(float*x, float* y, float* z);
int Position(float value, int position, vert* vert1);
vert* findPosition(float value, int position, vert* vert1, vert* vert2, vert* vert3);
float getXValue(vert top, vert mid, vert bot);
void getEdge(edge* triEdge, vert* top, vert* mid, vert* bot);
void getABC(edge* myEdge);
void getEdgeHor(edge* edges, vert diff, vert same1, vert same2);
void putSameVert(vert* same1, vert* same2, vert vert1, vert vert2);
void findDiff(vert* diff, vert* same1, vert* same2, vert vert1, vert vert2, vert vert3);
void getTri(vert* vert1, vert* vert2, vert* vert3, edge* triEdge);
void getCheckBound(checkBound* bound, vert vert1, vert vert2, vert vert3);
int checkEach(int x, int y, edge myEdge);
void getPlane(edge edge1, edge edge2 ,plane* myPlane, vert v);
int checkValid(int x, int y, edge* myEdges);
int checkZBuffer(int x, int y, plane myPlane,GzDepth* orgZ);
GzDepth getFbuf(GzRender* render, int x, int y);
void DoLEE(GzRender* render, GzCoord* tri);







int GzRotXMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along x axis
// Pass back the matrix using mat value
	float rad = DEG_TO_RAD(degree);

	mat[0][0] = 1;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = 0;

	mat[1][0] = 0;
	mat[1][1] = cos(rad);
	mat[1][2] = -sin(rad);
	mat[1][3] = 0;

	mat[2][0] = 0;
	mat[2][1] = sin(rad);
	mat[2][2] = cos(rad);
	mat[2][3] = 0;

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;

	return GZ_SUCCESS;
}


int GzRotYMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along y axis
// Pass back the matrix using mat value
	float rad = DEG_TO_RAD(degree);

	mat[0][0] = cos(rad);
	mat[0][1] = 0;
	mat[0][2] = sin(rad);
	mat[0][3] = 0;

	mat[1][0] = 0;
	mat[1][1] = 1;
	mat[1][2] = 0;
	mat[1][3] = 0;

	mat[2][0] = -sin(rad);
	mat[2][1] = 0;
	mat[2][2] = cos(rad);
	mat[2][3] = 0;

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
	
	return GZ_SUCCESS;
}


int GzRotZMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along z axis
// Pass back the matrix using mat value
	float rad = DEG_TO_RAD(degree);

	mat[0][0] = cos(rad);
	mat[0][1] = -sin(rad);
	mat[0][2] = 0;
	mat[0][3] = 0;

	mat[1][0] = sin(rad);
	mat[1][1] = cos(rad);
	mat[1][2] = 0;
	mat[1][3] = 0;

	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = 0;
	mat[2][3] = 1;

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
	return GZ_SUCCESS;
}


int GzTrxMat(GzCoord translate, GzMatrix mat)
{
// Create translation matrix
// Pass back the matrix using mat value
	mat[0][0] = 1;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = translate[0];

	mat[1][0] = 0;
	mat[1][1] = 1;
	mat[1][2] = 0;
	mat[1][3] = translate[1];

	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = 1;
	mat[2][3] = translate[2];

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
	return GZ_SUCCESS;
}


int GzScaleMat(GzCoord scale, GzMatrix mat)
{
// Create scaling matrix
// Pass back the matrix using mat value
	mat[0][0] = scale[0];
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = 0;

	mat[1][0] = 0;
	mat[1][1] = scale[1];
	mat[1][2] = 0;
	mat[1][3] = 0;

	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = scale[2];
	mat[2][3] = 0;

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
	return GZ_SUCCESS;
}

//----------------------------------------------------------
// Begin main functions
int GzNewRender(GzRender **render, GzDisplay	*display)
{
/*  
- malloc a renderer struct 
- setup Xsp and anything only done once 
- save the pointer to display 
- init default camera 
*/ 
	//init a renderer struct
	if(render == NULL || display == NULL){
		errorCall("GzNewRender" , "render == NULL or display == NULL");
		return GZ_FAILURE;
	}
	
	*render = (GzRender*)malloc(sizeof(GzRender));
	(*render)->display = display;
	
	//init default camera
	initCamera((*render) -> camera);
	
	return GZ_SUCCESS;
}


int GzFreeRender(GzRender *render)
{
/* 
-free all renderer resources
*/

	free(render -> display);
	free(render);
	
	return GZ_SUCCESS;
}


int GzBeginRender(GzRender *render)
{
/*  
- setup for start of each frame - init frame buffer color,alpha,z
- compute Xiw and projection xform Xpi from camera definition 
- init Ximage - put Xsp at base of stack, push on Xpi and Xiw 
- now stack contains Xsw and app can push model Xforms when needed 
*/ 
	if(render == NULL){
		errorCall("GzBeginRender","render is null");
		return GZ_FAILURE;
	}
	//setup for start of each frame, only one frame
	GzInitDisplay(render->display);

	//init matlevel
	render->matlevel = -1;
	
	//Compute Xsp
	computeXsp(render);
	
	//compute Xiw
	computeXiw(render);
	
	//compute Xpi
	computeXpi(render);
	
	//push Xsp Xpi Xiw
	GzPushMatrix(render,render->Xsp);
	GzPushMatrix(render,render->camera.Xpi);
	GzPushMatrix(render,render->camera.Xiw);
	
	return GZ_SUCCESS;
}

int GzPutCamera(GzRender *render, GzCamera *camera)
{
/*
- overwrite renderer camera structure with new camera definition
*/
	if(render ==NULL|| camera == NULL)
	{
		errorCall("GzPutCamera","render or camera is null");
	}

	render->camera = *camera;

	return GZ_SUCCESS;	
}


int GzPushMatrix(GzRender *render, GzMatrix	matrix)
{
/*
- push a matrix onto the Ximage stack
- check for stack overflow
*/
	//init if render->matlevel = -1
	if(render->matlevel == -1){
		initMatrix(&(render->Ximage[0]),4);
		(render->Ximage[0])[0][0] = 1;
		(render->Ximage[0])[1][1] = 1;
		(render->Ximage[0])[2][2] = 1;
		(render->Ximage[0])[3][3] = 1;
		render->matlevel += 1;
	}
	
	if(render->matlevel > -1)
	{
		if (render->matlevel < MATLEVELS - 1)
		{
			//GzMatrix tempMatrix;
			//matrixCopy(matrix, &tempMatrix,4,4);
			render->matlevel += 1;
			initMatrix(&(render->Ximage[render->matlevel]),4);
			matrixMul(render->Ximage[render->matlevel-1], matrix, &(render->Ximage[render->matlevel]),4,4,4);
		}else
		{
			errorCall("GzPushMatrix","matlevel >= MATLEVELS");
			AfxMessageBox( "Matrix has full\n" );
			return GZ_FAILURE;
		}
	}else
	{
		errorCall("GzPushMatrix", "render->matlevel < -1");
		//return GZ_FAILURE;
	}

	return GZ_SUCCESS;
}

int GzPopMatrix(GzRender *render)
{
/*
- pop a matrix off the Ximage stack
- check for stack underflow
*/
	if(render->matlevel == 0)
	{
		errorCall("GzPopMatrix","app try to pop up a matrix when render->matlevel == 0");
		 AfxMessageBox( "Matrix is empty\n" );
		 GZ_FAILURE;
	}else if(render->matlevel > 0 )
	{
		initMatrix(&(render->Ximage[render->matlevel]),4);
		render->matlevel -= 1;
	}else
	{
		errorCall("GzPopMatrix","render->matlevel < 0!!!");
	}
	return GZ_SUCCESS;
}


int GzPutAttribute(GzRender	*render, int numAttributes, GzToken	*nameList, 
	GzPointer	*valueList) /* void** valuelist */
{
/*
- set renderer attribute states (e.g.: GZ_RGB_COLOR default color)
- later set shaders, interpolaters, texture maps, and lights
*/
	for(int i = 0; i<numAttributes ; i++)
	{
		if(nameList[i] == GZ_RGB_COLOR)
		{
			GzColor* color = (GzColor*)(valueList[0]);
			
			render->flatcolor[RED] = color[0][RED];
			render->flatcolor[GREEN] = color[0][GREEN];
			render->flatcolor[BLUE] = color[0][BLUE];
			//TRACE("red: %f, green: %f, blue :%f",render->flatcolor[RED], render->flatcolor[GREEN], render->flatcolor[BLUE]);
		}
	}
	return GZ_SUCCESS;
}

int GzPutTriangle(GzRender	*render, int numParts, GzToken *nameList, GzPointer	*valueList)
/* numParts : how many names and values */
{
/*  
- pass in a triangle description with tokens and values corresponding to 
      GZ_POSITION:3 vert positions in model space 
- Xform positions of verts using matrix on top of stack 
- Clip - just discard any triangle with any vert(s) behind view plane 
       - optional: test for triangles with all three verts off-screen (trivial frustum cull)
- invoke triangle rasterizer  
*/ 
	for(int i = 0; i<numParts; i++)
	{
		int discard = 0;

		if(nameList[i] == GZ_NULL_TOKEN)
		{
			//DO NOTHING
		}else if(nameList[i] == GZ_POSITION)
		{
			GzCoord* tri = (GzCoord*)(valueList[0]);
			GzCoord* changedTri = (GzCoord*)malloc(sizeof(GzCoord)*3);
			discard = checkValidToScreen(render, tri, changedTri);
			if(!discard&&(render, changedTri))
			{
				DoLEE(render,changedTri);
			}
		}
	}
	return GZ_SUCCESS;
}

/*
----------------------------------------------all functions below are belong to GzPutTriangle from homework2--------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------
*/
//-------------------------------HW2 FUNCTIONS----------------------------------------------

void putVertValue(GzCoord coord, GzCoord* newCoord)
{
	(*newCoord)[0] = coord[0];
	(*newCoord)[1] = coord[1];
	(*newCoord)[2] = coord[2];

}

void exchangeValue(float* x, float* y){
	float temp;
	temp = *y;
	*y = *x;
	*x = temp;
}

void sort(float*x, float* y, float* z){    // x is the smallest value
	//float temp;
	if(*x>*y){
		exchangeValue(x,y);
	}
	if(*x>*z){
		exchangeValue(x,z);
	}
	if(*y>*z){
		exchangeValue(y,z);
	}
}

int Position(float value, int position, vert* vert1){
	int result = 0;
	if(value == vert1->coord[1]){
		vert1->postion = position;
		result = 1;
	}
	return result;
}

vert* findPosition(float value, int position, vert* vert1, vert* vert2, vert* vert3){
	vert* result;
	if(!Position(value, position, vert1)){
		if(!Position(value, position, vert2)){
			if(!Position(value, position, vert3)){
				TRACE("impossible in findPosition");
			}
			else
				result = vert3;
		}
		else
			result = vert2;
	}
	else
		result = vert1;
	return result;
}


float getXValue(vert top, vert mid, vert bot){
	float x1, y1;
	float x2, y2;
	float x3, y3;
	float x4, y4;
	x1 = top.coord[0];
	y1 = top.coord[1];
	x2 = mid.coord[0];
	y2 = mid.coord[1];
	x3 = bot.coord[0];
	y3 = bot.coord[1];
	y4 = mid.coord[1];

	x4 = ((y4-y1)*(x3-x1))/(y3-y1)+x1;
	return x4;
}

void getEdge(edge* triEdge, vert* top, vert* mid, vert* bot){  
	float x = mid->coord[0];
	float compX = getXValue(*top, *mid, * bot);
	if(x < compX){    //mid is left side
		putVertValue((*top).coord, &(triEdge[0].startVert));
		putVertValue((*bot).coord, &(triEdge[0].endVert));
		triEdge[0].position = RIGHT;

		putVertValue((*bot).coord, &(triEdge[1].startVert));
		putVertValue((*mid).coord, &(triEdge[1].endVert));
		triEdge[1].position = LEFT;

		putVertValue((*mid).coord, &(triEdge[2].startVert));
		putVertValue((*top).coord, &(triEdge[2].endVert));
		triEdge[2].position = LEFT;

	}else if(x > compX){     //mid is right side
		putVertValue((*top).coord, &(triEdge[0].startVert));
		putVertValue((*mid).coord, &(triEdge[0].endVert));
		triEdge[0].position = RIGHT;

		putVertValue((*mid).coord, &(triEdge[1].startVert));
		putVertValue((*bot).coord, &(triEdge[1].endVert));
		triEdge[1].position = RIGHT;

		putVertValue((*bot).coord, &(triEdge[2].startVert));
		putVertValue((*top).coord, &(triEdge[2].endVert));
		triEdge[2].position = LEFT;
	}else
		TRACE("impossible in getLandR");
}

void getABC(edge* myEdge){
	float dX, dY;
	dX = myEdge->endVert[0] - myEdge->startVert[0];
	dY = myEdge->endVert[1] - myEdge->startVert[1];
	myEdge->a = -dY;
	myEdge->b = dX;
	myEdge->c = -(dX*myEdge->startVert[1] - dY*myEdge->startVert[0]);

}


void getEdgeHor(edge* edges, vert diff, vert same1, vert same2){
	int position = diff.coord[1]>same1.coord[1]?1:0;// horizantial line top:1 bottom:0
	if(position)      //case top
	{
		putVertValue(same1.coord, &(edges[0].startVert));
		putVertValue(same2.coord, &(edges[0].endVert));
		edges[0].position = LINE_TOP;

		putVertValue(same2.coord, &(edges[1].startVert));
		putVertValue(diff.coord, &(edges[1].endVert));
		edges[0].position = RIGHT;

		putVertValue(diff.coord, &(edges[2].startVert));
		putVertValue(same1.coord, &(edges[2].endVert));
		edges[0].position = LEFT;
	}else
	{
		putVertValue(diff.coord, &(edges[0].startVert));
		putVertValue(same2.coord, &(edges[0].endVert));
		edges[0].position = RIGHT;

		putVertValue(same2.coord, &(edges[1].startVert));
		putVertValue(same1.coord, &(edges[1].endVert));
		edges[0].position = LINE_BOTTOM;

		putVertValue(same1.coord, &(edges[2].startVert));
		putVertValue(diff.coord, &(edges[2].endVert));
		edges[0].position = LEFT;
	}
}


void putSameVert(vert* same1, vert* same2, vert vert1, vert vert2)
{
	if(vert1.coord[0]>vert2.coord[0])
	{
		putVertValue(vert2.coord, &(same1->coord));
		putVertValue(vert1.coord, &(same2->coord));
	}else
	{
		putVertValue(vert2.coord, &(same2->coord));
		putVertValue(vert1.coord, &(same1->coord));
	}
}

void findDiff(vert* diff, vert* same1, vert* same2, vert vert1, vert vert2, vert vert3)
{
	int trace = 0;//which is the horizantial line
	if(!(vert1.coord[1] == vert2.coord[1]))
	{
		if(!(vert1.coord[1] == vert3.coord[3]))
		{
			if(!(vert3.coord[1] == vert2.coord[1]))
			{
				TRACE("impossible in findDiff");
			}else
				trace = 1;
		}else
			trace = 2;
	}else
		trace = 3;
	switch(trace)
	{
		case 1: 
			putVertValue(vert1.coord, &(diff->coord));
			putSameVert(same1, same2, vert2, vert3);
			break;
		case 2:
			putVertValue(vert2.coord, &(diff->coord));
			putSameVert(same1, same2, vert1, vert3);
			break;
		case 3:
			putVertValue(vert3.coord, &(diff->coord));
			putSameVert(same1, same2, vert1, vert2);
			break;
		default:
			TRACE("IMPOSSIBLE IN findDiff");
	}

}


//sort verts into top, mid, bot   aim: get the sequence of the triedge.
void getTri(vert* vert1, vert* vert2, vert* vert3, edge* triEdge)
{
	float top, mid, bot;
	vert* topVert;
	vert* midVert;
	vert* botVert;
    
    
	if((vert1->coord[1] != vert2->coord[1])&&(vert1->coord[1] != vert3->coord[1])&&(vert3->coord[1] != vert2->coord[1])){   //case 1
		top = vert1->coord[1];
		mid = vert2->coord[1];
		bot = vert3->coord[1];

		sort(&top, &mid, &bot);
		//TRACE("\n\n\nEdge_top: %f, Edge_mid: %f, Edge_bot: %f\n", top, mid, bot);
		topVert = findPosition(top, 1, vert1, vert2, vert3);
		midVert = findPosition(mid, 2, vert1, vert2, vert3);
		botVert = findPosition(bot, 3, vert1, vert2, vert3);
		

		//get left and right attribute
		getEdge(triEdge, topVert, midVert, botVert);

	}else if((vert1->coord[1] == vert2->coord[1])||(vert1->coord[1] == vert3->coord[1])||(vert3->coord[1] == vert2->coord[1])){
		vert diff, sameY1, sameY2;
		
		int position = 0; //HORIZANTAL LINE ; TOP = 1 OR BOTTOM = 0

		/*position = */findDiff(&diff, &sameY1, &sameY2, *vert1, *vert2, *vert3);   // let Y1 be the left vert and Y2 be the right vert.

		getEdgeHor(triEdge,diff, sameY1, sameY2);
	}
		//get A, B, C for each edge
		getABC(&triEdge[0]);
		getABC(&triEdge[1]);
		getABC(&triEdge[2]);
}


void getCheckBound(checkBound* bound, vert vert1, vert vert2, vert vert3){
	float x1 = vert1.coord[0];
	float x2 = vert2.coord[0];
	float x3 = vert3.coord[0];
	float y1 = vert1.coord[1];
	float y2 = vert2.coord[1];
	float y3 = vert3.coord[1];

	sort(&x1,&x2,&x3);
	sort(&y1,&y2,&y3);
	bound->maxX = x3;
	bound->minX = x1;
	bound->maxY = y3;
	bound->minY = y1;
}

int checkEach(int x, int y, edge myEdge){     //delete nodes that on left 
	float a, b, c/*, b1, b2, b3, c1, c2, c3*/;
	float result;
	int ret = 0;

	a = myEdge.a;
	b = myEdge.b;
	c = myEdge.c;

	result = a*x + b*y +c;
	//TRACE("Node: x: %d, y: %d, a: %f, b: %f, c: %f, result: %f\n",x, y,a,b,c, result);
	if(result >= 0)
		ret = 1;
	return ret;
}

void getPlane(edge edge1, edge edge2 ,plane* myPlane, vert v){
	float x1, y1, z1;
	float x2, y2, z2;

	x1 = edge1.endVert[0] - edge1.startVert[0];
	y1 = edge1.endVert[1] - edge1.startVert[1];
	z1 = edge1.endVert[2] - edge1.startVert[2];

	x2 = edge2.endVert[0] - edge2.startVert[0];
	y2 = edge2.endVert[1] - edge2.startVert[1];
	z2 = edge2.endVert[2] - edge2.startVert[2];

	myPlane->a = y1 * z2 - z1 * y2;
	myPlane->b = -( x1 * z2 - z1 * x2 );
	myPlane->c = x1 * y2 - y1 * x2;
	myPlane->d = -(myPlane->a*v.coord[0] + myPlane->b*v.coord[1] + myPlane->c*v.coord[2]);
}

int checkValid(int x, int y, edge* myEdges){
	return checkEach(x,y,myEdges[0])&&checkEach(x,y,myEdges[1])&&checkEach(x,y,myEdges[2]);
}

int checkZBuffer(int x, int y, plane myPlane,GzDepth* orgZ){
	float z;
	float a = myPlane.a;
	float b = myPlane.b;
	float c = myPlane.c;
	float d = myPlane.d;
	int ret = 0;
	z = -(a*x+b*y+d)/c;

	if(z < *orgZ)
	{	
		*orgZ = z;
		//TRACE("in checkBuffer, z: %f, orgZ: %d\n", z, *orgZ);
		ret = 1;
	}
	
	return ret;
}

GzDepth getFbuf(GzRender* render, int x, int y){
	int maxX = render->display->xres;
	int maxY = render->display->yres;
	if(!(x < 0 || x >= maxX || y >= maxY || y <0))
		return (render->display->fbuf[RENDARRAY(x,y)].z);
	else 
		return -1;
}

void DoLEE(GzRender* render, GzCoord* tri)
{
	/*
	float x1, y1, z1;
	float x2, y2, z2;
	float x3, y3, z3;
	*/
	GzPixel* pixel;
	vert vert1,vert2,vert3;
	edge triEdge[3];
	checkBound bound;
	plane triPlane;
	//GzCoord *tri = (GzCoord*)verts[0];
	GzDepth orgZ = 0; //depth
    
    //put value into verts
	putVertValue(tri[0], &vert1.coord);
	putVertValue(tri[1], &vert2.coord);
	putVertValue(tri[2], &vert3.coord);
    
    //sort verts using Y value
	getTri(&vert1, &vert2, &vert3, triEdge);
	getPlane(triEdge[0], triEdge[1], &triPlane, vert1);

	//get a rectangle bound to check value
	getCheckBound(&bound, vert1, vert2, vert3);
	//TRACE("minX: %f, maxX:  %f, minY: %f, maxY: %f \n", bound.minX, bound.maxX,bound.minY, bound.maxY);
	for(int i = bound.minY; i <= bound.maxY; i++)
	{
		for(int j = bound.minX; j <=bound.maxX; j++)
		{
			if(checkValid(j, i, triEdge)){             //implement later
				if((orgZ = getFbuf(render, j, i)) == -1)/*render->display->fbuf[RENDARRAY(j,i)].z;*/
				{
					continue;
				}
				//TRACE("orgZ = %d\n", orgZ);
				if(checkZBuffer(j, i, triPlane,&orgZ)){
					GzPutDisplay(render->display, j, i, ctoi(render->flatcolor[0]), ctoi(render->flatcolor[1]), ctoi(render->flatcolor[2]), 1, orgZ);
					//GzPutDisplay
				}
			}
		}
	}

}

//------------------------------------HW3 FUNCTIONS-------------------------------------
short	ctoi(float color)		/* convert float color to GzIntensity short */
{
  return(short)((int)(color * ((1 << 12) - 1)));
}


void errorCall(char* funcName, char* error){
	TRACE("Impossible in function: %s, the error is : %s",funcName, error);
	//exit(1);
}


void normalize(GzCoord* vec){
	
	float len = sqrt((*vec)[0]*(*vec)[0]+(*vec)[1]*(*vec)[1]+(*vec)[2]*(*vec)[2]);

	(*vec)[0] /= len;
	(*vec)[1] /= len;
	(*vec)[2] /= len;
}

void matrixCopy(const GzMatrix a, GzMatrix* b, int x, int y){
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			(*b)[i][j] = a[i][j];
		}
	}
}

float dotProFun(GzCoord a, GzCoord b){
	return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}

void initMatrix(GzMatrix* matrix, int num
				){

	for(int i = 0; i < num; i++){
		for(int j = 0; j < num; j++){
			(*matrix)[i][j] = 0;
		}
	}
}

void matrixMul(GzMatrix a, GzMatrix b, GzMatrix* result, int row, int column, int same){
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			for (int z = 0; z < same; z++)
			{
				(*result)[i][j] += a[i][z]*b[z][j];
			}
		}
	}
}

int checkValidToScreen(GzRender *render, GzCoord *verts, GzCoord *cVerts){
	GzMatrix& topMatrix = render->Ximage[render->matlevel];
	//TRACE("!!!!!");
	//printMatrix(topMatrix);
	float result[4];
	float vector[4];
	int discard = 0;

	for(int verIdx = 0; verIdx < 3; verIdx++)
	{
		if(discard == 1)
		{
			continue;
		}else
		{
			vector[0] = verts[verIdx][0];
			vector[1] = verts[verIdx][1];
			vector[2] = verts[verIdx][2];

			//TRACE("x: %f, y: %f, z: %f\n",vector[0], vector[1], vector[2]);
			vector[3] = 1;

			for (int i = 0; i < 4; i++)
			{
				result[i] = 0;
			}

			for (int row = 0; row < 4; row++)
			{
				for (int column = 0; column < 4; column++)
				{
					result [row] += topMatrix[row][column] * vector[column];
					
					//if(row == 0) TRACE("result [0]: %f\n", result[0]);
				}
			}

			if(result [2] <= 0)
			{
				discard = 1;
				//TRACE("z :%f\n", result[2]);
			}
			//TRACE("x: %f, y: %f, z: %f,w:%f\n",result [0], result [1],result [2],result [3]);
			cVerts[verIdx][0] = result [0] / result[3];
			cVerts[verIdx][1] = result [1] / result[3];
			cVerts[verIdx][2] = result [2] / result[3];
			//TRACE("x: %f, y: %f, z: %f\n",cVerts[verIdx][0], cVerts[verIdx][1],cVerts[verIdx][2]);
		}
	}
	return discard;

}

void initCamera(GzCamera& camera){
	camera.position[X] = DEFAULT_IM_X;      
	camera.position[Y] = DEFAULT_IM_Y;
  	camera.position[Z] = DEFAULT_IM_Z;

  	camera.lookat[X] = 0;
  	camera.lookat[Y] = 0;
  	camera.lookat[Z] = 0;

  	camera.worldup[X] = 0.0;
  	camera.worldup[Y] = 1.0;
  	camera.worldup[Z] = 0.0;

	camera.FOV = DEFAULT_FOV;
}

void computeXsp(GzRender* render){
	//compute Xsp
	//setup Xsp
	/*
			xs/2   0       0      xs/2
	Xsp =	0      -ys/2   0      ys/2
			0      0       Zmax/d 0
			0      0       0      1
	*/
	GzDisplay* display = render -> display;
	GzCamera& cam = render->camera;
	
	int a00 = (display->xres)/2;
	int a03 = a00;
	int a11 = -(display->yres)/2;
	int a13 = -a11;
	int Zmax = pow(2.0, (int)(sizeof(int)*8-1))-1;
	float d; //1/d
	d = 1/(tan((cam.FOV/2)*(PI/180)));
	int a22 = Zmax/d;//d = 1?
	initMatrix(&(render->Xsp),4);
	render->Xsp[0][0] = a00;
	render->Xsp[0][3] = a03;
	render->Xsp[1][1] = a11;
	render->Xsp[1][3] = a13;
	render->Xsp[2][2] = a22;
	render->Xsp[3][3] = 1;
	//printMatrix(render->Xsp);
}

void computeXiw(GzRender* render){
	//step 1: compute camera Z-axis
	GzCoord z_axis;
	GzDisplay* display = render -> display;
	GzCamera& cam = render->camera;

	z_axis[0] = cam.lookat[0] - cam.position[0];
	z_axis[1] = cam.lookat[1] - cam.position[1];
	z_axis[2] = cam.lookat[2] - cam.position[2];

	//normalize z_axis
	/*
	float z_len = sqrt(z_axis[0]*z_axis[0]+z_axis[1]*z_axis[1]+z_axis[2]*z_axis[2]);

	z_axis[0] /= z_len;
	z_axis[1] /= z_len;
	z_axis[2] /= z_len;
	*/
	normalize(&z_axis);
	//step 2: construct up': up' = up - (up(dot-product)Z)Z
	//up(dot-product)Z
	float dotPro = dotProFun(cam.worldup, z_axis);// = cam.worldup[0]*z_axis[0]+cam.worldup[1]*z_axis[1]+cam.worldup[2]*z_axis[2];
	//up'
	GzCoord up_;
	up_[0] = cam.worldup[0] - dotPro*z_axis[0];
	up_[1] = cam.worldup[1] - dotPro*z_axis[1];
	up_[2] = cam.worldup[2] - dotPro*z_axis[2];

	//normalize(&up_);

	//step3: construct X : X = (Y*Z) = (Yy*Zz - Yz Zy)i + (Yz*Zx - Yx*Zz)j + (YxZy - Yy*Zx)
	GzCoord _x;
	_x[0] = up_[1]*z_axis[2] - up_[2]*z_axis[1];
	_x[1] = up_[2]*z_axis[0] - up_[0]*z_axis[2];
	_x[2] = up_[0]*z_axis[1] - up_[1]*z_axis[0];
	
	//normalize x, y
	normalize(&_x);
	normalize(&up_);

	//construct Xiw
	float xC, yC, zC;
	xC = dotProFun(_x,cam.position);
	yC = dotProFun(up_,cam.position);
	zC = dotProFun(z_axis,cam.position);

	GzMatrix Xiw = {_x[0], _x[1], _x[2], -xC, 
					up_[0], up_[1], up_[2], -yC, 
					z_axis[0], z_axis[1], z_axis[2], -zC, 
					0, 0, 0, 1};

	matrixCopy(Xiw, &(render->camera.Xiw),4,4);
	//printMatrix(Xiw);
}

void computeXpi(GzRender* render){
	GzDisplay* display = render -> display;
	GzCamera& cam = render -> camera;
	float d; //1/d
	d = 1/(tan((cam.FOV/2)*(PI/180)));
	
	GzMatrix Xpi = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,1/d,1};
	matrixCopy(Xpi, &(render->camera.Xpi),4,4);
	//printMatrix(Xpi);
}

bool triangleOutsideImagePlane( GzRender * render, GzCoord * verts )
{
	
	if( !render || !render->display || !verts )
		return true; 

	if( verts[0][Y] < 0 && verts[1][Y] < 0 && verts[2][Y] < 0 )
		return true;
	else if( verts[0][Y] > render->display->yres && verts[1][Y] > render->display->yres && verts[2][Y] > render->display->yres )
		return true;
	else if( verts[0][X] < 0 && verts[1][X] < 0 && verts[2][X] < 0 )
		return true;
	else if( verts[0][X] > render->display->xres && verts[1][X] > render->display->xres && verts[2][X] > render->display->xres )
		return true;
	else
		return false;
}


