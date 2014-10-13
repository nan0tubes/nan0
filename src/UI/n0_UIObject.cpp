
#include "n0/n0.h"

namespace n0
{

UIObject::UIObject() 
{ 
	memzero(this,sizeof(UIObject));
	m_UID = (u32)-1;
	m_visible = kTrue;
	m_width = 100;
	m_height = 100;
		
}

UIObject::UIObject(u32 id)
{
	memzero(this,sizeof(UIObject));
	m_UID = id;
	m_visible = kTrue;
	m_width = 100;
	m_height = 100;
}

void UIObject::Draw()
{
	if(!m_visible)
		return;

	for(u32 it = 0;it < m_numChildren ; it++)
	{

		if(m_children[it])
		{
			m_children[it]->Draw();
		}
	}

}

void UIObject::Update(u32 delta) 
{ 

	for(u32 it = 0;it < m_numChildren ; it++)
	{
		if(m_children[it])
		{
			m_children[it]->SetParentPosition(GetWorldPostion());
			m_children[it]->Update(delta);
		}
	}

	IEventHandler::ProcessEvents(); 
	//After update processing, sort for depth

}

bool UIObject::OnEvent(n0Event *)
{
	
	return kFalse;
}


bool UIObject::AddChild(UIObject * child) 
{
	n0_ASSERT(child, "NULL POINTER SEND TO UIObject::AddChild");
	if(!child)
		return kFalse;
	n0_ASSERT(m_numChildren < kMaxNumChildren, "ADDING too many children to this object");
	if(m_numChildren >= kMaxNumChildren)
		return kFalse;
	m_children[m_numChildren++] = child;
	child->SetParentPosition(GetWorldPostion());
	return kTrue;
}

// Returns Removed Child on success, NULL on failure;
UIObject * UIObject::RemoveChild(UIObject * child)
{
	n0_ASSERT(child, "Attempting to Remove null pointer from children");
	if(!child)
		return NULL;
	UIObject * ret = NULL;

	for(u32 it = 0;it < m_numChildren ; it++)
	{
		if(m_children[it] == child)
		{
			ret = child;
			m_children.removeAt(it);
			ret->SetParentPosition(0,0);
			break;
		}
	}

	return ret;
}

UIObject * UIObject::RemoveChild(u32 childID)
{
	n0_ASSERT(childID != (u32)-1, "INVALID CHILD ID TO REMOVE");
	if(childID == -1)
		return NULL;
	UIObject * ret = NULL;


	for(u32 it = 0;it < m_numChildren ; it++)
	{
		if(m_children[it]->GetID() == childID)
		{
			ret = m_children[it];
			m_children.removeAt(it);
			ret->SetParentPosition(0,0);
			break;
		}
	}

	return ret;
}

UIObject::~UIObject()  
{
	for(u32 it = 0;it < m_numChildren ; it++)
	{
		SAFE_DELETE(m_children[it]);
	}
	m_numChildren = NULL;

}




};