#ifndef __DEFINES_H__
#define __DEFINES_H__

//Mark: - MACROS
#define ASSERT(cond) assert((cond))
#define n0_ASSERT(cond, output, ...) { if(!(cond)) { printf("ASSERT: %s:%d\n",__FILE__,__LINE__); printf(output, ##__VA_ARGS__); ASSERT((cond)); } }
#define n0_MALLOC(sz) malloc(sz)
#define n0_FREE(pData) { if(pData) { free(pData); } }
#ifdef nullptr
	#define NULL nullptr
#else
	#define NULL 0
#endif

#define NEW new
#define SAFE_DELETE(p) { if (p) delete (p); p = NULL; }

#if defined(_MSC_VER)
	#if !defined(snprintf)
		#define snprintf sprintf_s
	#endif
	#if !defined(strncpy)
		#define strncpy strncpy_s
	#endif
#endif

#define memzero(ptr, sz) { n0_ASSERT((ptr) != NULL, "trying to memzero NULL");  memset((ptr),0,(sz)); }

//Mark: - CONSTANTS
#define kTrue 1
#define kFalse 0

// common string lengths
#define kStrLen_Fine		   8
#define kStrLen_Diminutive	  16
#define kStrLen_Tiny		  32
#define kStrLen_Small		  64
#define kStrLen_Medium		 128
#define kStrLen_Large		 256
#define kStrLen_Huge		 512
#define kStrLen_Gargantuan	1024
#define kStrLen_Colassal	2048

#define kMaxFilenameLength 512

