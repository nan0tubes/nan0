#ifndef __SPRITE_H__
#define __SPRITE_H__



namespace n0
{

//Sprites are 2D in Nature

class Sprite 
{
public:
	enum EAnchor 
	{
		kAnchor_TopLeft = 0,
		kAnchor_Center,
		kAnchor_BottomLeft
	};
protected:
	//irr::video::ITexture * m_pTexture;

	u32 tWidth;
	u32 tHeight;
	u32 height;
	u32 width;
	u32 x;
	u32 y;
	u32 colour;

	EAnchor m_Anchor;
public:
	Sprite(const char* fileName);
	virtual ~Sprite();

	u32 GetHeight() { return height; }
	void SetHeight(u32 h) { height = h;}
	u32 GetWidth() { return width; }
	void SetWidth(u32 w) { width = w; }

	u32 GetX() { return x; }
	void SetX(u32 X) { x = X; }
	u32 GetY() { return y; }
	void SetY(u32 Y) { y = Y; }
	void SetPos(const vec2i & pos) { x = pos.X; y = pos.Y; }

	void Scale(float scale) { height = u32((float)height * scale); width = u32(float(width) * scale); }

	EAnchor GetAnchor() { return m_Anchor;}
	void SetAnchor(EAnchor anch) { m_Anchor = anch; }

	u32 GetColour() { return colour; }
	void SetColour(u32 c) { colour = c;}

//	virtual void Draw(irr::core::recti * srcRect = NULL);

//	static void DrawWireRect(irr::core::recti rect, irr::video::SColor color);

protected:
//	void GetDestRect(irr::core::recti &destRect);

};

class SpriteSheet : public Sprite
{
protected:
//	Json::Value m_JsonFrames;
//	Json::Value m_JsonMeta;
//	Json::Reader jReader;
//	Json::Value jRoot;

public:
	SpriteSheet(const char* textureFilename, const char* jsonFilename);
	virtual ~SpriteSheet() {}
	virtual void Draw(const char * filename, EAnchor anchor, const vec2i &pos, u32 & col);
//	irr::core::vector2di GetDims(const char * filename);
};



};
#endif //__SPRITE_H__