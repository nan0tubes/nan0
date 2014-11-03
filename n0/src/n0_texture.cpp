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

n0Texture::n0Texture(u32 texID, u32 texWidth, u32 texHeight, u32 bpp, u32 colorspace)
	:width(texWidth), height(texHeight), textureID(texID), bpp(bpp), colorspace(colorspace)
{
	//glEnable(GL_TEXTURE_2D);
	while( glGetError());
	glGenTextures(1,&glID);
	glBindTexture(GL_TEXTURE_2D, glID);
	Pow2(texWidth);
	Pow2(texHeight);
	u32 val = 0xff00ff00;
	u32 val2 = 0xff0000FF;
	u32 * fakeData = (u32*)malloc(texWidth*texHeight * sizeof(u32));

	for(u32 y = 0; y < texHeight ; y++)
	{
		if(y%16 == 0)
		{
			SWAP(val,val2);
		}
		for(u32 x = 0; x < texWidth ; x++)
		{
			if(x%16 == 0)
			{
				SWAP(val,val2);
			}
			fakeData[y*texWidth + x] = val;
	
		}

	}

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); // Linear Filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); // Linear Filtering
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, fakeData);


	//n0_FlushGLError();
	 u32 err; 
	 while(err = glGetError()) 
	 { 
		 printf("GL ERROR #%d - %s:%d",err,__FILE__,__LINE__);
	 };
//	 glDisable(GL_TEXTURE_2D);
}

void n0Texture::Bind(u32 slot)
{
//	glEnable(GL_TEXTURE_2D);
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