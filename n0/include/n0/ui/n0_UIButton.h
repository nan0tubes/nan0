#ifndef __UIBUTTON_H__
#define __UIBUTTON_H__
namespace n0
{
class UIButton : public UIDecorator
{
private:

protected:
	bool m_isDown;
	bool m_isMouseOver;
	


public:
	UIButton(u32 x = 0, u32 y = 0, u32 w = 0, u32 h = 0, UIDecorator *decorator = NULL, u32 id = -1 );
	virtual ~UIButton();
	virtual void Draw();
	virtual void Update(u32 delta);
	virtual bool OnEvent(n0Event *e);


};

};
#endif