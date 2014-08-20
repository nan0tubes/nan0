#ifndef __N0_MATERIAL_MANAGER_H__
#define __N0_MATERIAL_MANAGER_H__

namespace n0
{

	class n0MaterialManager
	{
	private:
		n0MaterialManager();

		std::vector<n0Material *> m_MaterialArray;
	public:
		~n0MaterialManager();
		static n0MaterialManager * GetInstance();
		static void DestroyInstance();

		n0Material * GetMaterial(u32 matID);
		void AddMaterial(n0Material* _mat);

	};


}

#endif __N0_MATERIAL_MANAGER_H__