#ifndef __UIOBJECT_H__
#define __UIOBJECT_H__

namespace n0
{

class UIObject : public IDrawable, public IUpdateable, public IEventListener, public IEventHandler<8>
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
	n0Array<UIObject*,kMaxNumChildren> m_children;

public:
	UIObject();
	UIObject(u32 id);
	virtual ~UIObject();

	inline u32 GetID() { return  m_UID; }

	virtual void Draw();
	virtual void Update(u32 delta);
	virtual bool OnEvent(n0Event *);

	inline virtual bool IsHidden() { return m_visible; }
	inline virtual void Hide() { m_visible = kFalse; }
	inline virtual void Show() { m_visible = kTrue; }
	inline virtual bool operator<(const UIObject &b) { return m_depth < b.m_depth; }

	bool AddChild(UIObject * child) ;
	UIObject * RemoveChild(UIObject * child);
	UIObject * RemoveChild(u32 childID);

	inline void SetDepth(s32 depth) { m_depth = depth; }
	inline void SetParentPosition(s32 x, s32 y) { m_parentPos.x = x;  m_parentPos.y = y; }
	inline void SetParentPosition(vec2i pos) { m_parentPos = pos; }

	inline void SetPosition(s32 x, s32 y) { m_postion.x = x; m_postion.y = y; }
	inline void SetPosition(vec2i pos) { m_postion = pos; }

	inline void SetAnchor(s32 x, s32 y) { m_anchor.x = x, m_anchor.y = y; }
	inline void SetAnchor(vec2i pos) { m_anchor = pos; }

	inline const vec2i GetPosition() { return m_postion; }
	inline const vec2i GetWorldPostion() { return (m_parentPos + m_postion); }

}; // UIObject

};

#endif