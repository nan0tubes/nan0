#ifndef __UIWINDOW_H__
#define __UIWINDOW_H__
namespace n0
{
class UIWindow : public UIDecorator
{

protected:
	bool m_isFocus; 
	bool m_isMouseOver;

	//irr::video::ITexture * m_pTexture;
public:
	UIWindow(u32 x = 0, u32 y = 0, u32 w = 100, u32 h = 100, UIDecorator *decorator = NULL, u32 id = -1);
	virtual ~UIWindow();
	virtual void Draw();
	virtual void Update(u32 delta);
	virtual bool OnEvent(n0Event *e);

	//void SetTexture(irr::video::ITexture *tex) { m_pTexture = tex; }


//	void AttachEvents(InputReceiver *receiver);
//	void DetachEvents(InputReceiver *receiver);
};
};

#endif