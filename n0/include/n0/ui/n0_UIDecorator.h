#ifndef __FWUIDECORATOR_H__
#define __FWUIDECORATOR_H__

class fwUIDecorator : public fwUIObject
{

protected:
	fwUIDecorator * m_decorator;
	fwUIDecorator(fwUIDecorator *decorator, u32 id) : fwUIObject(id) { m_decorator = decorator; }
	virtual ~fwUIDecorator() { }
public:
	
	virtual void Draw() { fwUIObject::Draw(); }
	virtual void Update(u32 delta)  { fwUIObject::Update(delta);}
	virtual bool OnEvent(Event *e) { return fwUIObject::OnEvent(e); }
	 
	void AddChild(fwUIObject * child) { fwUIObject::AddChild(child); }
	void RemoveChild(fwUIObject * child) { fwUIObject::RemoveChild(child); }
	void RemoveChild(u32 childID) { fwUIObject::RemoveChild(childID); }

};


#endif