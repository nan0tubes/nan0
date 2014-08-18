

namespace n0
{
	class n0Texture : public n0RefCounted
	{
		friend class n0TextureManager;
		u32 textureID;
		u32 width;
		u32 height;
		u32 bpp;
		u32 colorspace;
		u32 glID;
	private:
		n0Texture() {}
		~n0Texture() {}
		n0Texture(u32 texID, u32 texWidth, u32 texHeight, u32 bpp, u32 colorspace);
	};
}