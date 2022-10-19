#pragma once
#include "Shaders.h"
#include "StoneHenge.h"
#include "StoneHenge_Texture.h"
void PlotAPixel(int x, int y, float z, unsigned int color)
{
	if ((x >= 0 && y >= 0))
	{
		unsigned int here = TwoToOne(x, y, WIDTH);
		float upZ = zBuffer[here];
		if(z <= upZ)
		{
			pixels[here] = color;
			zBuffer[here] = z;
		}
		
	}
	//else pixels[here] = pixels[here];
}


void reverseValues(unsigned int& reverseIt)
{
	unsigned int saveIt = reverseIt;
	//reverseIt = ARGB(BLUE(reverseIt), GREEN(reverseIt), RED(reverseIt), ALPHA(reverseIt));
	//(reverseIt) & 0xFF;
	auto a = (saveIt & 0x000000FF);
	auto r = (saveIt & 0x0000FF00) >> 8;
	auto g = (saveIt & 0x00FF0000) >> 16;
	auto b = (saveIt & 0xFF000000) >> 24;
	reverseIt = (((a) << 24) | ((r) << 16) | ((g) << 8) | ((b)));
}
void PS_White(unsigned int& makeWhite)
{
	makeWhite = 0xFFFFFFFF;
}
void PS_Green(unsigned int& makeGreen)
{
	makeGreen = 0xFF00FF00;
}
void PS_Red(unsigned int& makeRed)
{
	makeRed = 0xFFFF0000;
}
void PS_Yellow(unsigned int& makeYellow)
{
	makeYellow = 0xFFFFFF00;
}
void PS_Blue(unsigned int& makeBlue)
{
	makeBlue = 0xFF0000FF;
}

//void MidpointLineAlgorithm(VERTEX_2D start, VERTEX_2D end)
//{
//	int currentX = start.pos.x;
//	int currentY = start.pos.y;
//	for (int i = 0; i < (start.pos.x - end.pos.x); ++i)
//	{
//		//PixelShader = PS_White;
//		PlotAPixel(currentX, currentY, start.color);
//		VEC_2D midpoint = currentX + 1, currentY + 0.05f;
//		if(ImplicitLine())
//	}
//}
void ParametricLine(VERTEX a, VERTEX b)
{
	float deltaX = b.pos.x - a.pos.x;
	float deltaY = b.pos.y - a.pos.y;
	float totalPixels = (deltaX > deltaY) ? deltaX : deltaY;
	for (float i = 0; i < totalPixels; ++i)
	{
		float ratio = i / totalPixels;
		float currentX = LERP(a.pos.x, b.pos.x, ratio);
		float currentY = LERP(a.pos.y, b.pos.y, ratio);
	}
}
void DrawLine(VERTEX& a, VERTEX& b)
{
	auto copyA = a;
	auto copyB = b;
	if(VertexShader)
	{
		VS_3D(copyA);
		VS_3D(copyB);
	}
	copyA = CartesianConversion(copyA);
	copyB = CartesianConversion(copyB);
	float deltaX = abs(copyB.pos.x - copyA.pos.x);
	float deltaY = abs(copyB.pos.y - copyA.pos.y);
	float totalPixels = (deltaX > deltaY) ? deltaX : deltaY;
	for (float i = 0; i < totalPixels; ++i)
	{
		const float ratio = i / totalPixels;
		const float currentX = LERP(copyA.pos.x, copyB.pos.x, ratio);
		const float currentY = LERP(copyA.pos.y, copyB.pos.y, ratio);
		float z = LERP(copyA.pos.z, copyB.pos.z, ratio);
		PlotAPixel(currentX, currentY, z, a.color);
	}
}
//Make implicit line (again)
float ImplicitLineEq(VERTEX a, VERTEX b, VERTEX p)
{
	return (((a.pos.y - b.pos.y) * p.pos.x) + ((b.pos.x - a.pos.x) * p.pos.y) + (a.pos.x * b.pos.y) - (a.pos.y * b.pos.x));
}
//Make barycentric formula
VERTEX findBarry(VERTEX a, VERTEX b, VERTEX c, VERTEX p)
{
	float maxA = ImplicitLineEq(b, c, a);
	float subA = ImplicitLineEq(b, c, p);

	float maxB = ImplicitLineEq(a, c, b);
	float subB = ImplicitLineEq(a, c, p);

	float maxC = ImplicitLineEq(b, a, c);
	float subC = ImplicitLineEq(b, a, p);

	return {subA / maxA, subB / maxB, subC / maxC};
}

//Fill triangle(brute): for all pixels bya = findBarry(currX, currY); if (b >= 0 && b <= 1 && y >= 0 && y <= 1 && a >= 0 && a <= 1) PlotAPixel(currX, currY);
void fillTriangle(VERTEX& a2c, VERTEX& b2c, VERTEX& c2c, VERTEX color)
{
	VERTEX a = a2c;
	VERTEX b = b2c;
	VERTEX c = c2c;
	
	if (VertexShader)
	{
		VS_3D(a);
		VS_3D(b);
		VS_3D(c);
	}
	a = CartesianConversion(a);
	b = CartesianConversion(b);
	c = CartesianConversion(c);
	float startX = WIDTH;
	float startY = HEIGHT;
	float endX = 0;
	float endY = 0;
	if(a.pos.x < WIDTH) startX = a.pos.x;
	if (b.pos.x < startX) startX = b.pos.x;
	if (c.pos.x < startX) startX = c.pos.x;
	if(a.pos.y < HEIGHT) startY = a.pos.y;
	if (b.pos.y < startY) startY = b.pos.y;
	if (c.pos.y < startY) startY = c.pos.y;
	if(a.pos.x > endX) endX = a.pos.x;
	if (b.pos.x > endX) endX = b.pos.x;
	if (c.pos.x > endX) endX = c.pos.x;
	if(a.pos.y > endY) endY = a.pos.y;
	if (b.pos.y > endY) endY = b.pos.y;
	if (c.pos.y > endY) endY = c.pos.y;
	
	for (int y = startY; y < endY; ++y)
	{
		for (int x = startX; x < endX; ++x)
		{
			VERTEX barry = findBarry(a, b, c, {x * 1.0f, y * 1.0f, 0, 0 });
			if (barry.pos.x >= 0 && barry.pos.x <= 1.0f && barry.pos.y >= 0 && barry.pos.y <= 1.0f && barry.pos.z >= 0 && barry.pos.z <= 1.0f)
			{
				float z = (a.pos.z * barry.pos.x) + (b.pos.z * barry.pos.y) + (c.pos.z * barry.pos.z);
				float u = (a.uv.u * barry.pos.x) + (b.uv.u * barry.pos.y) + (c.uv.u * barry.pos.z);
				float v = (a.uv.v * barry.pos.x) + (b.uv.v * barry.pos.y) + (c.uv.v * barry.pos.z);
				u = u * (IMAGEWIDTH);
				v = v * (IMAGEHEIGHT);

				unsigned int colorMe = TwoToOne(u, v, IMAGEWIDTH);
				unsigned int thisColor = StoneHenge_pixels[colorMe];
				reverseValues(thisColor);
				unsigned int tempColor =  LerpTheColors(a.color, b.color, c.color, barry);
				thisColor = ModulateColors(thisColor, tempColor);
				if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)PlotAPixel(x, y, z, thisColor);
			}
		}
	}
}