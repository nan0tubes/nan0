#ifndef __DELAYTIMER_H__
#define __DELAYTIMER_H__

template <u32 _MAX_DELAYS>
class fwDelayTimer: public IUpdateable
{
	struct SDelay
	{
		u32 timeRemaining; //ms
		u32 skip;
		u32 expired;
		u32 obj;
		u32 delayID;
		void *pUserData;
		Callback cb;
		SDelay():timeRemaining(0),delayID(0),expired(0),skip(0),pUserData(NULL) {}
	};
private:
	fwArray<SDelay,_MAX_DELAYS> m_delays;

public:
	fwDelayTimer()
	{
		memzero(&m_delays, sizeof(SDelay) * _MAX_DELAYS );
		for(u32 i = 0 ; i < _MAX_DELAYS ; i++)
		{
			m_delays[i].expired = kTrue;
		}
	};
	virtual ~fwDelayTimer() {};

	void Update(u32 delta)
	{
		for(u32 i = 0; i < _MAX_DELAYS ; i++)
		{
			if(m_delays[i].expired)
			{
				continue;
			}
			if(m_delays[i].skip)
			{
				m_delays[i].skip--;
				continue;
			}
			if(m_delays[i].timeRemaining < delta)
			{
				Event evt(Event::Event_DelayCallback,m_delays[i].pUserData);
				m_delays[i].cb.call(&evt);
				m_delays[i].expired = 1;
				m_delays[i].delayID = 0;
				m_delays[i].pUserData = NULL;
				continue;
			}
			m_delays[i].timeRemaining -= delta;
		}

	}

	template <class T>
	ErrorCode AddDelay(u32 ms, T* pObj, bool (T::*cbFunc)(Event*), u32 delayID = 0, void *pUserData = NULL)
	{
		if(!delayID)
			delayID = (u32)pObj;
		SDelay d;
		d.expired = 0;
		d.skip = 1;
		d.obj = u32(pObj);
		d.timeRemaining = ms;
		d.delayID = delayID;
		d.cb.set(*pObj,cbFunc);
		d.pUserData = pUserData;
#ifdef DEBUG
		for(u32 i = 0 ; i < _MAX_DELAYS ; i++)
		{
			if(m_delays[i].expired)
				continue;
			if(m_delays[i].delayID == delayID)
			{
				return kErrorCode_Duplicate;
			}
		}
#endif
		for(u32 i = 0 ; i < _MAX_DELAYS ; i++)
		{
			if(m_delays[i].expired)
			{
				m_delays[i] = d;
				return kErrorCode_Success;
			}
		}
		return kErrorCode_OutOfSpace;
	}
	ErrorCode RemoveDelay(u32 delayID)
	{
		if(!delayID)
			return kErrorCode_InvalidData;

		ErrorCode ret = kErrorCode_NotFound;
		
		for(u32 i = 0; i < _MAX_DELAYS ; i++)
		{
			if(m_delays[i].delayID == delayID)
			{
				m_delays[i].expired = kTrue;
				m_delays[i].delayID = 0;
				m_delays[i].pUserData = NULL;
				ret = kErrorCode_Success;
			}
		}
		return ret;
	}

	template <class T>
	ErrorCode RemoveDelay( T* pObj)
	{
		if(!pObj)
			return kErrorCode_InvalidData;

		ErrorCode ret = kErrorCode_NotFound;

		for(u32 i = 0; i < _MAX_DELAYS ; i++)
		{
			if(m_delays[i].obj == (u32)pObj)
			{
				m_delays[i].expired = kTrue;
				m_delays[i].delayID = 0;
				m_delays[i].pUserData = NULL;
				ret = kErrorCode_Success;
			}
			else if(m_delays[i].pUserData == pObj)
			{
				m_delays[i].expired = kTrue;
				m_delays[i].delayID = 0;
				m_delays[i].pUserData = NULL;
				ret = kErrorCode_Success;
			}
		}
		return ret;
	}

};


#endif __DELAYTIMER_H__