#ifndef __EVENTS_H__
#define __EVENTS_H__


namespace n0
{

struct n0Event 
{
	void *pData;
	u32 m_type;

	virtual void GetLog(char *buf, u32 maxLen) { snprintf(buf, maxLen, "Type: %u, pData: %p", m_type, pData); }
	n0Event(u32 type, void *data = 0) : pData(data),m_type(type) {} ;
	enum EEventType{ Event_NoEvent = 0, Event_DefaultEvent, Event_DelayCallback};
};

class CallbackSpecBase
{
public:
	virtual ~CallbackSpecBase() {}
	virtual bool operator()(n0Event*) const = 0;
};

template<class C, class T>
class CallbackSpec : public CallbackSpecBase
{
public:
	CallbackSpec(C& o, T m) : obj(o), method(m) {}
	bool operator()(n0Event* evt) const { return (&obj->*method)(evt); } // how to pass "..." into method(...)

private:
	C& obj;
	T method;
};

// PUBLIC API

class Callback
{
public:
	Callback() {}
	template<class C, class T>
	Callback(C& o, T m) { spec.reset(new CallbackSpec<C, T>(o, m)); }
	

	template<class C, class T>
	void set(C& o, T m) { spec.reset(new CallbackSpec<C, T>(o, m)); }
	bool call(n0Event *evt) { return (*spec)(evt); }

private:
	std::auto_ptr<CallbackSpecBase> spec;
};


//KeyEvent is just an example of the event design, key events are actually processed by irrlicht in most cases
struct SKeyEvent : public n0Event
{
	u32 m_keyCode;

	virtual void GetLog(char *buf, u32 maxLen) { snprintf(buf, maxLen, "Type: %u, Key %u, pData: %p", m_type, m_keyCode, pData); }
	SKeyEvent(u32 type, u32 keyCode, void *data =0 ) : n0Event(type,data), m_keyCode(keyCode) {}
	enum EKeyEvent{ kEvent_KeyDown = 100,kEvent_KeyUp, kEvent_KeyRepeat, kEvent_KeyCount};
};


struct SMouseEventData 
{
	int x;
	int y;
};
struct SMouseEvent : public n0Event
{
	
	virtual void GetLog(char *buf, u32 maxLen) { snprintf(buf, maxLen, "Type: %u, pData: %i %i", m_type, ((SMouseEventData*)pData)->x,((SMouseEventData*)pData)->y); }
	SMouseEvent(u32 type, void *data =0 ) : n0Event(type,data) {}
	enum EMouseEvent{ kEvent_LeftMBDown = 200,kEvent_LeftMBUp, kEvent_RightMBDown, kEvent_RightMBUp,kEvent_MiddleMBDown,kEvent_MiddleMBUp, kEvent_MouseMove};

};

struct STouchEvent : public n0Event
{

};

// struct SInputEvent : public n0Event
// {
// 	virtual void GetLog(char *buf, u32 maxLen) { snprintf(buf, maxLen, "Type: %u, pData: %p", m_type, pData); }
// 	SInputEvent(u32 type, void *data = 0) : n0Event(type, data) { }
// 	enum EInputEventType {
// 		kEvent_Input_First = 200,
// 		kEvent_InputLeft_Down = kEvent_Input_First, kEvent_InputLeft_Up,
// 		kEvent_InputRight_Down, kEvent_InputRight_Up,
// 		kEvent_InputUp_Down, kEvent_InputUp_Up,
// 		kEvent_InputDown_Down, kEvent_InputDown_Up,
// 		kEvent_InputA1_Down, kEvent_InputA1_Up,
// 		kEvent_InputA2_Down, kEvent_InputA2_Up,
// 		kEvent_InputA3_Down, kEvent_InputA3_Up,
// 		kEvent_InputA4_Down, kEvent_InputA4_Up,
// 		kEvent_InputA5_Down, kEvent_InputA5_Up,
// 		kEvent_InputA6_Down, kEvent_InputA6_Up,
// 		kEvent_InputReset_Down, kEvent_InputReset_Up,
// 		kEvent_InputQuit_Down, kEvent_InputQuit_Up,
// 
// 		kEvent_InputType_Count
// 	};
// };

struct SSceneEvent : public n0Event
{
	u32 sceneID;
	virtual void GetLog(char *buf, u32 maxLen) { snprintf(buf, maxLen, "Type: %u, ID: %u, pData: %p", m_type, sceneID, pData); }
	SSceneEvent(u32 type, u32 id, void *data = 0):n0Event(type,data),sceneID(id) {}
	enum ESceneEvent
	{
		kEvent_SceneCreated = 1000,
		kEvent_SceneShowing,
		kEvent_SceneUpdating,
		kEvent_SceneEndShowing,
		kEvent_SceneEndUpdating,
		kEvent_SceneDestroyed,
		kEvent_SceneCount,

		kEvent_SceneType_Count
	};
};

// 
// struct SGUIEvent : n0Event
// {
// 	u32 sceneID;
// 	virtual void GetLog(char *buf, u32 maxLen) { snprintf(buf, maxLen, "Type: %u, ID: %u, pData: %p", m_type, sceneID, pData); }
// 	SGUIEvent(u32 type, u32 id, void *data = 0) : n0Event(type, data),sceneID(id) { }
// 	enum EGUIEventType {
// 		kEvent_GUI_First = 400,
// 		kEvent_GUI_ButtonClicked = kEvent_GUI_First,
// 
// 		kEvent_GUIType_Count
// 	};
// };
// 
// struct SAchievementEvent : n0Event
// {
// 	u32 m_id;
// 	u32 m_value;
// 	virtual void GetLog(char *buf, u32 maxLen) { snprintf(buf, maxLen, "Type: %u, ID: %u, Val: %u,  pData: %p", m_type, m_id, m_value, pData); }
// 	SAchievementEvent(u32 type, u32 id, u32 val, void *data = 0) : n0Event(type, data), m_id(id), m_value(val) { }
// 	enum EAchievementType {
// 		kEvent_Achievement_GameNotification = 500,
// 		kEvent_Achievement_AchievementProgress,
// 		kEvent_Achievement_AchievementComplete,
// 
// 		kEvent_AchievementType_Count
// 	};
// };
// 

};

#endif //__EVENTS_H__