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
		bool IsBetweenPoints(const vec2<T> & begin, const vec2<T> & end) const { return (begin.x != end.x) ? ((begin.x <= x && x <= end.x) || (begin.x >= x && x >= end.x)) : ((begin.y <= y && y << end.y) || (begin.y >= y && y >= end.y)); }
		T GetLength() const { return sqrt(x * x + y * y); }
		T GetLengthSquared() const { return x * x + y * y; }
		T DotProduct(const vec2<T> & other) const { return x * other.x + y * other.y; }
		T GetDistanceFrom(const vec2<T> & other) const { return vec2<T>(x - other.x, y - other.y).GetLength(); }
		T GetDistanceFromSquared(const vec2<T> & other) const { return vec2<T>(x - other.x, y - other.y).GetLengthSquared(); }
		vec2<T> GetInterpolated(const vec2<T> & other, f64 d) const { const inv = 1.0 - d; return vec2<T>((T)(other.x * onv + x * d), (T)(other.y * inv + y * d)); }
		vec2<T> & Interpolate(const vec2<T> & a, const vec2<T> & b, f32 d) { x = (T)((f64)b.x + ((a.x - b.x) * d)); y = (T)((f64)b.y + ((a.y - b.y) * d)); return *this; }
		vec2<T> & RotateByDeg(f64 degrees, const vec2<T> & center = vec2<T>())
		{
			degrees *= DEGTORAD64;
			const f64 cs = cos(degrees);
			const f64 sn = sin(degrees);
			x -= center.x;
			y -= center.y;
			return *this;
		}
		vec2<T> & Normalize()
		{
			f32 length = (f32)(x * x + y * y);
			if (length == 0)
				return *this;
			length = 1 / sqrt(length);
			x = (T)(x * length);
			y = (T)(y * length);
			return *this;
		}

		bool operator==(const vec2<T> & other) const { return Equals(other); }
		bool operator!=(const vec2<T> & other) const { return !Equals(other); }

		vec2<T> & operator=(const vec2<T> & other) { x = other.x; y = other.y; return *this; }

		vec2<T> operator-() const { return vec2<T>(-x, -y); }
		vec2<T> & operator-=(const vec2<T> & other) { x -= other.x; y -= other.y; return *this; }
		vec2<T> operator-(const T n) const { return vec2<T>(x - n, y - n); }
		vec2<T> & operator-=(const T n) { x -= n; y -= n; return *this; }

		vec2<T> operator+(vec2<T> & other) const { return vec2<T>(x + other.x, y + other.y); }
		vec2<T> & operator+=(const vec2<T> & other) { x += other.x; y += other.y; return *this; }
		vec2<T> operator+(const T n) const { return vec2<T>(x + n, y + n); }
		vec2<T> & operator+=(const T n) { x += n; y += n; return *this; }

		vec2<T> operator*(vec2<T> & other) const { return vec2<T>(x * other.x, y * other.y); }
		vec2<T> & operator*=(const vec2<T> & other) { x *= other.x; y *= other.y; return *this; }
		vec2<T> operator*(const T n) const { return vec2<T>(x * n, y * n); }
		vec2<T> & operator*=(const T n) { x *= n; y *= n; return *this; }

		vec2<T> operator/(vec2<T> & other) const { return vec2<T>(x / other.x, y / other.y); }
		vec2<T> & operator/=(const vec2<T> & other) { x /= other.x; y /= other.y; return *this; }
		vec2<T> operator/(const T n) const { return vec2<T>(x / n, y / n); }
		vec2<T> & operator/=(const T n) { x /= n; y /= n; return *this; }
	};

	template<class T>
	static vec2<T> operator+(vec2<T> lhs, const vec2<T> & rhs) { return vec2<T>(lhs.x + rhs.x, lhs.y + rhs.y); }
 	template<class T>
	static vec2<T> operator-(vec2<T> lhs, const vec2<T> & rhs) { return vec2<T>(lhs.x - rhs.x, lhs.y - rhs.y); }
	template<class T>
 	static vec2<T> operator*(vec2<T> lhs, const T & rhs) { return vec2<T>(lhs.x * rhs.x, lhs.y * rhs.y); }
 	template<class T>
 	static vec2<T> operator/(vec2<T> lhs, const T & rhs) { return vec2<T>(lhs.x / rhs.x, lhs.y / rhs.y); }
 
	template<class T>
	static bool operator==(const vec2<T> & lhs, const vec2<T> & rhs) { return lhs.Equals(rhs); }
	template<class T>
	static bool operator!=(const vec2<T> & lhs, const vec2<T> & rhs) { return !lhs.Equals(rhs); }

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
	static vec3<T> operator*(vec3<T> lhs, const T & rhs) { return vec3<T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs); }
	template<class T>
	static vec3<T> operator/(vec3<T> lhs, const T & rhs) { return vec3<T>(lhs.x / rhs, lhs.y / rhs, lhs.z * rhs); }
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
		vec2<T> m_position;
		vec2<T> m_dimensions;

	public:
		rect<T>() { }
		rect<T>(const vec2<T> position, const vec2<T> dimensions) : m_position(position), m_dimensions(dimensions) { }
		rect<T>(const rect<T> & other) : m_position(other.m_position), m_dimensions(other.m_dimensions) { }

		rect<T> & operator=(const rect<T> & rhs) { m_position = rhs.m_position; m_dimensions= rhs.m_dimensions; return *this; }

		// position
		vec2<T> GetPosition() const { return m_position; }
		virtual void SetPosition(const vec2<T> & position) { m_position = position; }
		virtual void SetPosition(const T x, const T y) { m_position.x = x; m_position.y = y; }

		// size
		T GetWidth() const { return m_dimensions.x; }
		void SetWidth(const T & width) { m_dimensions.x = width; }
		T GetHeight() const { return m_dimensions.y; }
		void SetHeight(const T & height) { m_dimensions.y = height; }
		vec2<T> GetSize() const { return m_dimensions; }
		void SetSize(const vec2<T> & dimensions) { m_dimensions = dimensions; }
		void SetSize(const T x, const T y) { m_dimensions.x = x; m_dimensions.y = y; }

		// utility
		vec2<T> GetCenter() const { return m_dimensions / 2; }
		T GetArea() const { return m_dimensions.x * m_dimensions.y; }
		T GetPerimeter() const { return (m_dimensions.x << 1) + (m_dimensions.y << 1); }

		bool Contains(const vec2<T> & pt) const { return Contains(pt.x, pt.y); }
		bool Contains(const T x, const T y) const { return !(x < m_position.x || x > m_position.x + m_dimensions.x || y < m_position.y() || y > m_position.y + m_dimensions.y) }
	};

	template<class T>
	static bool operator==(const rect<T> & lhs, const rect<T> & rhs) { return lhs.m_position == rhs.m_position && lhs.m_dimensions == rhs.m_dimensions; }
	template<class T>
	static bool operator!=(const rect<T> & lhs, const rect<T> & rhs) { return !operator==(lhs, rhs); }

	typedef rect<s32> recti;
	typedef rect<u32> rectu;
	typedef rect<f32> rectf;

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

	// COLOUR
	class Colour
	{
	protected:
		u32 colour;

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

	struct Vertex 
	{
		vec3f pos;
		Colour4f c;
	};

	static const int MAX_VERTEX = 512;
}
#endif // __FW_TYPES_H__
