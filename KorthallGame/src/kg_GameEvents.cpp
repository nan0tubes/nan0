#include "global.h"

GameEvents::GameEvents()
{

	n0::n0InputEvents::GetInstance()->RegisterInputEvent(n0::SMouseEvent::kEvent_LeftMBDown,0,"TargetClick",NULL);
	n0::n0InputEvents::GetInstance()->RegisterInputEvent(n0::SMouseEvent::kEvent_MouseMove,0,"Mmove",NULL);
	n0::n0InputEvents::GetInstance()->RegisterInputEvent(n0::SKeyEvent::kEvent_KeyDown,'E',"theE",NULL);
	n0::n0InputEvents::GetInstance()->RegisterEventListener(Hash("TargetClick"),this,&GameEvents::OnMouseEvent,Hash("fixMeClickEvent"));
	n0::n0InputEvents::GetInstance()->RegisterEventListener(Hash("theE"),this,&GameEvents::OnKeyEvent,Hash("fixMeKeyEvent"));
	n0::n0InputEvents::GetInstance()->RegisterEventListener(Hash("Mmove"),this,&GameEvents::OnMouseMoveEvent,Hash("mouseMoveEvent"));
}

GameEvents::~GameEvents()
{

	n0::n0InputEvents::GetInstance()->DeRegisterInputEvent("TargetClick");
	n0::n0InputEvents::GetInstance()->DeRegisterInputEvent("Mmove");
	n0::n0InputEvents::GetInstance()->DeRegisterInputEvent("theE");
	n0::n0InputEvents::GetInstance()->DeRegisterEventListener(Hash("TargetClick"),this,&GameEvents::OnMouseEvent,Hash("fixMeClickEvent"));
	n0::n0InputEvents::GetInstance()->DeRegisterEventListener(Hash("theE"),this,&GameEvents::OnKeyEvent,Hash("fixMeKeyEvent"));
	n0::n0InputEvents::GetInstance()->DeRegisterEventListener(Hash("Mmove"),this,&GameEvents::OnMouseMoveEvent,Hash("mouseMoveEvent"));

}

bool GameEvents::OnEvent(n0::n0Event *evt)
{
	return false;
}
bool GameEvents::OnMouseEvent(n0::n0Event *_evt) 
{
	n0_ASSERT(Hash("TargetClick") == _evt->m_type, "Events are not appearing as they should (OnMouseEvent)");
	n0::SMouseEvent * pEvt = (n0::SMouseEvent *)_evt;
	n0::SMouseEventData * pEvtData = (n0::SMouseEventData *)pEvt->pData;
	printf("Mouse Click at %d,%d\n",pEvtData->x, pEvtData->y);
	return true;
}
bool GameEvents::OnKeyEvent(n0::n0Event *_evt) 
{
	n0_ASSERT(Hash("theE") == _evt->m_type, "Events are not appearing as they should (OnKeyEvent)");

	printf("E Pressed \n");
	return true;
}
bool GameEvents::OnMouseMoveEvent(n0::n0Event *_evt)
{

	n0_ASSERT(Hash("Mmove") == _evt->m_type, "Events are not appearing as they should (OnKeyEvent)");
	n0::SMouseEvent * pEvt = (n0::SMouseEvent *)_evt;
	n0::SMouseEventData * pEvtData = (n0::SMouseEventData *)pEvt->pData;
	printf("Mouse moved to %d,%d\n",pEvtData->x, pEvtData->y);

	return true;
}