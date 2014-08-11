#include "n0/n0.h"

namespace n0
{


n0InputEvents::n0InputEvents()
{


}
n0InputEvents::~n0InputEvents()
{


}

bool n0InputEvents::OnEvent(n0Event *evt)
{
	bool didHandle = false;

	std::vector<InputEvent>::iterator it;
	for(it = m_triggerEvents.begin(); it != m_triggerEvents.end(); it++)
	{
		if(evt->m_type = it->triggerID)
		{

		}

	}
	
	return didHandle;
}

void n0InputEvents::RegisterInputEvent( unsigned int tiggerEventID, unsigned int triggerEventData,char *eventName, void *pUserData)
{


}



}