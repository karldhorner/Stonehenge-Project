#pragma once

//Width is actually height and height is actually width, because math. *FIXED*
#define WIDTH 1200
#define HEIGHT 800
#define IMAGEWIDTH 1024
#define IMAGEHEIGHT 512
#define TOTAL_PIXELS ((HEIGHT * WIDTH))
#define LERP(a, b, ratio) ((((b) - (a)) * (ratio) + (a)))
// ALPHA - BLUE : breaks up into channels
#define ALPHA(argb) (unsigned int)(argb >> 24)
#define RED(argb) (unsigned int)(argb >> 16)
#define GREEN(argb) (unsigned int)(argb >> 8)
#define BLUE(argb) (unsigned int)(argb)
// ARGB : puts channels back together
#define ARGB(a, r, g, b) (((a) << 24) | ((r) & 0xFF << 16) | ((g) & 0xFF << 8) | ((b) & 0xFF))

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#include "Math.h"
unsigned int pixels[TOTAL_PIXELS];
unsigned int buffer[TOTAL_PIXELS];
float zBuffer[TOTAL_PIXELS];
float lightRadius = 1.0f;

struct VEC
{
	float x, y, z, w;
};

struct UV
{
	float u, v;
};

struct NORMALS
{
	float i, j, k;
};
struct VERTEX
{
	VEC pos;
	UV uv;
	NORMALS nrml;
	unsigned int color;
};

struct MATRIX
{
	float x[4], y[4], z[4], w[4];
};


#pragma region Identity Matrix
MATRIX iD = {{1, 0, 0, 0}, {0, 1, 0, 0},{0, 0, 1, 0},{0, 0, 0, 1}};
#pragma endregion

#pragma region Translate Matrix
float zPos = -4.0f;
MATRIX tL = {{1, 0, 0 ,0}, {0, 1, 0, 0},{0, 0, 1, 0}, {0, 0, zPos, 1}};

#pragma endregion
float the = -1.5f * M_PI / 180;
float theOther = 0.5f * M_PI / 180;
MATRIX rotateByX = {{1,0,0,0},{0,cos(the),-sin(the),0},{0,sin(the),cos(the),0},{0,0,0,1}};
MATRIX rotateByY = {{cos(theOther), 0, -sin(theOther), 0}, {0, 1, 0, 0}, {sin(theOther), 0, cos(theOther), 0}, {0, 0, 0, 1}};

float aspect = (static_cast<float>(HEIGHT) / static_cast<float>(WIDTH));
float yScale = 1 / tan((90.0f * (M_PI /180)) / 2);


float xScale = yScale * aspect;
float nearPlane = 0.1f;
float farPlane = 500.0f;
MATRIX projection = {{xScale, 0, 0, 0}, {0,yScale, 0 ,0}, {0, 0, farPlane / (farPlane - nearPlane), 1}, {0, 0, -(farPlane * nearPlane) / (farPlane - nearPlane), 0}};

VERTEX DirectionalLight;
VERTEX PointLight;