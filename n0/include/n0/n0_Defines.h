#ifndef __DEFINES_H__
#define __DEFINES_H__

//Mark: - MACROS
#define ASSERT(cond) assert((cond))
#define n0_ASSERT(cond, output, ...) { if(!(cond)) { printf("ASSERT: %s:%d ( %s )\n",__FILE__,__LINE__,__FUNCTION__); printf(output, ##__VA_ARGS__); ASSERT((cond)); } }
#define n0_MALLOC(sz) malloc(sz)
#define n0_FREE(pData) { if(pData) { free(pData); } }
#ifdef nullptr
	#define NULL nullptr
#elif defined null
	#define NULL null
#else
	#define NULL 0
#endif

#define n0_FlushGLError() { u32 err; while(err = glGetError()) { printf("GL ERROR #%d - %s:%d",err,__FILE__,__LINE__); }; }

#define NEW new
#define SAFE_DELETE(p) { if (p) delete (p); p = NULL; }
#define SWAP(x, y) { x ^= y; y ^= x; x ^= y; }
template <typename T> T CLAMP(const T& value, const T& low, const T& high) { return value < low ? low : (value > high ? high : value); }

#if defined(_MSC_VER)
	#if !defined(snprintf)
		#define snprintf sprintf_s
	#endif
//	#if !defined(strncpy)
//		#define strncpy strncpy_s
//	#endif
#endif

#define memzero(ptr, sz) { n0_ASSERT((ptr) != NULL, "trying to memzero NULL");  memset((ptr),0,(sz)); }

//Mark: - CONSTANTS
#define kTrue 1
#define kFalse 0

#define PI			3.14159265359f
#define PI_HALF		PI / 2.0f
#define PIE_TWO		PI * 2.0f
#define DEGTORAD	PI / 180.0f
#define RADTODEG	180.0f / PI

inline f32 RadToDeg(f32 rad) { return RADTODEG * rad; }
inline f32 DegToRad(f32 deg) { return DEGTORAD * deg; }

#define PI64		3.1415926535897932384626433832795028841971693993751
#define PI64_HALF	PI64 / 2.0
#define PI64_TWO	PI64 * 2.0
#define DEGTORAD64	PI64 / 180.0
#define RADTODEG64	180.0 / PI64

inline f64 RadToDeg(f64 rad) { return RADTODEG64 * rad; }
inline f64 DegToRad(f64 deg) { return DEGTORAD64 * deg; }

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