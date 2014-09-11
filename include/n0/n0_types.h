#ifndef __FW_TYPES_H__
#define __FW_TYPES_H__
	// TYPES
	// base types are borrowed from the Irrlicht Engine (irrTypes.h)
	// Copyright (C) 2002-2012 Nikolaus Gebhardt
#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
	typedef __int8 s8;
	typedef unsigned __int8 u8;
	typedef __int16 s16;
	typedef unsigned __int16 u16;
	typedef __int32 s32;
	typedef unsigned __int32 u32;
#else
	typedef signed char s8;
	typedef unsigned char u8;
	typedef signed short s16;
	typedef unsigned short u16;
	typedef signed int s32;
	typedef unsigned int u32;
#endif

	typedef unsigned char byte;

#if defined(_MSC_VER) || ((__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__))
	typedef __int64 s64;
	typedef unsigned __int64 u64;
#elif __GNUC__
#	if __WORDSIZE == 64
	typedef long int s64;
	typedef unsigned long int u64;
#	else
	__extension__ typedef long long s64;
	__extension__ typedef unsigned long long u64;
#	endif
#else
	typedef long long s64;
	typedef unsigned long long u64;
#endif

	typedef float f32;
	typedef double f64;



namespace n0
{
	//VEC2
	

	

	// ANCHOR
	class Anchor
	{
	public:
		// DON'T USE THE BASE ANCHORS FOR POSITIONING
		static const u8 TOP         = (1 << 0);
		static const u8 VCENTER     = (1 << 1);
		static const u8 BOTTOM      = (1 << 2);
		static const u8 LEFT        = (1 << 3);
		static const u8 HCENTER     = (1 << 4);
		static const u8 RIGHT       = (1 << 5);
		// USE THESE FANCILY NAMED ONES INSTEAD
		static const u8 TOPLEFT     = TOP | LEFT;
		static const u8 TOPCENTER   = TOP | HCENTER;
		static const u8 TOPRIGHT    = TOP | RIGHT;
		static const u8 BOTTOMLEFT  = BOTTOM | LEFT;
		static const u8 BOTTOMCENTER= BOTTOM | HCENTER;
		static const u8 BOTTOMRIGHT = BOTTOM | RIGHT;
		static const u8 CENTERLEFT  = VCENTER | LEFT;
		static const u8 CENTERCENTER= VCENTER | HCENTER;
		static const u8 CENTERRIGHT = VCENTER | RIGHT;
	};

	// COLOUR (RGBA)
	class Colour
	{
	protected:
		u32 colour;
		char retbuf[16];

	public:
		Colour() : colour(0) { }
		Colour(const Colour & other) : colour(other.colour) { }
		Colour(const u32 colour) { Set(colour); }
		Colour(const u8 r, const u8 g, const u8 b, const u8 a) { Set(r, g, b, a); }
		bool operator==(const Colour& other) const { return colour == other.colour; }
		bool operator!=(const Colour& other) const { return colour != other.colour; }
		Colour operator+(const Colour& other) const;

		void Set(const u32 c) { colour = c; }
		void Set(const u8 r, const u8 g, const u8 b, const u8 a) { colour = (((r & 0xff)<<24) | ((g & 0xff)<<16) | ((b & 0xff)<<8) | (a & 0xff)); }

		u8 GetRed() const { return colour >> 24; }
		void SetRed(const u8 r) { colour = ((r & 0xff)<<24) | (colour & 0x00ffffff); }
		u8 GetGreen() const { return (colour >> 16) & 0xff; }
		void SetGreen(const u8 g) { colour = ((g & 0xff)<<16) | (colour & 0xff00ffff); }
		u8 GetBlue() const { return (colour >> 8) & 0xff; }
		void SetBlue(const u8 b) { colour = ((b & 0xff)<<8) | (colour & 0xffff00ff); }
		u8 GetAlpha() const { return colour & 0xff; }
		void SetAlpha(const u8 a) { colour = (a & 0xff) | (colour & 0xffffff00); }

		u32 GetValue() const { return colour; }
		char * GetHex();
		u32 GetAverage() const { return (GetRed() + GetGreen() + GetBlue()) / 3; }

		Colour GetInterpolated(const Colour & other, f32 d) const
		{
			d = d < 0.0f ? 0.0f : (d > 1.0f ? 1.0f : d); // clamp
			const f32 inv = 1.0f - d;
			return Colour((u8)(other.GetRed() * inv + GetRed() * d),
				(u8)(other.GetGreen() * inv + GetGreen() * d),
				(u8)(other.GetBlue() * inv + GetBlue() * d),
				(u8)(other.GetAlpha() * inv + GetAlpha() * d));
		}
	};

	// COLOUR (RGBA floats) 
	class Colour4f
	{
	private:
		f32 r;
		f32 g;
		f32 b;
		f32 a;

	public:
		Colour4f() { Set(0.0f, 0.0f, 0.0f, 0.0f); }
		Colour4f(const f32 r, const f32 g, const f32 b, const f32 a) { Set(r, g, b, a); }
		Colour4f(const Colour4f & other) { Set(other); }
		Colour4f(const u32 colour) { Set(Colour(colour)); }
		Colour4f(const Colour & other) { Set(other); }

		void Set(const f32 r, const f32 g, const f32 b, const f32 a)
		{
			// clamp all the things!
			this->r = r < 0.0f ? 0.0f : (r > 1.0f ? 1.0f : r);
			this->g = g < 0.0f ? 0.0f : (g > 1.0f ? 1.0f : g);
			this->b = b < 0.0f ? 0.0f : (b > 1.0f ? 1.0f : b);
			this->a = a < 0.0f ? 0.0f : (a > 1.0f ? 1.0f : a);
		}
		void Set(const Colour4f & other) { Set(other.r, other.g, other.b, other.a); }
		void Set(const Colour & other) { const f32 inv = 1.0f / 255.0f; Set(other.GetRed() * inv, g = other.GetGreen() * inv, b = other.GetBlue() * inv, a = other.GetAlpha() * inv); }

		f32 GetRed() const { return r; }
		f32 GetGreen() const { return g; }
		f32 GetBlue() const { return b; }
		f32 GetAlpha() const { return a; }

		f32 GetAverage() const { return (GetRed() + GetGreen() + GetBlue()) / 3.0f; }

		Colour4f GetInterpolated(const Colour4f & other, f32 d) const
		{
			d = d < 0.0f ? 0.0f : (d > 1.0f ? 1.0f : d); // clamp
			const f32 inv = 1.0f - d;
			return Colour4f(other.r * inv + r * d, other.g * inv + g * d, other.b * inv + b * d, other.a * inv + a * d);
		}

		Colour ToColour() const { return Colour((u32)(r * 255.0f), (u32)(g * 255.0f), (u32)( b * 255.0f), (u32)(a * 255.0f)); }
	};

	

	static const int MAX_VERTEX = 512;
}
#endif // __FW_TYPES_H__
