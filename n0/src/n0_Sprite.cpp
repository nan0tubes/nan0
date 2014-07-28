#include "n0/n0.h"

namespace n0
{


Sprite::Sprite(const char* fileName)
{
	//m_pTexture = GetGame()->GetVideoDriver()->getTexture(fileName);
	if(m_pTexture)
	{
		tWidth = width = m_pTexture->getSize().Width;
		tHeight = height = m_pTexture->getSize().Height;
		char buf[kStrLen_Large];
		snprintf(buf,kStrLen_Large,"Sprite Created with image %s, size %u,%u",fileName,width,height);
		GetGame()->GetBlackBox()->Log("System",3,buf);
	}
	else
	{
		char buf[kStrLen_Large];
		snprintf(buf,kStrLen_Large,"Failed to create sprite with file %s",fileName);
		GetGame()->GetBlackBox()->Log("System",1,buf);
	}
	colour = irr::video::SColor(0xffffffff);
	x=0;
	y=0;
	m_Anchor = kAnchor_Center;
}

Sprite::~Sprite()
{
	m_pTexture = NULL;
}


void Sprite::GetDestRect(irr::core::recti &destRect)
{
	if(m_Anchor == kAnchor_Center)
		destRect = irr::core::recti(x-width/2,y-height/2,x+width/2,y+height/2);
	else if(m_Anchor == kAnchor_TopLeft)
		destRect = irr::core::recti(x,y,x+width,y+height);
	else if(m_Anchor == kAnchor_BottomLeft)
		destRect = irr::core::recti(x,y-height,x+width,y);
	else
		destRect = irr::core::recti(x,y,x+width,y+height);
}

void Sprite::Draw(irr::core::recti * srcRect)
{
	if(m_pTexture)
	{
		irr::core::recti destRect;
		GetDestRect(destRect);
		irr::video::SColor colors[4] = {colour,colour,colour,colour};
		bool shouldDeleteSrcRect = false;
		if (srcRect == NULL)
			srcRect = new irr::core::recti(0,0,m_pTexture->getSize().Width,m_pTexture->getSize().Height);
		GetGame()->GetVideoDriver()->draw2DImage(m_pTexture,destRect,*srcRect,0,&(colors[0]),true);
//		if (srcRect)
//			delete srcRect;
#ifdef DEBUG
		if(GetGame()->IsDebugRender())
		{
			Sprite::DrawWireRect(destRect,irr::video::SColor(255,255,0,255));
		}
#endif
	}

}
void Sprite::DrawWireRect(irr::core::recti rect, irr::video::SColor color)
{
	GetGame()->GetVideoDriver()->draw2DLine(rect.UpperLeftCorner,rect.LowerRightCorner,color);
	GetGame()->GetVideoDriver()->draw2DLine(rect.UpperLeftCorner,irr::core::vector2di(rect.UpperLeftCorner.X+rect.getWidth(),rect.UpperLeftCorner.Y),color);
	GetGame()->GetVideoDriver()->draw2DLine(rect.UpperLeftCorner,irr::core::vector2di(rect.UpperLeftCorner.X,rect.UpperLeftCorner.Y + rect.getHeight()),color);
	GetGame()->GetVideoDriver()->draw2DLine(irr::core::vector2di(rect.UpperLeftCorner.X+rect.getWidth(),rect.UpperLeftCorner.Y),rect.LowerRightCorner,color);
	GetGame()->GetVideoDriver()->draw2DLine(irr::core::vector2di(rect.UpperLeftCorner.X,rect.UpperLeftCorner.Y + rect.getHeight()),rect.LowerRightCorner,color);
	GetGame()->GetVideoDriver()->draw2DLine(irr::core::vector2di(rect.UpperLeftCorner.X+rect.getWidth(),rect.UpperLeftCorner.Y),irr::core::vector2di(rect.UpperLeftCorner.X,rect.UpperLeftCorner.Y + rect.getHeight()),color);
}


SpriteSheet::SpriteSheet(const char* textureFilename, const char* jsonFilename) : Sprite(textureFilename)
{
	std::ifstream datafile(jsonFilename, std::ifstream::binary);
	if (jReader.parse(datafile, jRoot))
	{
		m_JsonFrames = jRoot["frames"];
		m_JsonMeta = jRoot["meta"];
		char jsonMessage[kStrLen_Large];
		snprintf(jsonMessage, kStrLen_Large, "%u asset entries found in the json atlas data ('%s').", m_JsonFrames.size(), jsonFilename);
		GetGame()->GetBlackBox()->Log("SYSTEM", 0, jsonMessage);
	}
	datafile.close();
}

void SpriteSheet::Draw(const char * filename, EAnchor anchor, const irr::core::position2di &pos, irr::video::SColor & col)
{
	for (u32 i = 0; i < m_JsonFrames.size(); ++i)
	{
		std::string temp(m_JsonFrames[i]["filename"].asString());
		if (!temp.compare(filename))
		{
			Json::Value frame = m_JsonFrames[i]["frame"];
			Sprite::SetWidth(frame["w"].asInt());
			Sprite::SetHeight(frame["h"].asInt());
			Sprite::SetAnchor(anchor);
			Sprite::SetPos(pos);
			Sprite::SetColour(col);
			//NOTE: Sprite::Draw will delete this rectangle
			irr::core::recti  srcRect(frame["x"].asInt(), frame["y"].asInt(), frame["x"].asInt() + frame["w"].asInt(), frame["y"].asInt() + frame["h"].asInt());
			Sprite::Draw(&srcRect);
		}
	}
//	m_JsonFrames[filename]
//	irr::core::recti srcRect(0,0,m_pTexture->getSize().Width,m_pTexture->getSize().Height);
}

irr::core::vector2di SpriteSheet::GetDims(const char * filename)
{
	irr::core::vector2di retval;
	for (u32 i = 0; i < m_JsonFrames.size(); ++i)
	{
		if (!m_JsonFrames[i]["filename"].asString().compare(filename))
		{
			Json::Value frame = m_JsonFrames[i]["frame"];
			retval.X = frame["w"].asInt();
			retval.Y = frame["h"].asInt();
			break;
		}
	}
	return retval;
}


};