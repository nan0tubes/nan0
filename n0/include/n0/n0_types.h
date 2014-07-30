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

namespace n0
{

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

	//VEC2
	template<class T>
	class vec2
	{
	public:
		T x;
		T y;

	public:
		vec2<T>() : x(0), y(0) { }
		vec2<T>(const T & value) : x(value), y(value) { }
		vec2<T>(const T & x, const T & y) : x(x), y(y) { }
		vec2<T>(const vec2<T> & other) : x(other.x), y(other.y) { }

		bool Equals(const vec2<T> & other) const { return x == other.x && y == other.y; }
		bool IsBetweenPoints(const vec2<T> & begin, const vec2<T> & end) const;

		vec2<T> & operator=(const vec2<T> & rhs) { x = rhs.x; y = rhs.y; return *this; }
		vec2<T> & operator+=(const vec2<T> & rhs) { x += rhs.x; y += rhs.y; return *this; }
		vec2<T> & operator-=(const vec2<T> & rhs) { x -= rhs.x; y -= rhs.y; return *this; }
	};

	template<class T>
	static vec2<T> operator+(vec2<T> lhs, const vec2<T> & rhs) { lhs += rhs; return lhs; }
	template<class T>
	static vec2<T> operator-(vec2<T> lhs, const vec2<T> & rhs) { lhs -= rhs; return lhs; }
	template<class T>
	static vec2<T> operator*(vec2<T> lhs, const T & rhs) { lhs.x *= rhs; lhs.y *= rhs; return lhs; }
	template<class T>
	static vec2<T> operator/(vec2<T> lhs, const T & rhs) { lhs.x /= rhs; lhs.y /= rhs; return lhs; }

	template<class T>
	static bool operator==(const vec2<T> & lhs, const vec2<T> & rhs) { return lhs.Equals(rhs); }
	template<class T>
	static bool operator!=(const vec2<T> & lhs, const vec2<T> & rhs) { return !operator==(lhs, rhs); }

	typedef vec2<s32> vec2i;
	typedef vec2<u32> vec2u;
	typedef vec2<f32> vec2f;

	// VEC3
	template<class T>
	class vec3
	{
	public:
		T x;
		T y;
		T z;

	public:
		vec3<T>() : x(0), y(0), z(0) { }
		vec3<T>(const T & value) : x(value), y(value), z(value) { }
		vec3<T>(const T & x, const T & y, const T & z) : x(x), y(y), z(z) { }
		vec3<T>(const vec3<T> & other) : x(other.x), y(other.y), z(other.z) { }

		bool Equals(const vec3<T> & other) const { return x == other.x && y == other.y && z == other.z; }
//		bool IsBetweenPoints(const vec3<T> & begin, const vec3<T> & end) const;

