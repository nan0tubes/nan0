#ifndef __UIMANAGER_H__
#define __UIMANAGER_H__

namespace n0
{
class UIManager : public n0Class, public IUpdateable, public IDrawable, public IEventHandler<128>, public IEventListener
{
	static const u32 s_type;
	static const u32 kMaxUIObjects = 256;

	UIObject * m_pParentNode;
	n0Array<UIObject*,kMaxUIObjects> m_uiObjects;

	UIManager();
	~UIManager();

	static UIManager * s_Instance;
public:
	static UIManager * GetInstance();
	static void TearDown();

	UIButton * CreateUIButton( u32 ID, u32 x, u32 y, u32 w, u32 h,  u32 parent = 0);
	UIWindow * CreateUIWindow( u32 ID, u32 x, u32 y, u32 w, u32 h, u32 parent = 0);
	UIObject * CreateUINode( u32 ID, u32 x, u32 y, u32 parent = 0);

	void Draw();
	void Update(u32 delta);
	virtual bool IsType(u32 type) { if((type == UIManager::s_type)) return kTrue;return kFalse;}  

	bool OnEvent(n0Event *evt);
};

};

#endif //__UIMANAGER_H__