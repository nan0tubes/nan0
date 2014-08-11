#ifndef __N0_INPUTEVENTS_H__
#define __N0_INPUTEVENTS_H__

namespace n0
{


class n0InputEvents : IEventHandler<128>  , IEventListener 
{
	struct InputEvent{
		u32 triggerID;
		u32 triggerVal;
		u32 eventName;
		void *data;
	};


	std::vector<InputEvent> m_triggerEvents;

public:
	n0InputEvents();
	virtual ~n0InputEvents();

public:
	virtual bool OnEvent(n0Event *) = 0;

	virtual void RegisterInputEvent( unsigned int tiggerEventID, unsigned int triggerEventData,char *eventName, void *pUserData);

};





} // Namespace n0


#endif //__N0_INPUTEVENTS_H__