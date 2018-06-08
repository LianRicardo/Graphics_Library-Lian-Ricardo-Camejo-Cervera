#include "Canvas.h"
#include "Color.h"
using namespace colores;

void Canvas::PutPixel(int x, int y, Color c)
{
	pixelarray[SCREEN_WIDTH*y + x] = c;
}
Color Canvas::GetPixel(int x, int y)
{
	return pixelarray[SCREEN_WIDTH*y + x];
}
void Canvas::Bitblt(Canvas* pSrc, int x, int y, int x0, int y0, int xf, int yf, Color key)
{
	//char * plocScr[4] = pSrc*((y*pitch) + x);
	int imagenx = xf - x0;
	int imageny = yf - y0;
	Color colorscr;
	if (imagenx == 0 && imageny == 0)
	{
		int image_width = pSrc->GetWidth();
		int image_height = pSrc->GetHeigth();
		for (int k = 0; k < image_height; k++)
		{
			for (int l = 0; l < image_width; l++)
			{
				colorscr = pSrc->GetPixel(l, k);
				if (colorscr.GetRed() == key.GetRed() && colorscr.GetBlue() == key.GetBlue() && colorscr.GetGreen() == key.GetGreen())
				{
					continue;
				}
				this->PutPixel(x + l, y + k, colorscr);

			}
		}
	}
	else
	{
		for (int j = 0; j < imageny; j++)
		{
			for (int i = 0; i < imagenx; i++)
			{
				colorscr = pSrc->GetPixel(i, j);
				if (colorscr.GetRed() == key.GetRed() && colorscr.GetBlue() == key.GetBlue() && colorscr.GetGreen() == key.GetGreen())
				{
					continue;
				}
				this->PutPixel(x0 + i, y0 + j, colorscr);
			}
		}
	}
}
void Canvas::Drawline(int x1, int y1, int x2, int y2, Color c)
{
	float error, m;
	int x, y;
	x = x1;
	y = y1;
	if (x1 == x2)
	{
		while (y != y2)
		{
			if (y2 - y1>0)
				++y;
			else
				--y;
			PutPixel(x, y, c);
		}
	}
	else
	{
		m = (float)(y2 - y1) / (x2 - x1);
		error = 0;
		PutPixel(x, y, c);
		while (x != x2)
		{
			error += m;
			if (error>.5)
			{
				if (x2 - x1>0)
					y += 1;
				else
					y -= 1;
				--error;
			}
			if (x2 - x1>0)
				++x;
			else
				--x;
			PutPixel(x, y, c);
		}
	}
}
void Canvas::DrawCircle(int x, int y, int centerx, int centery, int r, Color c)
{
	int P_area = 2 - 2 * r;
	int error = 0;
	x = 0;
	y = r;
	while (y >= 0)
	{
		PutPixel(centerx + x, centery + y, c);
		PutPixel(centerx - x, centery + y, c);
		PutPixel(centerx + x, centery - y, c);
		PutPixel(centerx - x, centery - y, c);
		error = 2 * (P_area + y) - 1;
		if (P_area < 0 && error <= 0)
		{
			++x;
			P_area += 2 * x + 1;
			continue;
		}
		error = 2 * (P_area - x) - 1;
		if (P_area > 0 && error > 0)
		{
			--y;
			P_area += 1 - 2 * y;
			continue;
		}
		++x;
		P_area += 2 * (x - y);
		--y;
	}
}

void Canvas::Drawrect(int x, int y, int width, int height, Color c)
{
	Drawline(x, y, x + width, y, c);
	Drawline(x + width, y, x + width, y - height, c);
	Drawline(x + width, y - height, x, y - height, c);
	Drawline(x, y -height, x, y, c);
}

void Canvas::DrawElipse(int xcenter, int ycenter, int height, int width, Color c)
{
	int A = width * width;
	int B = height * height;
	int focoa = 4 * A, 
	int focob = 4 * B;
	int x, y, error;
	for (x = 0, y = height, error = 2 * B + A*(1 - 2 * height); B*x <= A*y; x++)
	{
		PutPixel(xcenter + x, ycenter + y, c);
		PutPixel(xcenter - x, ycenter + y, c);
		PutPixel(xcenter + x, ycenter - y, c);
		PutPixel(xcenter - x, ycenter - y, c);
		if (error >= 0)
		{
			error += focoa * (1 - y);
			y--;
		}
		error += B * ((4 * x) + 6);
	}
	for (x = width, y = 0, error = 2 * A + B*(1 - 2 * width); A*y <= B*x; y++)
	{
		PutPixel(xcenter + x, ycenter + y, c);
		PutPixel(xcenter - x, ycenter + y, c);
		PutPixel(xcenter + x, ycenter - y, c);
		PutPixel(xcenter - x, ycenter - y, c);
		if (error >= 0)
		{
			error += focob * (1 - x);
			x--;
		}
		error += A * ((4 * y) + 6);
	}
}
