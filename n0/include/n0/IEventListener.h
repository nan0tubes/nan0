
#ifndef FW_IEVENTLISTENER
#define FW_IEVENTLISTENER

class IEventListener
{

public:
	virtual bool OnEvent(Event *) = 0;
};


#endif