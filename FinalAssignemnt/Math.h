#pragma once
#include <cmath>
#define  M_PI 3.141592653589793238462643383279502884f
#include "Defines.h"
static  void Vec4MultMatrix4(float v[4], float m[4][4])
{
	float temp[4];
	temp[0] = (v[0] * m[0][0]) + (v[1] * m[1][0]) + (v[2] * m[2][0] + (v[3] * m[3][0]));
	temp[1] = (v[0] * m[0][1]) + (v[1] * m[1][1]) + (v[2] * m[2][1] + (v[3] * m[3][1]));
	temp[2] = (v[0] * m[0][2]) + (v[1] * m[1][2]) + (v[2] * m[2][2] + (v[3] * m[3][2]));
	temp[3] = (v[0] * m[0][3]) + (v[1] * m[1][3]) + (v[2] * m[2][3] + (v[3] * m[3][3]));
	v[0] = temp[0];
	v[1] = temp[1];
	v[2] = temp[2];
	v[3] = temp[3];
}

inline VERTEX VertexMultMatrix(VERTEX& v, MATRIX& m)
{
	VERTEX temp = v;
	temp.pos.x = (v.pos.x * m.x[0]) + (v.pos.y * m.y[0]) + (v.pos.z * m.z[0]) + (v.pos.w * m.w[0]);
	temp.pos.y = (v.pos.x * m.x[1]) + (v.pos.y * m.y[1]) + (v.pos.z * m.z[1]) + (v.pos.w * m.w[1]);
	temp.pos.z = (v.pos.x * m.x[2]) + (v.pos.y * m.y[2]) + (v.pos.z * m.z[2]) + (v.pos.w * m.w[2]);
	temp.pos.w = (v.pos.x * m.x[3]) + (v.pos.y * m.y[3]) + (v.pos.z * m.z[3]) + (v.pos.w * m.w[3]);
	v.pos.x = temp.pos.x;
	v.pos.y = temp.pos.y;
	v.pos.z = temp.pos.z;
	v.pos.w = temp.pos.w;
	return temp;
}
static void Vec3MultMatrix3(float v[3], float m[3][3])
{
	float temp[3];
	temp[0] = (v[0] * m[0][0]) + (v[1] * m[1][0]) + (v[2] * m[2][0]);
	temp[1] = (v[0] * m[0][1]) + (v[1] * m[1][1]) + (v[2] * m[2][1]);
	temp[2] = (v[0] * m[0][2]) + (v[1] * m[1][2]) + (v[2] * m[2][2]);
	v[0] = temp[0];
	v[1] = temp[1];
	v[2] = temp[2];
}

inline unsigned int TwoToOne(unsigned int X, unsigned int Y, unsigned int W)
{
	const unsigned int returnIt = (Y * W) + X;

	return returnIt;
}
//VERTEX RotateX(VERTEX& c, float rad)
//{
//	rad = rad * (M_PI / 180);
//	float multMe[3] = {c.pos.x, c.pos.y, c.pos.z};
//	float matrix[3][3] = {{1, 0, 0}, {0, cos(rad), -sin(rad)}, {0, sin(rad), cos(rad)}};
//	Vec3MultMatrix3(multMe, matrix);
//	c.pos.x = multMe[0];
//	c.pos.y = multMe[1];
//	c.pos.z = multMe[2];
//	return c;
//}
inline void RotateX(VERTEX& c, float rad)
{
	rad = rad * (M_PI / 180);
	float multMe[4] = {c.pos.x, c.pos.y, c.pos.z, c.pos.w};
	float matrix[4][4] = {{1, 0, 0, 0}, {0, cos(rad), -sin(rad), 0}, {0, sin(rad), cos(rad), 0}, {0, 0, 0, 1}};
	Vec4MultMatrix4(multMe, matrix);
	c.pos.x = multMe[0];
	c.pos.y = multMe[1];
	c.pos.z = multMe[2];
	c.pos.w = multMe[3];
}

