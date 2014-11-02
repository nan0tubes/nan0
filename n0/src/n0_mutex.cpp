

#include "n0/n0.h"

namespace n0
{

#ifdef N0_SIMPLE_MUTEX
n0Mutex *n0Mutex_Create(char * mutexName )
{
	n0Mutex *pMutex = new n0Mutex();
	pMutex->isLocked = kFalse;
	pMutex->name = Hash(mutexName);

	return pMutex;
}
void n0Mutex_Destroy(n0Mutex *pMutex)
{
	delete pMutex;
}
void n0Mutex_Lock(n0Mutex *pMutex)
{
	while(pMutex->isLocked)
		Sleep(100);

}
inline bool n0Mutex_IsLocked(n0Mutex *pMutex)
{
	return pMutex->isLocked;

}
void n0Mutex_Unlock(n0Mutex *pMutex)
{
	pMutex->isLocked = kFalse;
}
bool n0Mutex_TryLock(n0Mutex *pMutex)
{
	if(pMutex->isLocked)
		return kFalse;
	return pMutex->isLocked = kTrue;
}

#else

n0Mutex *n0Mutex_Create(char * mutexName )
{
	return NULL;
}
void n0Mutex_Destroy(n0Mutex *pMutex) { }
void n0Mutex_Lock(n0Mutex *pMutex) { }
bool n0Mutex_IsLocked(n0Mutex *pMutex) { return kFalse; }
void n0Mutex_Unlock(n0Mutex *pMutex) { }
bool n0Mutex_TryLock(n0Mutex *pMutex) { return kFalse;}

#endif


};