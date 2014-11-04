#include "n0/n0.h"

namespace n0
{
	// colour codes, from http://www.w3schools.com/html/html_colornames.asp and are in RGBA format
	const Colour Colour::Black(0x000000ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Navy(0x000080ff, Colour::ColourFormat_RGBA);
	const Colour Colour::DarkBlue(0x00008Bff, Colour::ColourFormat_RGBA);
	const Colour Colour::MediumBlue(0x0000CDff, Colour::ColourFormat_RGBA);
	const Colour Colour::Blue(0x0000FFff, Colour::ColourFormat_RGBA);
	const Colour Colour::DarkGreen(0x006400ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Green(0x008000ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Teal(0x008080ff, Colour::ColourFormat_RGBA);
	const Colour Colour::DarkCyan(0x008B8Bff, Colour::ColourFormat_RGBA);
	const Colour Colour::DeepSkyBlue(0x00BFFFff, Colour::ColourFormat_RGBA);
	const Colour Colour::DarkTurquoise(0x00CED1ff, Colour::ColourFormat_RGBA);
	const Colour Colour::MediumSpringGreen(0x00FA9Aff, Colour::ColourFormat_RGBA);
	const Colour Colour::Lime(0x00FF00ff, Colour::ColourFormat_RGBA);
	const Colour Colour::SpringGreen(0x00FF7Fff, Colour::ColourFormat_RGBA);
	const Colour Colour::Aqua(0x00FFFFff, Colour::ColourFormat_RGBA);
	const Colour Colour::Cyan(0x00FFFFff, Colour::ColourFormat_RGBA);
	const Colour Colour::MidnightBlue(0x191970ff, Colour::ColourFormat_RGBA);
	const Colour Colour::DodgerBlue(0x1E90FFff, Colour::ColourFormat_RGBA);
	const Colour Colour::LightSeaGreen(0x20B2AAff, Colour::ColourFormat_RGBA);
	const Colour Colour::ForestGreen(0x228B22ff, Colour::ColourFormat_RGBA);
	const Colour Colour::SeaGreen(0x2E8B57ff, Colour::ColourFormat_RGBA);
	const Colour Colour::DarkSlateGray(0x2F4F4Fff, Colour::ColourFormat_RGBA);
	const Colour Colour::LimeGreen(0x32CD32ff, Colour::ColourFormat_RGBA);
	const Colour Colour::MediumSeaGreen(0x3CB371ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Turquoise(0x40E0D0ff, Colour::ColourFormat_RGBA);
	const Colour Colour::RoyalBlue(0x4169E1ff, Colour::ColourFormat_RGBA);
	const Colour Colour::SteelBlue(0x4682B4ff, Colour::ColourFormat_RGBA);
	const Colour Colour::DarkSlateBlue(0x483D8Bff, Colour::ColourFormat_RGBA);
	const Colour Colour::MediumTurquoise(0x48D1CCff, Colour::ColourFormat_RGBA);
	const Colour Colour::Indigo (0x4B0082ff, Colour::ColourFormat_RGBA);
	const Colour Colour::DarkOliveGreen(0x556B2Fff, Colour::ColourFormat_RGBA);
	const Colour Colour::CadetBlue(0x5F9EA0ff, Colour::ColourFormat_RGBA);
	const Colour Colour::CornflowerBlue(0x6495EDff, Colour::ColourFormat_RGBA);
	const Colour Colour::MediumAquaMarine(0x66CDAAff, Colour::ColourFormat_RGBA);
	const Colour Colour::DimGray(0x696969ff, Colour::ColourFormat_RGBA);
	const Colour Colour::SlateBlue(0x6A5ACDff, Colour::ColourFormat_RGBA);
	const Colour Colour::OliveDrab(0x6B8E23ff, Colour::ColourFormat_RGBA);
	const Colour Colour::SlateGray(0x708090ff, Colour::ColourFormat_RGBA);
	const Colour Colour::LightSlateGray(0x778899ff, Colour::ColourFormat_RGBA);
	const Colour Colour::MediumSlateBlue(0x7B68EEff, Colour::ColourFormat_RGBA);
	const Colour Colour::LawnGreen(0x7CFC00ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Chartreuse(0x7FFF00ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Aquamarine(0x7FFFD4ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Maroon(0x800000ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Purple(0x800080ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Olive(0x808000ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Gray(0x808080ff, Colour::ColourFormat_RGBA);
	const Colour Colour::SkyBlue(0x87CEEBff, Colour::ColourFormat_RGBA);
	const Colour Colour::LightSkyBlue(0x87CEFAff, Colour::ColourFormat_RGBA);
	const Colour Colour::BlueViolet(0x8A2BE2ff, Colour::ColourFormat_RGBA);
	const Colour Colour::DarkRed(0x8B0000ff, Colour::ColourFormat_RGBA);
	const Colour Colour::DarkMagenta(0x8B008Bff, Colour::ColourFormat_RGBA);
	const Colour Colour::SaddleBrown(0x8B4513ff, Colour::ColourFormat_RGBA);
	const Colour Colour::DarkSeaGreen(0x8FBC8Fff, Colour::ColourFormat_RGBA);
	const Colour Colour::LightGreen(0x90EE90ff, Colour::ColourFormat_RGBA);
	const Colour Colour::MediumPurple(0x9370DBff, Colour::ColourFormat_RGBA);
	const Colour Colour::DarkViolet(0x9400D3ff, Colour::ColourFormat_RGBA);
	const Colour Colour::PaleGreen(0x98FB98ff, Colour::ColourFormat_RGBA);
	const Colour Colour::DarkOrchid(0x9932CCff, Colour::ColourFormat_RGBA);
	const Colour Colour::YellowGreen(0x9ACD32ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Sienna(0xA0522Dff, Colour::ColourFormat_RGBA);
	const Colour Colour::Brown(0xA52A2Aff, Colour::ColourFormat_RGBA);
	const Colour Colour::DarkGray(0xA9A9A9ff, Colour::ColourFormat_RGBA);
	const Colour Colour::LightBlue(0xADD8E6ff, Colour::ColourFormat_RGBA);
	const Colour Colour::GreenYellow(0xADFF2Fff, Colour::ColourFormat_RGBA);
	const Colour Colour::PaleTurquoise(0xAFEEEEff, Colour::ColourFormat_RGBA);
	const Colour Colour::LightSteelBlue(0xB0C4DEff, Colour::ColourFormat_RGBA);
	const Colour Colour::PowderBlue(0xB0E0E6ff, Colour::ColourFormat_RGBA);
	const Colour Colour::FireBrick(0xB22222ff, Colour::ColourFormat_RGBA);
	const Colour Colour::DarkGoldenRod(0xB8860Bff, Colour::ColourFormat_RGBA);
	const Colour Colour::MediumOrchid(0xBA55D3ff, Colour::ColourFormat_RGBA);
	const Colour Colour::RosyBrown(0xBC8F8Fff, Colour::ColourFormat_RGBA);
	const Colour Colour::DarkKhaki(0xBDB76Bff, Colour::ColourFormat_RGBA);
	const Colour Colour::Silver(0xC0C0C0ff, Colour::ColourFormat_RGBA);
	const Colour Colour::MediumVioletRed(0xC71585ff, Colour::ColourFormat_RGBA);
	const Colour Colour::IndianRed (0xCD5C5Cff, Colour::ColourFormat_RGBA);
	const Colour Colour::Peru(0xCD853Fff, Colour::ColourFormat_RGBA);
	const Colour Colour::Chocolate(0xD2691Eff, Colour::ColourFormat_RGBA);
	const Colour Colour::Tan(0xD2B48Cff, Colour::ColourFormat_RGBA);
	const Colour Colour::LightGray(0xD3D3D3ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Thistle(0xD8BFD8ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Orchid(0xDA70D6ff, Colour::ColourFormat_RGBA);
	const Colour Colour::GoldenRod(0xDAA520ff, Colour::ColourFormat_RGBA);
	const Colour Colour::PaleVioletRed(0xDB7093ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Crimson(0xDC143Cff, Colour::ColourFormat_RGBA);
	const Colour Colour::Gainsboro(0xDCDCDCff, Colour::ColourFormat_RGBA);
	const Colour Colour::Plum(0xDDA0DDff, Colour::ColourFormat_RGBA);
	const Colour Colour::BurlyWood(0xDEB887ff, Colour::ColourFormat_RGBA);
	const Colour Colour::LightCyan(0xE0FFFFff, Colour::ColourFormat_RGBA);
	const Colour Colour::Lavender(0xE6E6FAff, Colour::ColourFormat_RGBA);
	const Colour Colour::DarkSalmon(0xE9967Aff, Colour::ColourFormat_RGBA);
	const Colour Colour::Violet(0xEE82EEff, Colour::ColourFormat_RGBA);
	const Colour Colour::PaleGoldenRod(0xEEE8AAff, Colour::ColourFormat_RGBA);
	const Colour Colour::LightCoral(0xF08080ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Khaki(0xF0E68Cff, Colour::ColourFormat_RGBA);
	const Colour Colour::AliceBlue(0xF0F8FFff, Colour::ColourFormat_RGBA);
	const Colour Colour::HoneyDew(0xF0FFF0ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Azure(0xF0FFFFff, Colour::ColourFormat_RGBA);
	const Colour Colour::SandyBrown(0xF4A460ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Wheat(0xF5DEB3ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Beige(0xF5F5DCff, Colour::ColourFormat_RGBA);
	const Colour Colour::WhiteSmoke(0xF5F5F5ff, Colour::ColourFormat_RGBA);
	const Colour Colour::MintCream(0xF5FFFAff, Colour::ColourFormat_RGBA);
	const Colour Colour::GhostWhite(0xF8F8FFff, Colour::ColourFormat_RGBA);
	const Colour Colour::Salmon(0xFA8072ff, Colour::ColourFormat_RGBA);
	const Colour Colour::AntiqueWhite(0xFAEBD7ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Linen(0xFAF0E6ff, Colour::ColourFormat_RGBA);
	const Colour Colour::LightGoldenRodYellow(0xFAFAD2ff, Colour::ColourFormat_RGBA);
	const Colour Colour::OldLace(0xFDF5E6ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Red(0xFF0000ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Fuchsia(0xFF00FFff, Colour::ColourFormat_RGBA);
	const Colour Colour::Magenta(0xFF00FFff, Colour::ColourFormat_RGBA);
	const Colour Colour::DeepPink(0xFF1493ff, Colour::ColourFormat_RGBA);
	const Colour Colour::OrangeRed(0xFF4500ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Tomato(0xFF6347ff, Colour::ColourFormat_RGBA);
	const Colour Colour::HotPink(0xFF69B4ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Coral(0xFF7F50ff, Colour::ColourFormat_RGBA);
	const Colour Colour::DarkOrange(0xFF8C00ff, Colour::ColourFormat_RGBA);
	const Colour Colour::LightSalmon(0xFFA07Aff, Colour::ColourFormat_RGBA);
	const Colour Colour::Orange(0xFFA500ff, Colour::ColourFormat_RGBA);
	const Colour Colour::LightPink(0xFFB6C1ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Pink(0xFFC0CBff, Colour::ColourFormat_RGBA);
	const Colour Colour::Gold(0xFFD700ff, Colour::ColourFormat_RGBA);
	const Colour Colour::PeachPuff(0xFFDAB9ff, Colour::ColourFormat_RGBA);
	const Colour Colour::NavajoWhite(0xFFDEADff, Colour::ColourFormat_RGBA);
	const Colour Colour::Moccasin(0xFFE4B5ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Bisque(0xFFE4C4ff, Colour::ColourFormat_RGBA);
	const Colour Colour::MistyRose(0xFFE4E1ff, Colour::ColourFormat_RGBA);
	const Colour Colour::BlanchedAlmond(0xFFEBCDff, Colour::ColourFormat_RGBA);
	const Colour Colour::PapayaWhip(0xFFEFD5ff, Colour::ColourFormat_RGBA);
	const Colour Colour::LavenderBlush(0xFFF0F5ff, Colour::ColourFormat_RGBA);
	const Colour Colour::SeaShell(0xFFF5EEff, Colour::ColourFormat_RGBA);
	const Colour Colour::Cornsilk(0xFFF8DCff, Colour::ColourFormat_RGBA);
	const Colour Colour::LemonChiffon(0xFFFACDff, Colour::ColourFormat_RGBA);
	const Colour Colour::FloralWhite(0xFFFAF0ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Snow(0xFFFAFAff, Colour::ColourFormat_RGBA);
	const Colour Colour::Yellow(0xFFFF00ff, Colour::ColourFormat_RGBA);
	const Colour Colour::LightYellow(0xFFFFE0ff, Colour::ColourFormat_RGBA);
	const Colour Colour::Ivory(0xFFFFF0ff, Colour::ColourFormat_RGBA);
	const Colour Colour::White(0xFFFFFFff, Colour::ColourFormat_RGBA);


	// constructors
	Colour::Colour()
	{
		Set(1.0f, 1.0f, 1.0f, 1.0f); 
	}

	Colour::Colour(const Colour & other)
	{
		Set(other); 
	}

	Colour::Colour(const u32 c, EColourFormat colourFormat)
	{
		Set(c, colourFormat); 
	}

	Colour::Colour(const u8 r, const u8 g, const u8 b, const u8 a)
	{
		Set(r, g, b, a); 
	}

	Colour::Colour(const f32 r, const f32 g, const f32 b, const f32 a)
	{
		Set(r, g, b, a); 
	}


	// operators
	bool Colour::operator==(const Colour& other) const
	{
		const f32 epsilon = std::numeric_limits<f32>::epsilon();
		return (fabsf(m_red - other.m_red < epsilon) && fabsf(m_green - other.m_green < epsilon) && fabsf(m_blue - other.m_blue < epsilon) && fabsf(m_alpha - other.m_alpha < epsilon));
	}

	bool Colour::operator!=(const Colour& other) const
	{
		const f32 epsilon = std::numeric_limits<f32>::epsilon();
		return !(fabsf(m_red - other.m_red < epsilon) && fabsf(m_green - other.m_green < epsilon) && fabsf(m_blue - other.m_blue < epsilon) && fabsf(m_alpha - other.m_alpha < epsilon));
	}

	Colour& Colour::operator=(const Colour& other)
	{
		Set(other);
		return *this;
	}


	// getters
	u32 Colour::GetAsInt(EColourFormat colourFormat) const
	{
		u32 retval = 0;

		switch (colourFormat)
		{
		case ColourFormat_RGBA:
			retval = (((GetRedI() & 0xff)<<24) | ((GetGreenI() & 0xff)<<16) | ((GetBlueI() & 0xff)<<8) | (GetAlphaI() & 0xff)); 
			break;
		case ColourFormat_ARGB:
			retval = (((GetAlphaI() & 0xff)<<24) | ((GetRedI() & 0xff)<<16) | ((GetGreenI() & 0xff)<<8) | (GetBlueI() & 0xff)); 
			break;
		default:
			n0_ASSERT(false, "Undefined colour format.\n");
			break;
		}

		return retval;
	}

	void Colour::GetAsHexString(char * charArray, u32 maxlen, EColourFormat colourFormat) const
	{
		snprintf(charArray, maxlen, "0x%08x", GetAsInt(colourFormat));
	}


	// setters
	void Colour::Set(const Colour & other)
	{
		m_red = other.m_red;
		m_green = other.m_green;
		m_blue = other.m_blue;
		m_alpha = other.m_alpha;
	}

	void Colour::Set(const u32 colour, EColourFormat colourFormat)
	{
		switch (colourFormat)
		{
		case ColourFormat_RGBA:
			SetRed((u8)(colour >> 24));
			SetGreen((u8)((colour >> 16) & 0xff));
			SetBlue((u8)((colour >> 8) & 0xff));
			SetAlpha((u8)(colour & 0xff));
			break;
		case ColourFormat_ARGB:
			SetAlpha((u8)(colour >> 24));
			SetRed((u8)((colour >> 16) & 0xff));
			SetGreen((u8)((colour >> 8) & 0xff));
			SetBlue((u8)(colour & 0xff));
			break;
		default:
			n0_ASSERT(false, "Undefined colour format.\n");
			break;
		}
	}

	void Colour::Set(const u8 r, const u8 g, const u8 b, const u8 a)
	{
		SetRed(r);
		SetGreen(g);
		SetBlue(b);
		SetAlpha(a);
	}

	void Colour::Set(const f32 r, const f32 g, const f32 b, const f32 a)
	{
		SetRed(r);
		SetGreen(g);
		SetBlue(b);
		SetAlpha(a);
	}

	void Colour::SetRed(const f32 r)
	{
		m_red = CLAMP<f32>(r, 0.0f, 1.0f); 
	}

	void Colour::SetGreen(const f32 g)
	{
		m_green = CLAMP<f32>(g, 0.0f, 1.0f); 
	}

	void Colour::SetBlue(const f32 b)
	{
		m_blue = CLAMP<f32>(b, 0.0f, 1.0f); 
	}

	void Colour::SetAlpha(const f32 a)
	{
		m_alpha = CLAMP<f32>(a, 0.0f, 1.0f); 
	}
} // namespace n0