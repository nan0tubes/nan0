#include "n0/n0.h"

namespace n0
{


u32 n0Scene::s_sceneID = Hash("Default Scene"); 

n0Scene::n0Scene(u32 sceneName)
	: m_sceneName(sceneName)
{
	
	m_bAlive = false;
}

n0Scene::~n0Scene()
{
	if(m_bAlive)
	{
		CleanUp();
	}
}

bool n0Scene::Init()
{
	
	//SSceneEvent dEvent(SSceneEvent::kEvent_SceneCreated,this->GetSceneType(),this);
	return true;
}

void n0Scene::CleanUp()
{
	m_bAlive = false;
}

void n0Scene::Update(unsigned int delta)
{

	//printf("Scene: %u: I am updating!\n",(unsigned int)this);
	std::list<IUpdateable*>::iterator it = m_UpdateStack.begin();
	for(; it != m_UpdateStack.end(); ++it)
	{
		(*it)->Update(delta);
	}

	IEventHandler::ProcessEvents();
}
void n0Scene::Draw()
{
	//printf("Scene: %u: I am Drawering!\n",(unsigned int)this);

}




};