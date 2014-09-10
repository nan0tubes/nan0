
#ifndef __N0_MUTEX_H__
#define __N0_MUTEX_H__

namespace n0
{

#ifdef N0_SIMPLE_MUTEX



struct n0Mutex 
{
	bool isLocked;
	u32 name;	
};

#else

struct n0Mutex 
{
	//Semaphores
	u32 name;	
};

#endif


n0Mutex *n0Mutex_Create(char * mutexName );
void n0Mutex_Destroy(n0Mutex *pMutex);
void n0Mutex_Lock(n0Mutex *pMutex);
bool n0Mutex_IsLocked(n0Mutex *pMutex);
void n0Mutex_Unlock(n0Mutex *pMutex);
bool n0Mutex_TryLock(n0Mutex *pMutex);


};

#endif