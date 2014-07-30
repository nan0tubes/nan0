#include "n0/n0.h"

namespace n0
{
	template<class T>
	bool Vec2<T>::IsBetweenPoints(const Vec2<T> & begin, const Vec2<T> & end) const
	{
		if (begin.GetX() != end.GetX())
			return ((begin.GetX() <= this->x && this->x <= end.GetX()) || (begin.GetX >= this->x && this->x >= end.GetX()));
		else
			return ((begin.GetY() <= this->y && this->y <= end.GetY()) || (begin.GetY() >= this->y && this->y >= end.GetY()));
	}

	Colour Colour::operator+(const Colour& other) const
	{	
		return Colour(min(GetRed() + other.GetRed(), 255),
					  min(GetGreen() + other.GetGreen(), 255),
					  min(GetBlue() + other.GetBlue(), 255),
					  min(GetAlpha() + other.GetAlpha(), 255)); 
	}

	Colour Colour::GetInterpolated(const Colour & other, f32 d) const
	{
		d = d < 0.0f ? 0.0f : (d > 1.0f ? 1.0f : d); // clamp
		const f32 inv = 1.0f - d;
		return Colour((u32)(other.GetRed() * inv + GetRed() * d),
					  (u32)(other.GetGreen() * inv + GetGreen() * d),
					  (u32)(other.GetBlue() * inv + GetBlue() * d),
					  (u32)(other.GetAlpha() * inv + GetAlpha() * d));
	}

	void Colour4f::Set(const f32 r, const f32 g, const f32 b, const f32 a)
	{
		// clamp all the things!
		this->r = r < 0.0f ? 0.0f : (r > 1.0f ? 1.0f : r);
		this->g = g < 0.0f ? 0.0f : (g > 1.0f ? 1.0f : g);
		this->b = b < 0.0f ? 0.0f : (b > 1.0f ? 1.0f : b);
		this->a = a < 0.0f ? 0.0f : (a > 1.0f ? 1.0f : a);
	}

	Colour4f Colour4f::GetInterpolated(const Colour4f & other, f32 d) const
	{
		d = d < 0.0f ? 0.0f : (d > 1.0f ? 1.0f : d); // clamp
		const f32 inv = 1.0f - d;
		return Colour4f(other.r * inv + r * d, other.g * inv + g * d, other.b * inv + b * d, other.a * inv + a * d);
	}
}