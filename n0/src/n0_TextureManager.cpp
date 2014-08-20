#include "n0/n0.h"

namespace n0
{

n0TextureManager::n0TextureManager() {}

n0TextureManager::~n0TextureManager()
{
	std::vector<n0Texture *>::iterator it;

	for(it = m_TextureArray.begin(); it != m_TextureArray.end() ; it++)
	{
		(*it)->Drop();
	}
	m_TextureArray.clear();
}
static n0TextureManager * s_instance = NULL;
n0TextureManager * n0TextureManager::GetInstance()
{
	if(!s_instance)
	{
		s_instance = new n0TextureManager();
	}
	return s_instance;
}
void n0TextureManager::DestroyInstance()
{

	n0_ASSERT(s_instance, "Texture manager instance is NULL!");
	SAFE_DELETE(s_instance);
}

n0Texture * n0TextureManager::GetTexture(u32 texID)
{
	std::vector<n0Texture *>::iterator it;

	for(it = m_TextureArray.begin(); it != m_TextureArray.end() ; it++)
	{
		if((*it)->textureID == texID)
		{
			return *it;
		}
	}

	return NULL;
}

n0Texture * n0TextureManager::GenerateTexture(u32 texID, u32 width, u32 height)
{
	if(GetTexture(texID))
	{
		return GetTexture(texID);
	}
	else
	{
		n0Texture * newTex = new n0Texture(texID,width,height,24,GL_RGBA);
		m_TextureArray.push_back(newTex);
		return GetTexture(texID);

	}
}


}