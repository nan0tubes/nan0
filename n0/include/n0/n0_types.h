#ifndef __FW_TYPES_H__
#define __FW_TYPES_H__


typedef unsigned char btye;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;
typedef float f32;
typedef double f64;


#ifdef __IRRLICHT_H_INCLUDED__

typedef irr::core::vector2df vec2f;
typedef irr::core::vector2di vec2i;
typedef irr::core::vector3df vec3f;
typedef irr::core::vector3di vec3i;
typedef irr::scene::IBillboardSceneNode irrBillboardSceneNode;
typedef irr::scene::ISceneNode irrSceneNode;

#else

typedef struct _vec2f {
	f32 X;
	f32 Y;
	
	_vec2f() { X = 0; Y = 0; }
	_vec2f(f32 x,f32 y):X(x),Y(y) {}
	_vec2f operator +(_vec2f &b) { X += b.X; Y += b.Y; return *this; }

} vec2f;

typedef struct _vec2i {
	s32 X;
	s32 Y;
	_vec2i() { X = 0; Y = 0; }
	_vec2i(s32 x,s32 y):X(x),Y(y) {}
	_vec2i operator +(_vec2i &b) { X += b.X; Y += b.Y; return *this; }
} vec2i;

typedef struct _vec3f {
	f32 X;
	f32 Y;
	f32 Z;

	_vec3f() { X = 0; Y = 0; Z = 0;}
	_vec3f(f32 x,f32 y,f32 z):X(x),Y(y),Z(z) {}
	_vec3f operator +(_vec3f &b) { X += b.X; Y += b.Y; Z += b.Z; return *this; }
} vec3f;

typedef struct _vec3i {
	s32 X;
	s32 Y;
	s32 Z;

	
	_vec3i() { X = 0; Y = 0; Z = 0;}
	_vec3i(s32 x,s32 y,s32 z):X(x),Y(y),Z(z) {}
	_vec3i operator +(_vec3i &b) { X += b.X; Y += b.Y; Z += b.Z; return *this; }
} vec3i;
#endif

#endif // __FW_TYPES_H__