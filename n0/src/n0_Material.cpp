#include "n0/n0.h"

namespace n0
{

n0Material::n0Material(u32 _matName, n0Texture* _texture, u32 _progID)
{
	memzero(this,sizeof(n0Material));

	materialName = _matName;
	texpArray[0] = _texture;
	glProgramID = _progID;
}

n0Material::~n0Material()
{
	for(int i = 0 ; i < kMaxMaterialTextures ; i++ )
	{
		if(texpArray[i])
		{
			texpArray[i]->Drop();
			texpArray[i] = 0;
		}
	}
}

void n0Material::SetTexture(u32 glSlot, n0Texture* texture)
{
	switch(glSlot)
	{
	case GL_TEXTURE_2D:
		{
			if(texpArray[0])
			{
				texpArray[0]->Drop();
			}
			texpArray[0] = texture;
		}
		break;
	case GL_TEXTURE1:
		{
			if(texpArray[1])
			{
				texpArray[1]->Drop();
			}
			texpArray[1] = texture;
		}
		break;
	case GL_TEXTURE2:
		{
			if(texpArray[2])
			{
				texpArray[2]->Drop();
			}
			texpArray[2] = texture;
		}
		break;
	case GL_TEXTURE3:
		{
			if(texpArray[3])
			{
				texpArray[3]->Drop();
			}
			texpArray[3] = texture;
		}
		break;
	case GL_TEXTURE4:
		{
			if(texpArray[4])
			{
				texpArray[4]->Drop();
			}
			texpArray[4] = texture;
		}
		break;
	}

}

void n0Material::Bind()
{
	if(texpArray[0])
		texpArray[0]->Bind();
	if(texpArray[1])
		texpArray[1]->Bind(GL_TEXTURE1);
	if(texpArray[2])
		texpArray[2]->Bind(GL_TEXTURE2);
	if(texpArray[3])
		texpArray[3]->Bind(GL_TEXTURE3);
	if(texpArray[4])
		texpArray[4]->Bind(GL_TEXTURE4);

}

}