// colour codes, from http://www.w3schools.com/html/html_colornames.asp
#define kColour_Black	0xff000000
#define kColour_Navy 	0xff000080
#define kColour_DarkBlue 	0xff00008B	 
#define kColour_MediumBlue 	0xff0000CD	 
#define kColour_Blue 	0xff0000FF	 
#define kColour_DarkGreen 	0xff006400	 
#define kColour_Green 	0xff008000	 
#define kColour_Teal 	0xff008080	 
#define kColour_DarkCyan 	0xff008B8B	 
#define kColour_DeepSkyBlue 	0xff00BFFF	 
#define kColour_DarkTurquoise 	0xff00CED1	 
#define kColour_MediumSpringGreen 	0xff00FA9A	 
#define kColour_Lime 	0xff00FF00	 
#define kColour_SpringGreen 	0xff00FF7F	 
#define kColour_Aqua 	0xff00FFFF	 
#define kColour_Cyan 	0xff00FFFF	 
#define kColour_MidnightBlue 	0xff191970	 
#define kColour_DodgerBlue 	0xff1E90FF	 
#define kColour_LightSeaGreen 	0xff20B2AA	 
#define kColour_ForestGreen 	0xff228B22	 
#define kColour_SeaGreen 	0xff2E8B57	 
#define kColour_DarkSlateGray 	0xff2F4F4F	 
#define kColour_LimeGreen 	0xff32CD32	 
#define kColour_MediumSeaGreen 	0xff3CB371	 
#define kColour_Turquoise 	0xff40E0D0	 
#define kColour_RoyalBlue 	0xff4169E1	 
#define kColour_SteelBlue 	0xff4682B4	 
#define kColour_DarkSlateBlue 	0xff483D8B	 
#define kColour_MediumTurquoise 	0xff48D1CC	 
#define kColour_Indigo  	0xff4B0082	 
#define kColour_DarkOliveGreen 	0xff556B2F	 
#define kColour_CadetBlue 	0xff5F9EA0	 
#define kColour_CornflowerBlue 	0xff6495ED	 
#define kColour_MediumAquaMarine 	0xff66CDAA	 
#define kColour_DimGray 	0xff696969	 
#define kColour_SlateBlue 	0xff6A5ACD	 
#define kColour_OliveDrab 	0xff6B8E23	 
#define kColour_SlateGray 	0xff708090	 
#define kColour_LightSlateGray 	0xff778899	 
#define kColour_MediumSlateBlue 	0xff7B68EE	 
#define kColour_LawnGreen 	0xff7CFC00	 
#define kColour_Chartreuse 	0xff7FFF00	 
#define kColour_Aquamarine 	0xff7FFFD4	 
#define kColour_Maroon 	0xff800000	 
#define kColour_Purple 	0xff800080	 
#define kColour_Olive 	0xff808000	 
#define kColour_Gray 	0xff808080	 
#define kColour_SkyBlue 	0xff87CEEB	 
#define kColour_LightSkyBlue 	0xff87CEFA	 
#define kColour_BlueViolet 	0xff8A2BE2	 
#define kColour_DarkRed 	0xff8B0000	 
#define kColour_DarkMagenta 	0xff8B008B	 
#define kColour_SaddleBrown 	0xff8B4513	 
#define kColour_DarkSeaGreen 	0xff8FBC8F	 
#define kColour_LightGreen 	0xff90EE90	 
#define kColour_MediumPurple 	0xff9370DB	 
#define kColour_DarkViolet 	0xff9400D3	 
#define kColour_PaleGreen 	0xff98FB98	 
#define kColour_DarkOrchid 	0xff9932CC	 
#define kColour_YellowGreen 	0xff9ACD32	 
#define kColour_Sienna 	0xffA0522D	 
#define kColour_Brown 	0xffA52A2A	 
#define kColour_DarkGray 	0xffA9A9A9	 
#define kColour_LightBlue 	0xffADD8E6	 
#define kColour_GreenYellow 	0xffADFF2F	 
#define kColour_PaleTurquoise 	0xffAFEEEE	 
#define kColour_LightSteelBlue 	0xffB0C4DE	 
#define kColour_PowderBlue 	0xffB0E0E6	 
#define kColour_FireBrick 	0xffB22222	 
#define kColour_DarkGoldenRod 	0xffB8860B	 
#define kColour_MediumOrchid 	0xffBA55D3	 
#define kColour_RosyBrown 	0xffBC8F8F	 
#define kColour_DarkKhaki 	0xffBDB76B	 
#define kColour_Silver 	0xffC0C0C0	 
#define kColour_MediumVioletRed 	0xffC71585	 
#define kColour_IndianRed  	0xffCD5C5C	 
#define kColour_Peru 	0xffCD853F	 
#define kColour_Chocolate 	0xffD2691E	 
#define kColour_Tan 	0xffD2B48C	 
#define kColour_LightGray 	0xffD3D3D3	 
#define kColour_Thistle 	0xffD8BFD8	 
#define kColour_Orchid 	0xffDA70D6	 
#define kColour_GoldenRod 	0xffDAA520	 
#define kColour_PaleVioletRed 	0xffDB7093	 
#define kColour_Crimson 	0xffDC143C	 
#define kColour_Gainsboro 	0xffDCDCDC	 
#define kColour_Plum 	0xffDDA0DD	 
#define kColour_BurlyWood 	0xffDEB887	 
#define kColour_LightCyan 	0xffE0FFFF	 
#define kColour_Lavender 	0xffE6E6FA	 
#define kColour_DarkSalmon 	0xffE9967A	 
#define kColour_Violet 	0xffEE82EE	 
#define kColour_PaleGoldenRod 	0xffEEE8AA	 
#define kColour_LightCoral 	0xffF08080	 
#define kColour_Khaki 	0xffF0E68C	 
#define kColour_AliceBlue 	0xffF0F8FF	 
#define kColour_HoneyDew 	0xffF0FFF0	 
#define kColour_Azure 	0xffF0FFFF	 
#define kColour_SandyBrown 	0xffF4A460	 
#define kColour_Wheat 	0xffF5DEB3	 
#define kColour_Beige 	0xffF5F5DC	 
#define kColour_WhiteSmoke 	0xffF5F5F5	 
#define kColour_MintCream 	0xffF5FFFA	 
#define kColour_GhostWhite 	0xffF8F8FF	 
#define kColour_Salmon 	0xffFA8072	 
#define kColour_AntiqueWhite 	0xffFAEBD7	 
#define kColour_Linen 	0xffFAF0E6	 
#define kColour_LightGoldenRodYellow 	0xffFAFAD2	 
#define kColour_OldLace 	0xffFDF5E6	 
#define kColour_Red 	0xffFF0000	 
#define kColour_Fuchsia 	0xffFF00FF	 
#define kColour_Magenta 	0xffFF00FF	 
#define kColour_DeepPink 	0xffFF1493	 
#define kColour_OrangeRed 	0xffFF4500	 
#define kColour_Tomato 	0xffFF6347	 
#define kColour_HotPink 	0xffFF69B4	 
#define kColour_Coral 	0xffFF7F50	 
#define kColour_DarkOrange 	0xffFF8C00	 
#define kColour_LightSalmon 	0xffFFA07A	 
#define kColour_Orange 	0xffFFA500	 
#define kColour_LightPink 	0xffFFB6C1	 
#define kColour_Pink 	0xffFFC0CB	 
#define kColour_Gold 	0xffFFD700	 
#define kColour_PeachPuff 	0xffFFDAB9	 
#define kColour_NavajoWhite 	0xffFFDEAD	 
#define kColour_Moccasin 	0xffFFE4B5	 
#define kColour_Bisque 	0xffFFE4C4	 
#define kColour_MistyRose 	0xffFFE4E1	 
#define kColour_BlanchedAlmond 	0xffFFEBCD	 
#define kColour_PapayaWhip 	0xffFFEFD5	 
#define kColour_LavenderBlush 	0xffFFF0F5	 
#define kColour_SeaShell 	0xffFFF5EE	 
#define kColour_Cornsilk 	0xffFFF8DC	 
#define kColour_LemonChiffon 	0xffFFFACD	 
#define kColour_FloralWhite 	0xffFFFAF0	 
#define kColour_Snow 	0xffFFFAFA	 
#define kColour_Yellow 	0xffFFFF00	 
#define kColour_LightYellow 	0xffFFFFE0	 
#define kColour_Ivory 	0xffFFFFF0	 
#define kColour_White 	0xffFFFFFF
#define kColour_White50 0x7fFFFFFF

