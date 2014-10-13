#ifndef __FWUIOBJECT_H__
#define __FWUIOBJECT_H__

class fwUIObject : public IDrawable, public IUpdateable, public IEventListener, public IEventHandler<8>
{
	static const u32 kMaxNumChildren = 32;

protected:
	bool m_visible;
	//UI TO WORK IN PIXEL POSITIONS
	vec2i m_postion; // relative to parent object position
	vec2i m_parentPos; // world position of parent object
	vec2i m_anchor; // offset from top left corner to position


	u32 m_width;
	u32 m_height;
	s32 m_depth; // parameter for sorting
	u32 m_UID;

	u32 m_numChildren;
	fwArray<fwUIObject*,kMaxNumChildren> m_children;

public:
	fwUIObject();
	fwUIObject(u32 id);
	virtual ~fwUIObject();

	inline u32 GetID() { return  m_UID; }

	virtual void Draw();
	virtual void Update(u32 delta);
	virtual bool OnEvent(Event *);

	inline virtual bool IsHidden() { return m_visible; }
	inline virtual void Hide() { m_visible = kFalse; }
	inline virtual void Show() { m_visible = kTrue; }
	inline virtual bool operator<(const fwUIObject &b) { return m_depth < b.m_depth; }

	bool AddChild(fwUIObject * child) ;
	fwUIObject * RemoveChild(fwUIObject * child);
	fwUIObject * RemoveChild(u32 childID);

	inline void SetDepth(s32 depth) { m_depth = depth; }
	inline void SetParentPosition(s32 x, s32 y) { m_parentPos.X = x;  m_parentPos.Y = y; }
	inline void SetParentPosition(vec2i pos) { m_parentPos = pos; }

	inline void SetPosition(s32 x, s32 y) { m_postion.X = x; m_postion.Y = y; }
	inline void SetPosition(vec2i pos) { m_postion = pos; }

	inline void SetAnchor(s32 x, s32 y) { m_anchor.X = x, m_anchor.Y = y; }
	inline void SetAnchor(vec2i pos) { m_anchor = pos; }

	inline const vec2i GetPosition() { return m_postion; }
	inline const vec2i GetWorldPostion() { return (m_parentPos + m_postion); }

}; // fwUIObject

#endif