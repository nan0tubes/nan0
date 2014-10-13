#ifndef __UIDECORATOR_H__
#define __UIDECORATOR_H__
namespace n0
{

class UIDecorator : public UIObject
{

protected:
	UIDecorator * m_decorator;
	UIDecorator(UIDecorator *decorator, u32 id) : UIObject(id) { m_decorator = decorator; }
	virtual ~UIDecorator() { }
public:
	
	virtual void Draw() { UIObject::Draw(); }
	virtual void Update(u32 delta)  { UIObject::Update(delta);}
	virtual bool OnEvent(n0Event *e) { return UIObject::OnEvent(e); }
	 
	void AddChild(UIObject * child) { UIObject::AddChild(child); }
	void RemoveChild(UIObject * child) { UIObject::RemoveChild(child); }
	void RemoveChild(u32 childID) { UIObject::RemoveChild(childID); }

};

};
#endif