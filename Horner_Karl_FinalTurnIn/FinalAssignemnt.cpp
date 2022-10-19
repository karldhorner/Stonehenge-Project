// FinalAssignemnt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>

#include "DrawFunctions.h"
#include "RasterSurface.h"

//Global Stuffs
VERTEX stars[3000];
float starMin = -1;
float starMax = 1;
float RandomThing();
float change = the;
float changeOther = theOther;
int resetRadius = 0;

int main()
{
    srand(time(nullptr));
    //StoneHenge Stuffs
    VERTEX hengeVertex[1457];
    for (int i = 0; i < 1457; ++i)
    {
        hengeVertex[i].pos.x = StoneHenge_data[i].pos[0] * 0.1f;
        hengeVertex[i].pos.y = StoneHenge_data[i].pos[1] * 0.1f;
        hengeVertex[i].pos.z = StoneHenge_data[i].pos[2] * 0.1f;
        hengeVertex[i].pos.w = 1.0f;
        hengeVertex[i].uv.u = StoneHenge_data[i].uvw[0];
        hengeVertex[i].uv.v = StoneHenge_data[i].uvw[1];
        hengeVertex[i].nrml.i = StoneHenge_data[i].nrm[0];
        hengeVertex[i].nrml.j = StoneHenge_data[i].nrm[1];
        hengeVertex[i].nrml.k = StoneHenge_data[i].nrm[2];

    }
    //Build the stars
    for (int i = 0; i < 3000; ++i)
    {
        stars[i].pos.x = (RandomThing() * 50.0f);
        stars[i].pos.y = (RandomThing() * 50.0f);
        stars[i].pos.z = (RandomThing() * 50.0f);
        stars[i].pos.w = 1.0f;
    }

    RS_Initialize("Karl Horner", WIDTH, HEIGHT);

    while (true)
    {
        RS_Update(pixels, TOTAL_PIXELS);

        VertexShader = VS_3D;
        World = iD;
        //Camera rotation stuffs
    	MATRIX rotX = {{1,0,0,0},{0,cos(the),-sin(the),0},{0,sin(the),cos(the),0},{0,0,0,1}};
    	MATRIX rotY = {{cos(theOther), 0, -sin(theOther), 0}, {0, 1, 0, 0}, {sin(theOther), 0, cos(theOther), 0}, {0, 0, 0, 1}};
    	World = Mult4x4(rotX, rotY);
        // Clear buffer to sky
        for (int i = 0; i < TOTAL_PIXELS; ++i)
        {
            pixels[i] = 0xFF172a44;
            zBuffer[i] = 5.0f;
        }
        // Draw stars
        for (int i = 0; i < 3000; ++i)
        {
            VERTEX copy = stars[i];
            if (VertexShader) VS_3D(copy);
        	CartesianConversion(copy);
            if(copy.pos.x >= 0 && copy.pos.x <= WIDTH && copy.pos.y >= 0 && copy.pos.y <= HEIGHT) PlotAPixel(copy.pos.x , copy.pos.y, copy.pos.z, 0xFFfbff14);
        }
        // Draw Stonehenge
        for (int i = 0; i < 2532;)
        {
            int two = i + 1;
            int three = i + 2;
            fillTriangle(hengeVertex[StoneHenge_indicies[i]], hengeVertex[StoneHenge_indicies[two]], hengeVertex[StoneHenge_indicies[three]], hengeVertex[StoneHenge_indicies[i]]);
            i += 3;
        }
        if(lightRadius <= 10.0f && resetRadius == 0)
        {
            lightRadius += 0.1f;
            if (lightRadius >= 10.0f) resetRadius = 1;
        }
        if(lightRadius > 1 && resetRadius ==1)
        {
            lightRadius -= 0.1f;
            if (lightRadius <= 1) resetRadius = 0;
        }

#pragma region Key Controls
        if (GetAsyncKeyState(0x28)) the -= 0.01f;   // Up
        if (GetAsyncKeyState(0x26)) the += 0.01f;   // Down
        if (GetAsyncKeyState(0x25)) theOther -= 0.01f;   // Left
        if (GetAsyncKeyState(0x27)) theOther += 0.01f;   // Right
#pragma endregion

    }

    RS_Shutdown();
}
/// <summary>
/// Make a random float based on starMax and starMin
/// </summary>
/// <returns>float</returns>
float RandomThing()
{
    return starMin + ((rand() / static_cast<float>(RAND_MAX)) * (starMax - starMin));
}
