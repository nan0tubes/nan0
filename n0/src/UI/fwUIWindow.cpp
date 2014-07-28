#include "n0/n0.h"

namespace n0
{

UIWindow::UIWindow(u32 x, u32 y, u32 w, u32 h, UIDecorator *decorator, u32 id)
	:UIDecorator(decorator,id) 
{
	//m_pTexture = NULL;
	m_postion.X = x;
	m_postion.Y = y;
	m_width = w;
	m_height = h;
	m_anchor.X = w >> 1;
	m_anchor.Y = h >> 1;

}
UIWindow::~UIWindow()
{

}

void UIWindow::Draw() 
{ 
	

	if(m_decorator) 
		m_decorator->Draw();
	else
		UIObject::Draw();
}

void UIWindow::Update(u32 delta) 
{ 
	if(m_decorator) 
		m_decorator->Update(delta);
	else
		UIObject::Update(delta);
}

bool UIWindow::OnEvent(n0Event *e) 
{
	if(m_decorator) 
	{
		if(m_decorator->OnEvent(e))
		{
			return true;
		}
	}

	return kFalse;
}


};