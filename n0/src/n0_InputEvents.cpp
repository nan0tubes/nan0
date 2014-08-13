#include "n0/n0.h"

namespace n0
{
n0InputEvents * n0InputEvents::s_Instance = NULL;


n0InputEvents * n0InputEvents::GetInstance()
{
	if(s_Instance == NULL)
	{
		s_Instance = new n0InputEvents();
	}

	ASSERT(s_Instance != NULL);

	return s_Instance;

}

void n0InputEvents::DestroyInstance()
{
	ASSERT(s_Instance != NULL);
	delete s_Instance;

}

n0InputEvents::n0InputEvents()
{


}
n0InputEvents::~n0InputEvents()
{


}

bool n0InputEvents::OnEvent(n0Event *_evt)
{
	bool didHandle = false;

	std::vector<InputEvent>::iterator it;
	for(it = m_triggerEvents.begin(); it != m_triggerEvents.end(); it++)
	{
		if(_evt->m_type = it->triggerID)
		{
			n0Event evt(it->eventName,it->data != NULL ? it->data : _evt->pData);
			FireEvent(&evt);
		}

	}
	
	return didHandle;
}

void n0InputEvents::RegisterInputEvent( unsigned int triggerEventID, unsigned int triggerEventData,char *eventName, void *pUserData)
{
	InputEvent iEvent;
	iEvent.data = pUserData;
	iEvent.eventName = Hash(eventName);
	iEvent.triggerID  = triggerEventID;
	iEvent.triggerVal = triggerEventData;

	m_triggerEvents.push_back(iEvent);

}



}