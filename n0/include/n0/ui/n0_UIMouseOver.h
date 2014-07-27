#ifndef __FWUIMOUSEOVER_H__
#define __FWUIMOUSEOVER_H__

class fwUIMouseOver : public fwUIDecorator
{

private:

public:
	fwUIMouseOver(fwUIDecorator *decorator, u32 id = -1 ):fwUIDecorator(decorator,id) { }
	virtual void Draw() { if(m_decorator) m_decorator->Draw();}
	virtual void Update(u32 delta) {if(m_decorator)  m_decorator->Update(delta); }
	virtual bool OnEvent(Event *e) { if(m_decorator) m_decorator->OnEvent(e); }
};

#endif //__FWUIMOUSEOVER_H__