#define BASEHASH 5315
u32 Hash(const char *inputStr);

#define MAXDELAYS 64
#define kStartingPointsScore 75000

static const u32 kFont_Default = Hash("BuiltInFont");

//Mark: - ENUMERATIONS
enum ErrorCode
{
	kErrorCode_NoError = 0,
	//Engine codes
	kErrorCode_Success = kErrorCode_NoError,
	kErrorCode_Quit,

	kErrorCode_InvalidData = 10,
	kErrorCode_OutOfSpace,
	kErrorCode_BadAllocation,
	kErrorCode_UnknownException,
	kErrorCode_HardFailure,
	KErrorCode_SoftFailure,
	kErrorCode_Duplicate,

	//Web codes
	kErrorCode_RequestComplete = 200,
	kErrorCode_Accepted = 202,
	
	kErrorCode_Moved,
	kErrorCode_MovedTemp,
	kErrorCode_AccessDenied = 303,
	kErrorCode_BadRequest  = 400,
	kErrorCode_Unauthorized,
	kErrorCode_PaymentRequired,
	kErrorCode_Forbidden,
	kErrorCode_NotFound,

	kErrorCode_ServerError = 500,
	kErrorCode_NotImplemented,
	kErrorCode_BadGateWay,
	kErrorCode_OutOfResources,
	kErrorCode_GateWay,
	kErrorCode_HttpVersionNotSupported,

	kErrorCodeTypes_Count
};
#define kSuccess kErrorCode_Success;



#endif // __DEFINES_H__