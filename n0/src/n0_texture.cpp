#include "n0/n0.h"


namespace n0
{


n0Texture::n0Texture(u32 texID, u32 texWidth, u32 texHeight, u32 bpp, u32 colorspace)
	:width(texWidth), height(texHeight), textureID(texID), bpp(bpp), colorspace(colorspace)
{
	glGenTextures(1,&glID);
	glBindTexture(GL_TEXTURE_2D, glID);

	
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, 0);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); // Linear Filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); // Linear Filtering

	n0_FlushGLError();
}

}