inline VERTEX RotateY(VERTEX& c, float rad)
{
	rad = rad * (M_PI / 180);
	float multMe[4] = {c.pos.x, c.pos.y, c.pos.z, c.pos.w};
	float matrix[4][4] = {{cos(rad), 0, -sin(rad), 0}, {0, 1, 0, 0}, {sin(rad), 0, cos(rad), 0}, {0, 0, 0, 1}};
	Vec4MultMatrix4(multMe, matrix);
	c.pos.x = multMe[0];
	c.pos.y = multMe[1];
	c.pos.z = multMe[2];
	return c;
}

inline MATRIX Mult4x4(MATRIX& a, MATRIX& b)
{
	MATRIX temp = a;
	temp.x[0] = a.x[0] * b.x[0] + a.x[1] * b.y[0] + a.x[2] * b.z[0] + a.x[3] * b.w[0];
	temp.y[0] = a.y[0] * b.x[0] + a.y[1] * b.y[0] + a.y[2] * b.z[0] + a.y[3] * b.w[0];
	temp.z[0] = a.z[0] * b.x[0] + a.z[1] * b.y[0] + a.z[2] * b.z[0] + a.z[3] * b.w[0];
	temp.w[0] = a.w[0] * b.x[0] + a.w[1] * b.y[0] + a.w[2] * b.z[0] + a.w[3] * b.w[0];
	temp.x[1] = a.x[0] * b.x[1] + a.x[1] * b.y[1] + a.x[2] * b.z[1] + a.x[3] * b.w[1];
	temp.y[1] = a.y[0] * b.x[1] + a.y[1] * b.y[1] + a.y[2] * b.z[1] + a.y[3] * b.w[1];
	temp.z[1] = a.z[0] * b.x[1] + a.z[1] * b.y[1] + a.z[2] * b.z[1] + a.z[3] * b.w[1];
	temp.w[1] = a.w[0] * b.x[1] + a.w[1] * b.y[1] + a.w[2] * b.z[1] + a.w[3] * b.w[1];
	temp.x[2] = a.x[0] * b.x[2] + a.x[1] * b.y[2] + a.x[2] * b.z[2] + a.x[3] * b.w[2];
	temp.y[2] = a.y[0] * b.x[2] + a.y[1] * b.y[2] + a.y[2] * b.z[2] + a.y[3] * b.w[2];
	temp.z[2] = a.z[0] * b.x[2] + a.z[1] * b.y[2] + a.z[2] * b.z[2] + a.z[3] * b.w[2];
	temp.w[2] = a.w[0] * b.x[2] + a.w[1] * b.y[2] + a.w[2] * b.z[2] + a.w[3] * b.w[2];
	temp.x[3] = a.x[0] * b.x[3] + a.x[1] * b.y[3] + a.x[2] * b.z[3] + a.x[3] * b.w[3];
	temp.y[3] = a.y[0] * b.x[3] + a.y[1] * b.y[3] + a.y[2] * b.z[3] + a.y[3] * b.w[3];
	temp.z[3] = a.z[0] * b.x[3] + a.z[1] * b.y[3] + a.z[2] * b.z[3] + a.z[3] * b.w[3];
	temp.w[3] = a.w[0] * b.x[3] + a.w[1] * b.y[3] + a.w[2] * b.z[3] + a.w[3] * b.w[3];
	
	return temp;
}

