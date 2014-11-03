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
	private:
		// DON'T USE THE BASE ANCHORS FOR POSITIONING
		static const u8 TOP         = (1 << 0);
		static const u8 VCENTER     = (1 << 1);
		static const u8 BOTTOM      = (1 << 2);
		static const u8 LEFT        = (1 << 3);
		static const u8 HCENTER     = (1 << 4);
		static const u8 RIGHT       = (1 << 5);
	public:
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

	// COLOUR
	class Colour
	{
	public:

		//TODO: name these in a Norm friendly manner
		enum EColourFormat
		{
			ColourFormat_RGBA = 0,
			ColourFormat_ARGB,

			ColourFormat_count,
			ColourFormat_invalid = -1
		};

		// colour codes, from http://www.w3schools.com/html/html_colornames.asp
		static const Colour Black;
		static const Colour Navy;
		static const Colour DarkBlue;
		static const Colour MediumBlue;
		static const Colour Blue;
		static const Colour DarkGreen;
		static const Colour Green;
		static const Colour Teal;
		static const Colour DarkCyan;
		static const Colour DeepSkyBlue;
		static const Colour DarkTurquoise;
		static const Colour MediumSpringGreen;
		static const Colour Lime;
		static const Colour SpringGreen;
		static const Colour Aqua;
		static const Colour Cyan;
		static const Colour MidnightBlue;
		static const Colour DodgerBlue;
		static const Colour LightSeaGreen;
		static const Colour ForestGreen;
		static const Colour SeaGreen;
		static const Colour DarkSlateGray;
		static const Colour LimeGreen;
		static const Colour MediumSeaGreen;
		static const Colour Turquoise;
		static const Colour RoyalBlue;
		static const Colour SteelBlue;
		static const Colour DarkSlateBlue;
		static const Colour MediumTurquoise;
		static const Colour Indigo;
		static const Colour DarkOliveGreen;
		static const Colour CadetBlue;
		static const Colour CornflowerBlue;
		static const Colour MediumAquaMarine;
		static const Colour DimGray;
		static const Colour SlateBlue;
		static const Colour OliveDrab;
		static const Colour SlateGray;
		static const Colour LightSlateGray;
		static const Colour MediumSlateBlue;
		static const Colour LawnGreen;
		static const Colour Chartreuse;
		static const Colour Aquamarine;
		static const Colour Maroon;
		static const Colour Purple;
		static const Colour Olive;
		static const Colour Gray;
		static const Colour SkyBlue;
		static const Colour LightSkyBlue;
		static const Colour BlueViolet;
		static const Colour DarkRed;
		static const Colour DarkMagenta;
		static const Colour SaddleBrown;
		static const Colour DarkSeaGreen;
		static const Colour LightGreen;
		static const Colour MediumPurple;
		static const Colour DarkViolet;
		static const Colour PaleGreen;
		static const Colour DarkOrchid;
		static const Colour YellowGreen;
		static const Colour Sienna;
		static const Colour Brown;
		static const Colour DarkGray;
		static const Colour LightBlue;
		static const Colour GreenYellow;
		static const Colour PaleTurquoise;
		static const Colour LightSteelBlue;
		static const Colour PowderBlue;
		static const Colour FireBrick;
		static const Colour DarkGoldenRod;
		static const Colour MediumOrchid;
		static const Colour RosyBrown;
		static const Colour DarkKhaki;
		static const Colour Silver;
		static const Colour MediumVioletRed;
		static const Colour IndianRed;
		static const Colour Peru;
		static const Colour Chocolate;
		static const Colour Tan;
		static const Colour LightGray;
		static const Colour Thistle;
		static const Colour Orchid;
		static const Colour GoldenRod;
		static const Colour PaleVioletRed;
		static const Colour Crimson;
		static const Colour Gainsboro;
		static const Colour Plum;
		static const Colour BurlyWood;
		static const Colour LightCyan;
		static const Colour Lavender;
		static const Colour DarkSalmon;
		static const Colour Violet;
		static const Colour PaleGoldenRod;
		static const Colour LightCoral;
		static const Colour Khaki;
		static const Colour AliceBlue;
		static const Colour HoneyDew;
		static const Colour Azure;
		static const Colour SandyBrown;
		static const Colour Wheat;
		static const Colour Beige;
		static const Colour WhiteSmoke;
		static const Colour MintCream;
		static const Colour GhostWhite;
		static const Colour Salmon;
		static const Colour AntiqueWhite;
		static const Colour Linen;
		static const Colour LightGoldenRodYellow;
		static const Colour OldLace;
		static const Colour Red;
		static const Colour Fuchsia;
		static const Colour Magenta;
		static const Colour DeepPink;
		static const Colour OrangeRed;
		static const Colour Tomato;
		static const Colour HotPink;
		static const Colour Coral;
		static const Colour DarkOrange;
		static const Colour LightSalmon;
		static const Colour Orange;
		static const Colour LightPink;
		static const Colour Pink;
		static const Colour Gold;
		static const Colour PeachPuff;
		static const Colour NavajoWhite;
		static const Colour Moccasin;
		static const Colour Bisque;
		static const Colour MistyRose;
		static const Colour BlanchedAlmond;
		static const Colour PapayaWhip;
		static const Colour LavenderBlush;
		static const Colour SeaShell;
		static const Colour Cornsilk;
		static const Colour LemonChiffon;
		static const Colour FloralWhite;
		static const Colour Snow;
		static const Colour Yellow;
		static const Colour LightYellow;
		static const Colour Ivory;
		static const Colour White;

	protected:

		f32 m_red;
		f32 m_green;
		f32 m_blue;
		f32 m_alpha;

	public:

		// constructors
		Colour() { Set(1.0f, 1.0f, 1.0f, 1.0f); }
		Colour(const Colour & other) { Set(other); }
		Colour(const u32 c, EColourFormat colourFormat) { Set(c, colourFormat); }
		Colour(const u8 r, const u8 g, const u8 b, const u8 a) { Set(r, g, b, a); }
		Colour(const f32 r, const f32 g, const f32 b, const f32 a) { Set(r, g, b, a); }

		// operators
		bool operator==(const Colour& other) const;
		bool operator!=(const Colour& other) const;
		Colour& operator=(const Colour& other);

		// getters
 		u32 GetAsInt(EColourFormat colourFormat) const;
		void GetAsHexString(char * charArray, u32 maxlen, EColourFormat colourFormat) const;
		u8 GetRedI() const { return (u8)(m_red * 255.0f); }
		u8 GetGreenI() const { return (u8)(m_green * 255.0f); }
		u8 GetBlueI() const { return (u8)(m_blue * 255.0f); }
		u8 GetAlphaI() const { return (u8)(m_alpha * 255.0f); }
		f32 GetRedF() const { return m_red; }
		f32 GetGreenF() const { return m_green; }
		f32 GetBlueF() const { return m_blue; }
		f32 GetAlphaF() const { return m_alpha; }
		
		// setters
		void Set(const Colour & other);
 		void Set(const u32 colour, EColourFormat colourFormat);
 		void Set(const u8 r, const u8 g, const u8 b, const u8 a);
		void Set(const f32 r, const f32 g, const f32 b, const f32 a);
		void SetRed(const u8 r) { m_red = r / 255.0f; }
		void SetGreen(const u8 g) { m_green = g / 255.0f; }
		void SetBlue(const u8 b) { m_blue = b / 255.0f; }
		void SetAlpha(const u8 a) { m_alpha = a / 255.0f; }
		void SetRed(const f32 r);
		void SetGreen(const f32 g);
		void SetBlue(const f32 b);
		void SetAlpha(const f32 a);
	};


	static const int MAX_VERTEX = 512;
}
#endif // __FW_TYPES_H__
