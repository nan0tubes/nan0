#include "n0/n0.h"

static n0_RefManager * g_refManager = NULL;
n0_RefCounted::n0_RefCounted() 
{
#ifdef _DEBUG
	wasDestroyed = false;
#endif
	_count = 1;
}
void n0_RefCounted::Drop()
{
#ifdef _DEBUG
	n0_ASSERT(!wasDestroyed,"Object was Already Destroyed!");
#endif
	n0_ASSERT(_count > 0,"Reference Dropped when lower than 1.");

	--_count;

	if(_count == 0)
	{
		n0_RefManager::GetInstance()->RegisterForDelete(this);
	}
}

void n0_RefCounted::Retain()
{
#ifdef _DEBUG
	n0_ASSERT(!wasDestroyed,"Object was Already Destroyed!");
#endif
	n0_ASSERT( _count > 0 ,"Retaining a Object at count 0, this object should get destroyed")
	++_count;
}



n0_RefManager::n0_RefManager()
{


}
n0_RefManager::~n0_RefManager()
{
	Purge();

}

void n0_RefManager::RegisterForDelete(n0_RefCounted *_object)
{
#ifdef _DEBUG
	memset(_object,0xc,sizeof(n0_RefCounted));
	_object->wasDestroyed = true;
#endif
	m_objects.push_back(_object);
}

void n0_RefManager::Purge()
{

#ifdef _DEBUG
	m_oldObjects.insert(m_oldObjects.end(),m_objects.begin(),m_objects.end());
#else
	std::vector<n0_RefCounted*>::iterator it = m_objects.begin();
	for(;it !=m_objects.end(); it++)
	{
		delete (*it);
	}
#endif
	m_objects.clear();
}

n0_RefManager * n0_RefManager::GetInstance()
{
	if(g_refManager == NULL)
	{
		g_refManager = new n0_RefManager();
	}
	return g_refManager;
}