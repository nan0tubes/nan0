#include "n0/n0.h"

namespace n0
{

AnimatedSprite::AnimatedSprite(const char* fileName, u32 frameHeight, u32 frameWidth, u32 numframes, u32 frameRate)
	: Sprite(fileName)
	, m_isPaused(false)
{
	m_frameHeight = frameHeight;
	m_frameWidth = frameWidth;
	m_frameRate = 1000 / frameRate;
	m_numFrames = numframes;

	m_anims.push_back(Animation(Hash("default"),0,numframes));
	m_currentAnim = 0;
	if(width %frameWidth != 0)
	{
		printf("Warning Image Width is not a multiple of frame width, may cause undefined behaviour");
	}
	m_framesPerRow = width / frameWidth;

	if(height %frameHeight != 0)
	{
		printf("Warning Image height is not a multiple of frame height, may cause undefined behaviour");
	}
	u32 rows = height / frameHeight;
	if(m_numFrames > m_framesPerRow * rows)
	{
		u32 maxFrames = m_framesPerRow * rows;
		printf("Warning More frames(%u) than can exists in image(%u - (%u x %u), reducing to %u"
			,m_numFrames, maxFrames, m_framesPerRow, rows, maxFrames);
		m_numFrames = maxFrames;
	}
	width = m_frameWidth;
	height = m_frameHeight;

	m_time = 0;

}
AnimatedSprite::~AnimatedSprite()
{


}
void AnimatedSprite::Update(u32 delta)
{
	if(m_isPaused)
		return;
	m_time += delta;

	if(m_time >= m_frameRate * m_numFrames)
	{
		u32 animFrames =  (m_anims[m_currentAnim].endFrame - m_anims[m_currentAnim].startFrame);
		m_time -= m_frameRate * animFrames;
	}

}

void AnimatedSprite::AddAnim(u32 animID, u32 startFrame, u32 endFrame)
{
	if(endFrame > m_numFrames)
		return;
	if(startFrame > m_numFrames)
		return;
	if(startFrame > endFrame)
		endFrame = startFrame;
	for(int i = 0 ; i < m_anims.size() ; i++)
	{
		if(m_anims[i].animID == animID)
		{
			m_anims[i].startFrame = startFrame;
			m_anims[i].endFrame = endFrame;
			return;
		}
	}
	m_anims.push_back(Animation(animID,startFrame,endFrame));
}

void AnimatedSprite::SetAnim(u32 animID)
{
	for(int i = 0 ; i < m_anims.size() ; i++)
	{
		if(m_anims[i].animID == animID)
		{
			m_currentAnim = i;
			m_time = 0;
			break;
		}
	}

}

const  AnimatedSprite::Animation * AnimatedSprite::GetAnim(u32 id)
{
	for(int i = 0 ; i < m_anims.size() ; i++)
	{
		if(m_anims[i].animID == id)
		{
			return &m_anims[i];
			break;
		}
	}
	return NULL;
}


irr::core::recti AnimatedSprite::GetSourceRect(irr::core::recti * srcRect)
{
	irr::core::recti rect;

	rect.LowerRightCorner.X = width;
	rect.LowerRightCorner.Y = height;
	rect.UpperLeftCorner.X = rect.UpperLeftCorner.Y = 0;
	u32 frame = m_time / m_frameRate;

	frame = frame %( (m_anims[m_currentAnim].endFrame - m_anims[m_currentAnim].startFrame) + 1);

	frame += m_anims[m_currentAnim].startFrame;
	

	u32 row = frame / m_framesPerRow;
	u32 col = frame % m_framesPerRow;

	if(srcRect)
	{
		rect = *srcRect;
	}


	rect.UpperLeftCorner.X += m_frameWidth * col;
	rect.UpperLeftCorner.Y += m_frameHeight * row;

	rect.LowerRightCorner.X = rect.UpperLeftCorner.X + m_frameWidth; 
	rect.LowerRightCorner.Y = rect.UpperLeftCorner.Y + m_frameHeight;

	return rect;
}

void AnimatedSprite::Draw(irr::core::recti * srcRect)
{
	irr::core::recti rect(GetSourceRect(srcRect));
	
	Sprite::Draw(&rect);
}



AnimatedSpriteBillboard::AnimatedSpriteBillboard(const char* filename, u32 frameHeight, u32 frameWidth, u32 numFrames, u32 framerate /* = 30 */, irr::scene::ISceneNode *pParent, irr::core::vector3df pos, irr::scene::ISceneManager * pMgr)
	: AnimatedSprite(filename, frameHeight, frameWidth, numFrames, framerate)
	, m_pSceneNode(NULL)
{
	scale.X = (float)frameWidth / (float) tWidth;
	scale.Y = (float)frameHeight / (float) tHeight; 
	if(!pMgr)
		pMgr = GetGame()->GetDevice()->getSceneManager();
 	m_pSceneNode = pMgr->addBillboardSceneNode(pParent, irr::core::dimension2d<f32>(frameWidth, frameHeight), pos );

 	m_pSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
 	m_pSceneNode->setMaterialTexture( 0, m_pTexture );
 	m_pSceneNode->setMaterialType( irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL );
	m_pSceneNode->getMaterial(0).TextureLayer[0].TextureWrapV = irr::video::ETC_CLAMP;
	m_pSceneNode->getMaterial(0).TextureLayer[0].TextureWrapU = irr::video::ETC_CLAMP;
}

AnimatedSpriteBillboard::~AnimatedSpriteBillboard()
{

}

void AnimatedSpriteBillboard::Draw(irr::core::recti * srcRect)
{
	irr::core::recti rect(GetSourceRect(srcRect));

	irr::core::vector2df translate((float)rect.UpperLeftCorner.X/(float)tWidth, (float)rect.UpperLeftCorner.Y/(float)tHeight);
	irr::core::matrix4 mat;
	mat.buildTextureTransform(0.0f, irr::core::vector2df(0.0f), translate, scale);
	m_pSceneNode->getMaterial(0).setTextureMatrix(0, mat);
}

void AnimatedSpriteBillboard::Update(u32 delta)
{
	if(!m_pSceneNode)
		return;
	if(!m_pSceneNode->isVisible())
		return;
	AnimatedSprite::Update(delta);
	Draw(); // To set texture on material!  Buildboards are rendered by the scene manager!
}



};