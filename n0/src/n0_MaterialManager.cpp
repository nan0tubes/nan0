#include "n0/n0.h"

namespace n0
{
	n0MaterialManager* s_instance = NULL;
	n0MaterialManager::n0MaterialManager() 
	{
		
	}

	n0MaterialManager::~n0MaterialManager()
	{
		std::vector<n0Material *>::iterator it;

		for(it = m_MaterialArray.begin(); it != m_MaterialArray.end() ; it++)
		{
			(*it)->Drop();
		}
		m_MaterialArray.clear();
	}
	n0MaterialManager * n0MaterialManager::GetInstance()
	{
		if(!s_instance)
		{
			s_instance = new n0MaterialManager();
		}

		n0_ASSERT(s_instance, "material manager instance is NULL!");
		return s_instance;
	}
	void n0MaterialManager::DestroyInstance()
	{
		n0_ASSERT(s_instance, "material manager instance is NULL!");
		SAFE_DELETE(s_instance);
	}

	n0Material * n0MaterialManager::GetMaterial(u32 matID)
	{
		std::vector<n0Material *>::iterator it;

		for(it = m_MaterialArray.begin(); it != m_MaterialArray.end() ; it++)
		{
			if((*it)->materialName == matID)
			{
				return *it;
			}
		}

		return NULL;
	}
	void n0MaterialManager::AddMaterial(n0Material* _mat)
	{
		if(!GetMaterial(_mat->materialName))
			m_MaterialArray.push_back(_mat);
	}


}