inline MATRIX Mult4x4notRef(MATRIX a, MATRIX b)
{
	MATRIX temp = a;
	temp.x[0] = a.x[0] * b.x[0] + a.x[1] * b.y[0] + a.x[2] * b.z[0] + a.x[3] * b.w[0];
	temp.y[0] = a.y[0] * b.x[0] + a.y[1] * b.y[0] + a.y[2] * b.z[0] + a.y[3] * b.w[0];
	temp.z[0] = a.z[0] * b.x[0] + a.z[1] * b.y[0] + a.z[2] * b.z[0] + a.z[3] * b.w[0];
	temp.w[0] = a.w[0] * b.x[0] + a.w[1] * b.y[0] + a.w[2] * b.z[0] + a.w[3] * b.w[0];
	temp.x[1] = a.x[0] * b.x[1] + a.x[1] * b.y[1] + a.x[2] * b.z[1] + a.x[3] * b.w[1];
	temp.y[1] = a.y[0] * b.x[1] + a.y[1] * b.y[1] + a.y[2] * b.z[1] + a.y[3] * b.w[1];
	temp.z[1] = a.z[0] * b.x[1] + a.z[1] * b.y[1] + a.z[2] * b.z[1] + a.z[3] * b.w[1];
	temp.w[1] = a.w[0] * b.x[1] + a.w[1] * b.y[1] + a.w[2] * b.z[1] + a.w[3] * b.w[1];
	temp.x[2] = a.x[0] * b.x[2] + a.x[1] * b.y[2] + a.x[2] * b.z[2] + a.x[3] * b.w[2];
	temp.y[2] = a.y[0] * b.x[2] + a.y[1] * b.y[2] + a.y[2] * b.z[2] + a.y[3] * b.w[2];
	temp.z[2] = a.z[0] * b.x[2] + a.z[1] * b.y[2] + a.z[2] * b.z[2] + a.z[3] * b.w[2];
	temp.w[2] = a.w[0] * b.x[2] + a.w[1] * b.y[2] + a.w[2] * b.z[2] + a.w[3] * b.w[2];
	temp.x[3] = a.x[0] * b.x[3] + a.x[1] * b.y[3] + a.x[2] * b.z[3] + a.x[3] * b.w[3];
	temp.y[3] = a.y[0] * b.x[3] + a.y[1] * b.y[3] + a.y[2] * b.z[3] + a.y[3] * b.w[3];
	temp.z[3] = a.z[0] * b.x[3] + a.z[1] * b.y[3] + a.z[2] * b.z[3] + a.z[3] * b.w[3];
	temp.w[3] = a.w[0] * b.x[3] + a.w[1] * b.y[3] + a.w[2] * b.z[3] + a.w[3] * b.w[3];

	return temp;
}
//MATRIX InverseMatrix(MATRIX& a)
//{
//	float det = a.x[0] * (a.y[1] * a.z[2] - a.z[1] * a.y[2]) - a.x[1] * (a.y[0] * a.z[2] - a.y[2] * a.z[0]) + a.x[2] * (a.y[0] * a.z[1] - a.y[2] * a.z[0]);
//	det = 1 / det;
//	MATRIX t;
//	t.x[0] = (a.y[1] * a.z[2] * a.w[3]) + (a.y[2] * a.z[3] * a.w[1]) + (a.y[3] * a.z[1] * a.w[2]) - (a.y[3] * a.z[2] * a.w[1]) - (a.y[2] * a.z[1] * a.w[3]) - (a.y[1] * a.z[3] * a.w[2]);
//	t.x[1] = (a.y[0] * a.z[2] * a.w[3]) + (a.y[2] * a.z[3] * a.w[0]) + (a.y[3] * a.z[0] * a.w[2]) - (a.y[3] * a.z[2] * a.w[0]) - (a.y[2] * a.z[0] * a.w[3]) - (a.y[0] * a.z[3] * a.w[2]);
//	t.x[2] = (a.y[0] * a.z[1] * a.w[3]) + (a.y[1] * a.z[3] * a.w[0]) + (a.y[3] * a.z[0] * a.w[1]) - (a.y[3] * a.z[1] * a.w[0]) - (a.y[1] * a.z[0] * a.w[3]) - (a.y[0] * a.z[3] * a.w[1]);
//	t.x[3] = (a.y[0] * a.z[1] * a.w[2]) + (a.y[1] * a.z[2] * a.w[0]) + (a.y[2] * a.z[0] * a.w[1]) - (a.y[2] * a.z[1] * a.w[0]) - (a.y[1] * a.z[0] * a.w[2]) - (a.y[0] * a.z[2] * a.w[1]);
//	t.y[0] = (a.x[1] * a.z[2] * a.w[3]) + (a.x[2] * a.z[3] * a.w[1]) + (a.x[3] * a.z[1] * a.w[2]) - (a.x[3] * a.z[2] * a.w[1]) - (a.x[2] * a.z[1] * a.w[3]) - (a.x[1] * a.z[3] * a.w[2]);
//	t.y[1] = (a.x[0] * a.z[2] * a.w[3]) + (a.x[2] * a.z[3] * a.w[0]) + (a.x[3] * a.z[0] * a.w[2]) - (a.x[3] * a.z[2] * a.w[0]) - (a.x[2] * a.z[0] * a.w[3]) - (a.x[0] * a.z[3] * a.w[2]);
//	t.y[2] = (a.x[0] * a.z[1] * a.w[3]) + (a.x[1] * a.z[3] * a.w[0]) + (a.x[3] * a.z[0] * a.w[1]) - (a.x[3] * a.z[1] * a.w[0]) - (a.x[1] * a.z[0] * a.w[3]) - (a.x[0] * a.z[3] * a.w[1]);
//	t.y[3] = (a.x[0] * a.z[1] * a.w[2]) + (a.x[1] * a.z[2] * a.w[0]) + (a.x[2] * a.z[0] * a.w[1]) - (a.x[2] * a.z[1] * a.w[0]) - (a.x[1] * a.z[0] * a.w[2]) - (a.x[0] * a.z[2] * a.w[1]);
//	t.z[0] = (a.x[1] * a.y[2] * a.w[3]) + (a.x[2] * a.y[3] * a.w[1]) + (a.x[3] * a.y[1] * a.w[2]) - (a.x[3] * a.y[2] * a.w[1]) - (a.x[2] * a.y[1] * a.w[3]) - (a.x[1] * a.y[3] * a.w[2]);
//	t.z[1] = (a.x[0] * a.y[2] * a.w[3]) + (a.x[2] * a.y[3] * a.w[0]) + (a.x[3] * a.y[0] * a.w[2]) - (a.x[3] * a.y[2] * a.w[0]) - (a.x[2] * a.y[0] * a.w[3]) - (a.x[0] * a.y[3] * a.w[2]);
//	t.z[2] = (a.x[0] * a.y[1] * a.w[3]) + (a.x[1] * a.y[3] * a.w[0]) + (a.x[3] * a.y[0] * a.w[1]) - (a.x[3] * a.y[1] * a.w[0]) - (a.x[1] * a.y[0] * a.w[3]) - (a.x[0] * a.y[3] * a.w[1]);
//	t.z[3] = (a.x[0] * a.y[1] * a.w[2]) + (a.x[1] * a.y[2] * a.w[0]) + (a.x[2] * a.y[0] * a.w[1]) - (a.x[2] * a.y[1] * a.w[0]) - (a.x[1] * a.y[0] * a.w[2]) - (a.x[0] * a.y[2] * a.w[1]);
//	t.w[0] = (a.x[1] * a.y[2] * a.z[3]) + (a.x[2] * a.y[3] * a.z[1]) + (a.x[3] * a.y[1] * a.z[2]) - (a.x[3] * a.y[2] * a.z[1]) - (a.x[2] * a.y[1] * a.z[3]) - (a.x[1] * a.y[3] * a.z[2]);
//	t.w[1] = (a.x[0] * a.y[2] * a.z[3]) + (a.x[2] * a.y[3] * a.z[0]) + (a.x[3] * a.y[0] * a.z[2]) - (a.x[3] * a.y[2] * a.z[0]) - (a.x[2] * a.y[0] * a.z[3]) - (a.x[0] * a.y[3] * a.z[2]);
//	t.w[2] = (a.x[0] * a.y[1] * a.z[3]) + (a.x[1] * a.y[3] * a.z[0]) + (a.x[3] * a.y[0] * a.z[1]) - (a.x[3] * a.y[1] * a.z[0]) - (a.x[1] * a.y[0] * a.z[3]) - (a.x[0] * a.y[3] * a.z[1]);
//	t.w[3] = (a.x[0] * a.y[1] * a.z[2]) + (a.x[1] * a.y[2] * a.z[0]) + (a.x[2] * a.y[0] * a.z[1]) - (a.x[2] * a.y[1] * a.z[0]) - (a.x[1] * a.y[0] * a.z[2]) - (a.x[0] * a.y[2] * a.z[1]);
//	return t;
//}

