
#ifndef __N0_PLATFORM_H__
#define __N0_PLATFORM_H__

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <queue>
#include <list>
#include <map>
#include <vector>
#include <array>
#include <iostream>
#include <fstream>

#if  defined(_WIN32)
#include "platform/n0_windows.h"


#elif defined(n0_IPHONE)

#include "platform/n0_iphone.h"

#elif define(n0_ANDROID)

#include "platform/n0_android.h"

#endif


#endif