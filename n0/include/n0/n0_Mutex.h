
#ifdef FW_SIMPLE_MUTEX

struct fwMutex 
{
	bool isLocked;
	u32 name;	
};

#else

struct fwMutex 
{
	//Semaphores
	u32 name;	
};

#endif


fwMutex *fwMutex_Create(char * mutexName );
void fwMutex_Destroy(fwMutex *pMutex);
void fwMutex_Lock(fwMutex *pMutex);
bool fwMutex_IsLocked(fwMutex *pMutex);
void fwMutex_Unlock(fwMutex *pMutex);
bool fwMutex_TryLock(fwMutex *pMutex);