#include "n0/n0.h"

namespace n0
{
	// this is in the .cpp to make the includes simpler (for use of min() ).
	Colour Colour::operator+(const Colour& other) const
	{	
		return Colour(min(GetRed() + other.GetRed(), 255),
			min(GetGreen() + other.GetGreen(), 255),
			min(GetBlue() + other.GetBlue(), 255),
			min(GetAlpha() + other.GetAlpha(), 255)); 
	}
	
	char * Colour::GetHex()
	{
		sprintf(retbuf, "0x%08x", colour); return retbuf;
	}

}
