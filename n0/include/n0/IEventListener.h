
#ifndef FW_IEVENTLISTENER
#define FW_IEVENTLISTENER


namespace n0
{

class IEventListener
{

public:
	virtual bool OnEvent(n0Event *) = 0;
};


};


#endif