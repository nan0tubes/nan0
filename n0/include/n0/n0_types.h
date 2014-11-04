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


	static const int MAX_VERTEX = 512;
}
#endif // __FW_TYPES_H__