		vec3<T> & operator=(const vec3<T> & rhs) { x = rhs.x; y = rhs.y; z = rhs.z; return *this; }
		vec3<T> & operator+=(const vec3<T> & rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
		vec3<T> & operator-=(const vec3<T> & rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
	};

	template<class T>
	static vec3<T> operator+(vec3<T> lhs, const vec3<T> & rhs) { lhs += rhs; return lhs; }
	template<class T>
	static vec3<T> operator-(vec3<T> lhs, const vec3<T> & rhs) { lhs -= rhs; return lhs; }
	template<class T>
	static vec3<T> operator*(vec3<T> lhs, const T & rhs) { lhs.x *= rhs; lhs.y *= rhs; return lhs; }
	template<class T>
	static vec3<T> operator/(vec3<T> lhs, const T & rhs) { lhs.x /= rhs; lhs.y /= rhs; return lhs; }
	template<class T>
	static bool operator==(const vec3<T> & lhs, const vec3<T> & rhs) { return lhs.Equals(rhs); }
	template<class T>
	static bool operator!=(const vec3<T> & lhs, const vec3<T> & rhs) { return !operator==(lhs, rhs); }

	typedef vec3<s32> vec3i;
	typedef vec3<u32> vec3u;
	typedef vec3<f32> vec3f;

	// RECT
	template<class T>
	class rect
	{
	protected:
		vec2<T> position;
		vec2<T> dimensions;

	public:
		rect<T>() { }
		rect<T>(const vec2<T> position, const vec2<T> dimensions) : position(position), dimensions(dimensions) { }
		rect<T>(const rect<T> & other) : position(other.position), dimensions(other.dimensions) { }

		rect<T> & operator=(const rect<T> & rhs) { position = rhs.position; dimensions= rhs.dimensions; return *this; }

		// position
		vec2<T> GetPosition() const { return position; }
		void SetPosition(const vec2<T> & position) { this->position = position; }
		void SetPosition(const T x, const T y) { position.x = x; position.y = y; }

		// size
		T GetWidth() const { return dimensions.x; }
		void SetWidth(const T & width) { dimensions.x = width; }
		T GetHeight() const { return dimensions.y; }
		void SetHeight(const T & height) { dimensions.y = height; }
		vec2<T> GetSize() const { return dimensions; }
		void SetSize(const vec2<T> & dimensions) { this->dimensions = dimensions; }
		void SetSize(const T x, const T y) { dimensions.x = x; dimensions.y = y; }

		// utility
		vec2<T> GetCenter() const { return vec2<T>(position + (dimensions / 2)); }
		T GetArea() const { return GetWidth() * GetHeight(); }
		T GetPerimeter() const { return (GetWidth() << 1) + (GetHeight() << 1); }

		bool Contains(const vec2<T> & pt) const { return Contains(pt.x, pt.y); }
		bool Contains(const T x, const T y) const { return !(x < position.x || x > position.x + dimensions.x || y < position.y() || y > position.y + dimensions.y) }
	};

	template<class T>
	static bool operator==(const rect<T> & lhs, const rect<T> & rhs) { return lhs.position == rhs.position && lhs.dimensions == rhs.dimensions; }
	template<class T>
	static bool operator!=(const rect<T> & lhs, const rect<T> & rhs) { return !operator==(lhs, rhs); }

	typedef rect<s32> recti;
	typedef rect<u32> rectu;
	typedef rect<f32> rectf;

	// ANCHOR
	class Anchor
	{
	public:
		static const u8 TOP         = (1 << 0);
		static const u8 VCENTER     = (1 << 1);
		static const u8 BOTTOM      = (1 << 2);
		static const u8 LEFT        = (1 << 3);
		static const u8 HCENTER     = (1 << 4);
		static const u8 RIGHT       = (1 << 5);
		static const u8 TOPLEFT     = TOP | LEFT;
		static const u8 TOPRIGHT    = TOP | RIGHT;
		static const u8 BOTTOMLEFT  = BOTTOM | LEFT;
		static const u8 BOTTOMRIGHT = BOTTOM | RIGHT;
		static const u8 CENTER      = HCENTER | VCENTER;
	};

	// COLOUR
	class Colour
	{
	private:
		u32 colour;

	public:
		Colour() : colour(0) { }
		Colour(const Colour & other) : colour(other.colour) { }
		Colour(const u32 colour) { Set(colour); }
		Colour(const u32 r, const u32 g, const u32 b, const u32 a) { Set(r, g, b, a); }

		bool operator==(const Colour& other) const { return colour == other.colour; }
		bool operator!=(const Colour& other) const { return colour != other.colour; }
		Colour operator+(const Colour& other) const;
		
		void Set(const u32 c) { colour = c; }
		void Set(const u32 r, const u32 g, const u32 b, const u32 a) { colour = (((r & 0xff)<<24) | ((g & 0xff)<<16) | ((b & 0xff)<<8) | (a & 0xff)); }

		u32 GetRed() const { return colour >> 24; }
		void SetRed(const u32 r) { colour = ((r & 0xff)<<24) | (colour & 0x00ffffff); }
		u32 GetGreen() const { return (colour >> 16) & 0xff; }
		void SetGreen(const u32 g) { colour = ((g & 0xff)<<16) | (colour & 0xff00ffff); }
		u32 GetBlue() const { return (colour >> 8) & 0xff; }
		void SetBlue(const u32 b) { colour = ((b & 0xff)<<8) | (colour & 0xffff00ff); }
		u32 GetAlpha() const { return colour & 0xff; }
		void SetAlpha(const u32 a) { colour = (a & 0xff) | (colour & 0xffffff00); }

		u32 GetValue() const { return colour; }
		u32 GetAverage() const { return (GetRed() + GetGreen() + GetBlue()) / 3; }

		Colour GetInterpolated(const Colour & other, f32 d) const;
	};

	class Colour4f
	{
	private:
		f32 r;
		f32 g;
		f32 b;
		f32 a;

	public:
		Colour4f() { Set(0.0f, 0.0f, 0.0f, 0.0f); }
		Colour4f(const Colour4f & other) { Set(other); }
		Colour4f(const u32 colour) { Set(Colour(colour)); }
		Colour4f(const f32 r, const f32 g, const f32 b, const f32 a) { Set(r, g, b, a); }
		Colour4f(const Colour & other) { const f32 inv = 1.0f / 255.0f; Set(other.GetRed() * inv, g = other.GetGreen() * inv, b = other.GetBlue() * inv, a = other.GetAlpha() * inv); }

		void Set(const f32 r, const f32 g, const f32 b, const f32 a);
		void Set(const Colour4f & other) { Set(other.r, other.g, other.b, other.a); }
		void Set(const Colour & other) { Set((f32)other.GetRed(), (f32)other.GetGreen(), (f32)other.GetBlue(), (f32)other.GetAlpha()); }

		Colour ToColour() const { return Colour((u32)(r * 255.0f), (u32)(g * 255.0f), (u32)( b * 255.0f), (u32)(a * 255.0f)); }

		f32 GetRed() const { return r; }
		f32 GetGreen() const { return g; }
		f32 GetBlue() const { return b; }
		f32 GetAlpha() const { return a; }

		f32 GetAverage() const { return (GetRed() + GetGreen() + GetBlue()) / 3.0f; }

		Colour4f GetInterpolated(const Colour4f & other, f32 d) const;
	};

	struct Vertex 
	{
		vec3f pos;
		Colour4f c;
	};

	static const int MAX_VERTEX = 512;
}
#endif // __FW_TYPES_H__