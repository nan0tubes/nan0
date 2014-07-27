

class fwUIManager : public fwClass, public IUpdateable, public IDrawable, public IEventHandler<128>
{
	static const u32 s_type;
	static const u32 kMaxUIObjects = 256;
	fwUIObject * m_pParentNode;
	fwArray<fwUIObject*,kMaxUIObjects> m_uiObjects;

	fwUIButton * CreateUIButton( u32 ID, u32 x, u32 y, u32 w, u32 h,  u32 parent = 0);
	fwUIWindow * CreateUIWindow( u32 ID, u32 x, u32 y, u32 w, u32 h, u32 parent = 0);
	fwUIObject * CreateUINode( u32 ID, u32 x, u32 y, u32 parent = 0);

	void Draw();
	void Update(u32 delta);
	virtual bool IsType(u32 type) { if((type == fwUIManager::s_type)) return kTrue;}  
};