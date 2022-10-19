#pragma once
#include "Math.h"


void (*VertexShader)(VERTEX&) = nullptr;
void (*PixelShader)(unsigned int&) = nullptr;

MATRIX World = iD;
MATRIX Camera = Mult4x4(tL, rotateByX);
MATRIX ViewMatrix = InverseMatrix(Camera);

void VS_3D(VERTEX& v)
{
	v = VertexMultMatrix(v, World);

	DirectionalLight.nrml.i = 0.577f;
	DirectionalLight.nrml.j = 0.577f;
	DirectionalLight.nrml.k = -0.577f;
	DirectionalLight.color = 0xFFC0C0F0;
	float lightRatio = Clamp(DotProduct(DirectionalLight, v));
	DirectionalLight.color = Lerp(0xFF000000, DirectionalLight.color, lightRatio);

	PointLight.pos.x = -1.0f;
	PointLight.pos.y = 0.5f;
	PointLight.pos.z = 1.0f;
	PointLight.color = 0xFFFFFF00;
	VERTEX pointDirection = Normalize(subtractVertex(PointLight, v));
	pointDirection.nrml.i = pointDirection.pos.x;
	pointDirection.nrml.j = pointDirection.pos.y;
	pointDirection.nrml.k = pointDirection.pos.z;
	float attenuation = 1 - Clamp(VectorLength(subtractVertex(PointLight, v)) / lightRadius);
	float pointRatio = Clamp((DotProduct(pointDirection, v)));
	pointRatio *= attenuation;
	pointDirection.color = CombineColors(pointDirection.color, DirectionalLight.color);
	v.color = Lerp(DirectionalLight.color, pointDirection.color, pointRatio);

	v = VertexMultMatrix(v, ViewMatrix);
	v = VertexMultMatrix(v, projection);
	v.pos.x /= v.pos.w;
	v.pos.y /= v.pos.w;
	v.pos.z /= v.pos.w;
	
}