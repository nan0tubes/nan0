#ifndef __N0_TEXTUREMANAGER_H__
#define __N0_TEXTUREMANAGER_H__


namespace n0
{
	const vec2i TEXTURE_DIMS_SMALL = vec2i(512,512);
	const vec2i TEXTURE_DIMS_NORMAL = vec2i(1024,1024);
	const vec2i TEXTURE_DIMS_LONG = vec2i(2048,1024);
	const vec2i TEXTURE_DIMS_DOUBLE = vec2i(2048,2048);
	const vec2i TEXTURE_DIMS_DOUBLELONG = vec2i(4096,2048);
	const vec2i TEXTURE_DIMS_4K = vec2i(4096,4096);

	class n0TextureManager
	{
	private:
		n0TextureManager();

		std::vector<n0Texture *> m_TextureArray;
	public:
		~n0TextureManager();
		static n0TextureManager * GetInstance();
		static void DestroyInstance();

		n0Texture * GetTexture(u32 texID);

		n0Texture * GenerateTexture(u32 texID, u32 width, u32 height);
	};
}



#endif __N0_TEXTUREMANAGER_H__