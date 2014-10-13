


#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H


namespace n0
{

class AnimatedSprite : public Sprite, public IUpdateable
{
public:
	struct Animation {
		u32 animID;
		u32 startFrame;
		u32 endFrame;
		Animation(u32 aID, u32 sf, u32 ef) : animID(aID) , startFrame(sf) , endFrame(ef) { }
	};
protected:

	u32 m_numFrames;
	u32 m_frameHeight;
	u32 m_frameWidth;
	u32 m_frameRate;
	u32 m_time;

	u32 m_framesPerRow;

	u32 m_currentAnim;

	u32 m_numAnims;
	std::vector<Animation> m_anims;

	bool m_isPaused;

public:

	AnimatedSprite(const char* fileName, u32 frameHeight, u32 frameWidth, u32 numframes, u32 framerate = 30);
	virtual ~AnimatedSprite();

	void AddAnim(u32 animID, u32 startFrame, u32 endFrame);

	void SetAnim(u32 animID);
	inline u32 GetCurrentAnimID() { return m_anims[m_currentAnim].animID; }
	inline const Animation * GetCurrentAnim() { if(m_currentAnim>= m_anims.size()) return NULL; return &m_anims[m_currentAnim] ; }
	const Animation * GetAnim(u32 id);
	//virtual void Draw(irr::core::recti * srcRect = NULL);
	virtual void Update(u32 delta);

	virtual void Pause() { m_isPaused = kTrue; }
	virtual void Resume() { m_isPaused = kFalse; }
	//irr::core::recti GetSourceRect(irr::core::recti * srcRect);
};


class AnimatedSpriteBillboard : public AnimatedSprite
{

	vec2f scale;
	vec2f translate;
protected:
	void * m_pSceneNode;
public:
	AnimatedSpriteBillboard(const char* filename, u32 frameHeight, u32 frameWidth, u32 numFrames, u32 framerate = 30,void  *pParent = NULL, vec3f pos = vec3f(0,0,0), void * pMgr = NULL);
	virtual ~AnimatedSpriteBillboard();

	inline void * GetSceneNode() { return m_pSceneNode; }

//	virtual void Draw(irr::core::recti * srcRect = NULL);
	virtual void Update(u32 delta);

	virtual void Pause() { AnimatedSprite::Pause(); }
	virtual void Resume() { AnimatedSprite::Resume(); }

//	inline void Hide() { if(m_pSceneNode) m_pSceneNode->setVisible(kFalse); }
//	inline void Show() { if(m_pSceneNode) m_pSceneNode->setVisible(kTrue); }
};



};
#endif