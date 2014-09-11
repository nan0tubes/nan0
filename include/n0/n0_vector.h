//
//  n0_vector.h
//  n0
//
//  Created by Norman van der Ploeg on 2014-09-10.
//  Copyright (c) 2014 Norman van der Ploeg. All rights reserved.
//

#ifndef n0_n0_vector_h
#define n0_n0_vector_h




namespace n0
{
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
        vec2<T> GetInterpolated(const vec2<T> & other, f64 d) const { const float inv = 1.0 - d; return vec2<T>((T)(other.x * inv + x * d), (T)(other.y * inv + y * d)); }
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
    
}
#endif