inline MATRIX InverseMatrix(MATRIX& a)
{
	MATRIX temp = a;
	a.y[0] = temp.x[1];
	a.x[1] = temp.y[0];
	a.z[0] = temp.x[2];
	a.x[2] = temp.z[0];
	a.z[1] = temp.y[2];
	a.y[2] = temp.z[1];
	VERTEX tV;
	tV.pos.x = a.w[0];
	tV.pos.y = a.w[1];
	tV.pos.z = a.w[2];
	tV.pos.w = a.w[3];
	tV = VertexMultMatrix(tV, a);
	a.w[0] -= tV.pos.x;
	a.w[1] -= tV.pos.y;
	a.w[2] -= tV.pos.z;
	//a.w[3] -= tV.pos.w;
	return a;
}

inline float DotProduct(VERTEX a, VERTEX b)
{
	float p = 0;
	p = p + (a.nrml.i * b.nrml.i);
	p = p + (a.nrml.j * b.nrml.j);
	p = p + (a.nrml.k * b.nrml.k);
	return p;
}

inline VERTEX CrossProduct(VERTEX a, VERTEX b)
{
	VERTEX r = a;
	r.pos.x = (a.pos.y * b.pos.z) - (a.pos.z * b.pos.x);
	r.pos.y = (a.pos.z * b.pos.x) - (a.pos.x * b.pos.z);
	r.pos.z = (a.pos.x * b.pos.y) - (a.pos.y * b.pos.x);
	return r;
}

