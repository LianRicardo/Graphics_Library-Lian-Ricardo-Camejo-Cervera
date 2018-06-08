#pragma once
#include "Color.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGTH 600
#define BITES_PER_PIXEL 4
class Canvas
{
public:
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y);
	void Drawline(int x1, int y1, int x2, int y2, Color c);
	void Bitblt(Canvas* pSrc, int x, int y, int x0, int y0, int xf, int yf, Color key);
	void DrawCircle(int x, int y, int centerx, int centery, int r, Color c);
	void Drawrect(int x, int y, int w, int h, Color c);
	void DrawElipse(int xcenter, int ycenter, int height, int width, Color c);
	int GetWidth()
	{
		return SCREEN_WIDTH;
	}
	int GetHeigth()
	{
		return SCREEN_HEIGTH;
	}
private:
	Color* pixelarray = nullptr;
	float pitch = BITES_PER_PIXEL*SCREEN_WIDTH;
};

