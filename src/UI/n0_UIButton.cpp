#include "n0/n0.h"

namespace n0
{

UIButton::UIButton(u32 x, u32 y, u32 w, u32 h, UIDecorator *decorator, u32 id ) 
	: UIDecorator(decorator,id) 
{

	m_isDown = false;
	m_isMouseOver = false;
	m_postion.x = x;
	m_postion.y = y;
	m_width = w;
	m_height = h;
	m_anchor.x = w >> 1;
	m_anchor.y = h >> 1;
}

UIButton::~UIButton()
{


}

void UIButton::Draw() 
{
	if(m_decorator) 
		m_decorator->Draw();
	else
		UIObject::Draw();
}

void UIButton::Update(u32 delta) 
{ 

	if(m_decorator)
		m_decorator->Update(delta);
	else
		UIObject::Update(delta);
}

bool UIButton::OnEvent(n0Event *e) 
{ 
	if(!e)
		return kFalse;

	if(m_decorator) 
	{
		return m_decorator->OnEvent(e);
	}

	return kFalse;
}


};