inline float VectorLength(VERTEX a)
{
	//The length of the vector is square root of (x*x+y*y+z*z)
	float vecLenght = sqrtf((a.pos.x * a.pos.x) + (a.pos.y * a.pos.y) + (a.pos.z * a.pos.z));
	return vecLenght;
}

inline VERTEX Normalize(VERTEX a)
{
	VERTEX r = a;
	r.pos.x = a.pos.x / VectorLength(a);
	r.pos.y = a.pos.y / VectorLength(a);
	r.pos.z = a.pos.z / VectorLength(a);
	return r;
}

inline unsigned int CombineColors(unsigned int a, unsigned int b)
{
	auto b1 = (a & 0x000000FF);
	auto g1 = (a & 0x0000FF00) >> 8;
	auto r1 = (a & 0x00FF0000) >> 16;
	auto a1 = (a & 0xFF000000) >> 24;


	auto b2 = (b & 0x000000FF);
	auto g2 = (b & 0x0000FF00) >> 8;
	auto r2 = (b & 0x00FF0000) >> 16;
	auto a2 = (b & 0xFF000000) >> 24;
	if((a1 + a2) > 255)
	{
		a1 = 255;
		a2 = 0;
	}
	if ((b1 + b2) > 255)
	{
		b1 = 255;
		b2 = 0;
	}
	if ((g1 + g2) > 255)
	{
		g1 = 255;
		g2 = 0;
	}
	if ((r1 + r2) > 255)
	{
		r1 = 255;
		r2 = 0;
	}
	unsigned int r = (((a1 + a2) << 24) | ((r1 + r2) << 16) | ((g1 + g2) << 8) | ((b1 + b2)));
	return r;
}

inline unsigned int ModulateColors(unsigned int a, unsigned int b)
{
	unsigned int b1 = (a & 0x000000FF);
	float b1c = static_cast<float>(b1) / 255;
	auto g1 = (a & 0x0000FF00) >> 8;
	float g1c = static_cast<float>(g1) / 255;
	auto r1 = (a & 0x00FF0000) >> 16;
	float r1c = static_cast<float>(r1) / 255;
	auto a1 = (a & 0xFF000000) >> 24;
	float a1c = static_cast<float>(a1) / 255;

	unsigned int b2 = (b & 0x000000FF);
	float b2c = static_cast<float>(b2) / 255;
	auto g2 = (b & 0x0000FF00) >> 8;
	float g2c = static_cast<float>(g2) / 255;
	auto r2 = (b & 0x00FF0000) >> 16;
	float r2c = static_cast<float>(r2) / 255;
	auto a2 = (b & 0xFF000000) >> 24;
	float a2c = static_cast<float>(a2) / 255;
	b1c = b1c * b2c;
	g1c = g1c * g2c;
	r1c = r1c * r2c;
	a1c = a1c * a2c;
	b1c *= 255;
	b1 = b1c;
	g1c *= 255;
	g1 = g1c;
	r1c *= 255;
	r1 = r1c;
	a1c *= 255;
	a1 = a1c;
	unsigned int r = (((a1) << 24) | ((r1) << 16) | ((g1) << 8) | ((b1)));
	return r;
}

