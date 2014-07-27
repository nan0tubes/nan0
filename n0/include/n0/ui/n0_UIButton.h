#ifndef __FWUIBUTTON_H__
#define __FWUIBUTTON_H__

class fwUIButton : public fwUIDecorator
{
private:

protected:
	bool m_isDown;
	bool m_isMouseOver;
	
	//irr::video::ITexture * m_pUpTexture;
	//irr::video::ITexture * m_pDownTexture;
	//irr::video::ITexture * m_pMouseOverTexture;


public:
	fwUIButton(u32 x = 0, u32 y = 0, u32 w = 0, u32 h = 0, fwUIDecorator *decorator = NULL, u32 id = -1 );
	virtual ~fwUIButton();
	virtual void Draw();
	virtual void Update(u32 delta);
	virtual bool OnEvent(Event *e);


//	void AttachEvents(InputReceiver *receiver);
//	void DetachEvents(InputReceiver *receiver);
};

#endif