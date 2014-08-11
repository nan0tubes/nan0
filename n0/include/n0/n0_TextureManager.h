

namespace n0
{

	class n0TextureManager
	{
	private:
		n0TextureManager();

		std::vector<n0Texture *> m_TextureArray();
	public:
		~n0TextureManager();
		static n0TextureManager * GetInstance();

		n0Texture * GetTexture(u32 texID);
	};
}