inline float Clamp(float a)
{
	if (a > 1) return 1;
	if (a < 0) return 0;
	return a;
}

inline unsigned int LerpTheColors(unsigned int a, unsigned int b, unsigned int c, VERTEX barry)
{
	unsigned int b1 = (a & 0x000000FF);
	auto g1 = (a & 0x0000FF00) >> 8;
	auto r1 = (a & 0x00FF0000) >> 16;
	auto a1 = (a & 0xFF000000) >> 24;


	unsigned int b2 = (b & 0x000000FF);
	auto g2 = (b & 0x0000FF00) >> 8;
	auto r2 = (b & 0x00FF0000) >> 16;
	auto a2 = (b & 0xFF000000) >> 24;

	unsigned int b3 = (c & 0x000000FF);
	auto g3 = (c & 0x0000FF00) >> 8;
	auto r3 = (c & 0x00FF0000) >> 16;
	auto a3 = (c & 0xFF000000) >> 24;

	unsigned int aR = (a1 * barry.pos.x) + (a2 * barry.pos.y) + (a3 * barry.pos.z);
	unsigned int rR = (r1 * barry.pos.x) + (r2 * barry.pos.y) + (r3 * barry.pos.z);
	unsigned int gR = (g1 * barry.pos.x) + (g2 * barry.pos.y) + (g3 * barry.pos.z);
	unsigned int bR = (b1 * barry.pos.x) + (b2 * barry.pos.y) + (b3 * barry.pos.z);
	unsigned r = (((aR) << 24) | ((rR) << 16) | ((gR) << 8) | ((bR)));
	return r;
}

inline unsigned int Lerp(unsigned int a, unsigned int b, float ratio)
{
	auto a1 = (a & 0xFF000000) >> 24;
	auto r1 = (a & 0x00FF0000) >> 16;
	auto g1 = (a & 0x0000FF00) >> 8;
	auto b1 = (a & 0x000000FF);
	auto a2 = (b & 0xFF000000) >> 24;
	auto r2 = (b & 0x00FF0000) >> 16;
	auto g2 = (b & 0x0000FF00) >> 8;
	auto b2 = (b & 0x000000FF);
	unsigned int aL = LERP(a1, a2, ratio);
	unsigned int rL = LERP(r1, r2, ratio);
	unsigned int gL = LERP(g1, g2, ratio);
	unsigned int bL = LERP(b1, b2, ratio);
	unsigned int r = (((aL) << 24) | ((rL) << 16) | ((gL) << 8) | ((bL)));
	return r;
}

inline VERTEX subtractVertex(VERTEX a, VERTEX b)
{
	VERTEX r = a;
	r.pos.x = a.pos.x - b.pos.x;
	r.pos.y = a.pos.y - b.pos.y;
	r.pos.z = a.pos.z - b.pos.z;
	return r;
}
///Converts VERTEX from -1 to +1 values to pixel coordinates
inline VERTEX CartesianConversion(VERTEX& convert)
{
	//change the convert variable that come is, pass by pointer or reference
	float convertX = convert.pos.x;
	float convertY = convert.pos.y;
	convertX = (convertX + 1) * (WIDTH / 2);
	convertY -= (convertY + convertY);
	convertY = (convertY + 1) * (HEIGHT / 2);

	convert.pos.x = convertX;
	convert.pos.y = convertY;
	return convert;
}