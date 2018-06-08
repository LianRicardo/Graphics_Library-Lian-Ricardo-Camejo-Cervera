#pragma once

class Color
{
public:
	unsigned int Key;
	constexpr Color() : Key() {}
	constexpr Color(const Color& col)
		:
		Key(col.Key)
	{}
	constexpr Color(unsigned int dw)
		:
		Key(dw)
	{}
	constexpr Color(unsigned char x, unsigned char r, unsigned char g, unsigned char b)
		:
		Key((x << 24u) | (r << 16u) | (g << 8u) | b)
	{}
	constexpr Color(unsigned char r, unsigned char g, unsigned char b)
		:
		Key((r << 16u) | (g << 8u) | b)
	{}
	constexpr Color(Color col, unsigned char x)
		:
		Color((x << 24u) | col.Key)
	{}
	Color& operator =(Color color)
	{
		Key = color.Key;
		return *this;
	}
	/*Color& operator ==(Color c)
	{
		Key == c.Key;
		return *this;
	}*/
	constexpr unsigned char GetAlpha() const
	{
		return Key >> 24u;
	}
	constexpr unsigned char GetRed() const
	{
		return (Key >> 16u) & 0xFFu;
	}
	constexpr unsigned char GetGreen() const
	{
		return (Key >> 8u) & 0xFFu;
	}
	constexpr unsigned char GetBlue() const
	{
		return Key & 0xFFu;
	}
	void SetAlpha(unsigned char x)
	{
		Key = (Key & 0xFFFFFFu) | (x << 24u);
	}
	void SetRed(unsigned char r)
	{
		Key = (Key & 0xFF00FFFFu) | (r << 16u);
	}
	void SetGreen(unsigned char g)
	{
		Key = (Key & 0xFFFF00FFu) | (g << 8u);
	}
	void SetBlue(unsigned char b)
	{
		Key = (Key & 0xFFFFFF00u) | b;
	}
};

namespace colores
{
	static constexpr Color MakeColor(unsigned char r, unsigned char g, unsigned char b)
	{
		return (r << 16) | (g << 8) | b;
	}
	static constexpr Color White = MakeColor(255u, 255u, 255u);
	static constexpr Color Black = MakeColor(0u, 0u, 0u);
	static constexpr Color Gray = MakeColor(0x80u, 0x80u, 0x80u);
	static constexpr Color LightGray = MakeColor(0xD3u, 0xD3u, 0xD3u);
	static constexpr Color Red = MakeColor(255u, 0u, 0u);
	static constexpr Color Green = MakeColor(0u, 255u, 0u);
	static constexpr Color Blue = MakeColor(0u, 0u, 255u);
	static constexpr Color Yellow = MakeColor(255u, 255u, 0u);
	static constexpr Color Cyan = MakeColor(0u, 255u, 255u);
	static constexpr Color Magenta = MakeColor(255u, 0u, 255u);
}
