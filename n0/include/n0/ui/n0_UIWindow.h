#ifndef __FWUIWINDOW_H__
#define __FWUIWINDOW_H__

class fwUIWindow : public fwUIDecorator
{

protected:
	bool m_isFocus; 
	bool m_isMouseOver;

	//irr::video::ITexture * m_pTexture;
public:
	fwUIWindow(u32 x = 0, u32 y = 0, u32 w = 100, u32 h = 100, fwUIDecorator *decorator = NULL, u32 id = -1);
	virtual ~fwUIWindow();
	virtual void Draw();
	virtual void Update(u32 delta);
	virtual bool OnEvent(Event *e);

	//void SetTexture(irr::video::ITexture *tex) { m_pTexture = tex; }


//	void AttachEvents(InputReceiver *receiver);
//	void DetachEvents(InputReceiver *receiver);
};


#endif