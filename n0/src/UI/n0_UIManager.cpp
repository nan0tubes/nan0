
#include "n0/n0.h"

namespace n0
{

const u32 UIManager::s_type = Hash("UIManager");


UIManager::UIManager()
{
	n0InputEvents::GetInstance()->RegisterEventListener(Hash("MouseMove"),this,&UIManager::OnEvent,s_type);

}

UIManager * UIManager:: s_Instance = NULL;
UIManager * UIManager::GetInstance()
{
	if(!s_Instance)
	{
		s_Instance = new UIManager();
	}
	n0_ASSERT(s_Instance != NULL,"UI Manager Instance was NULL!");
	return s_Instance;
}
void UIManager::TearDown()
{

	n0_ASSERT(s_Instance != NULL,"UI Manager Instance was NULL!");
	delete s_Instance;
}


UIButton * UIManager::CreateUIButton( u32 ID, u32 x, u32 y, u32 w, u32 h,  u32 parent )
{

	return NULL;
}

UIWindow * UIManager::CreateUIWindow( u32 ID, u32 x, u32 y, u32 w, u32 h, u32 parent )
{

	return NULL;
}

UIObject * UIManager::CreateUINode( u32 ID, u32 x, u32 y, u32 parent )
{
	return NULL;
}

void UIManager::Draw()
{

}
void UIManager::Update(u32 delta)
{

}
bool UIManager::OnEvent(n0Event *evt)
{
	return false;
}

};