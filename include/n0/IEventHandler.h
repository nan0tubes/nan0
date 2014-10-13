#ifndef __IEVENTHANDLER_H__
#define __IEVENTHANDLER_H__



namespace n0
{

template <u32 MAX_LISTENERS> class IEventHandler
{
	struct Listener
	{
		Callback cb;
		u32 listenerID;
		u32 eventType;
	};
	
private:
	u32 m_numListeners;
	std::array<Listener,MAX_LISTENERS> m_listeners;
	std::queue<n0Event*> m_eventQueue;

public:

	IEventHandler() { m_numListeners = 0;}

	template <class T>
	ErrorCode RegisterEventListener(u32 eventType, T* pObj, bool (T::*cbFunc)(n0Event*), u32 listenerID = 0)
	{
		if(m_numListeners == MAX_LISTENERS )
			return kErrorCode_OutOfSpace;
		if(!listenerID)
			listenerID = (u32)pObj;
		Listener l;
		l.cb.set(*pObj,cbFunc);
		l.eventType =eventType;
		l.listenerID = listenerID;
		m_listeners[m_numListeners++] = l;

		return kErrorCode_Success;
	}

	template <class T>
	ErrorCode DeRegisterEventListener(u32 eventType, T* pObj, bool (T::*cbFunc)(n0Event*), u32 listenerID = 0)
	{
		ErrorCode returnCode = kErrorCode_NotFound;
		if(!listenerID)
			listenerID = (u32)pObj;
		for (u32 i =0 ; i < m_numListeners ; ++i)
		{
			if(m_listeners[i].eventType == eventType)
			{
				if(m_listeners[i].listenerID == listenerID)
				{
					removeAt(m_listeners,i);
					m_numListeners--; i--;
					returnCode = kErrorCode_Success;
				}
			}

		}

		return returnCode;
	}

	bool FireEvent(n0Event *e)
	{
		bool eventHandled = false;
// 		char log[kStrLen_Medium];
// 		e->GetLog(log, kStrLen_Medium);
// 		GetGame()->GetBlackBox()->Log("Event", 0,log);
		
		for (u32 i =0 ; i < m_numListeners && !eventHandled; ++i)
		{
			if(m_listeners[i].eventType == e->m_type)
			{
				Callback &cb = m_listeners[i].cb; 
				eventHandled = cb.call(e);
			}

		}
		return eventHandled;
	}

	template <class n0EventClass>
	void QueueEvent(n0EventClass *e)
	{
		n0EventClass *evt = new n0EventClass(*e);
		std::memcpy(evt,e,sizeof(n0EventClass));
		m_eventQueue.push(evt);
	}

	void ProcessEvents()
	{
		
		while(!m_eventQueue.empty())
		{
			n0Event *evt = m_eventQueue.front();
			FireEvent(evt);
			SAFE_DELETE(evt);
			m_eventQueue.pop();
		}
	}

};


};

#endif // __IEVENTHANDER_H__