#ifndef __UIMOUSEOVER_H__
#define __UIMOUSEOVER_H__


namespace n0
{

class UIMouseOver : public UIDecorator
{

private:

public:
	UIMouseOver(UIDecorator *decorator, u32 id = -1 ):UIDecorator(decorator,id) { }
	virtual void Draw() { if(m_decorator) m_decorator->Draw();}
	virtual void Update(u32 delta) {if(m_decorator)  m_decorator->Update(delta); }
    virtual bool OnEvent(n0Event *e) { if(m_decorator) return m_decorator->OnEvent(e); return false; }
};

};

#endif //__UIMOUSEOVER_H__