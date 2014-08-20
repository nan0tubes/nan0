#include "n0/n0.h"


namespace n0
{

	void Pow2(u32 &val) // Convert Val to power of 2
	{
		u32 i = 0;
		while(val > (u32)1<<i)
		{
			i++;
		}
		val = 1<<i;
	}
#define SWAP( x, y) { x ^= y; y ^= x; x ^= y;}
n0Texture::n0Texture(u32 texID, u32 texWidth, u32 texHeight, u32 bpp, u32 colorspace)
	:width(texWidth), height(texHeight), textureID(texID), bpp(bpp), colorspace(colorspace)
{
	glGenTextures(1,&glID);
	glBindTexture(GL_TEXTURE_2D, glID);
	Pow2(texWidth);
	Pow2(texHeight);
	u16 val = 0xffff;
	u16 val2 = 0x0000;
	u16 * fakeData = (u16*)malloc(texWidth*texHeight * sizeof(u16));
	for(u32 y = 0; y < texHeight ; y++)
	{
		if(y % 16 == 0)
			SWAP(val,val2);
		for(u32 x = 0; x < texWidth && texWidth > 16; x +=16)
		{
			memset(&fakeData[y*texWidth + x],val,16);
			SWAP(val,val2);
		}
	}
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, fakeData);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); // Linear Filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); // Linear Filtering

	n0_FlushGLError();
}

void n0Texture::Bind(u32 slot)
{
	glBindTexture(slot, glID);

}


void n0Texture::WritePixels(u32 x, u32 y, u32 w, u32 h, byte * data)
{
	Bind();
	glTexSubImage2D(GL_TEXTURE_2D,0,x,y,w,h,GL_RGBA,GL_UNSIGNED_SHORT_4_4_4_4,(void*)data);

	

}

void n0Texture::LoadPng(const char *path)
{
	//load the file

	u32 width = 1024;
	u32 height = 1024;
	byte *data = 0;
	WritePixels(0,0,width,height,data);

}

}