
#ifndef __N0_PLATFORM_H__
#define __N0_PLATFORM_H__



#if  defined(_WIN32)
#include "platform/n0_windows.h"


#elif defined(n0_IPHONE)

#include "platform/n0_iphone.h"

#elif define(n0_ANDROID)

#include "platform/n0_android.h"

#endif


#endif