#ifndef __N0_INPUTEVENTS_H__
#define __N0_INPUTEVENTS_H__

namespace n0
{


class n0InputEvents : public IEventHandler<128>  , public IEventListener 
{
	struct InputEvent{
		u32 triggerID;
		u32 triggerVal;
		u32 eventName;
		void *data;
	};


	std::vector<InputEvent> m_triggerEvents;

private:
	n0InputEvents();
	virtual ~n0InputEvents();
	static n0InputEvents *s_Instance;
public:
	virtual bool OnEvent(n0Event *);

	virtual void RegisterInputEvent( unsigned int triggerEventID, unsigned int triggerEventData,char *eventName, void *pUserData);
	virtual void DeRegisterInputEvent( char *eventName );


static n0InputEvents * GetInstance();
static void DestroyInstance();
};





} // Namespace n0


#endif //__N0_INPUTEVENTS_H__