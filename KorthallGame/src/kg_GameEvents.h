class GameEvents : public n0::IEventListener
{
public:

	GameEvents();
	~GameEvents();
	bool OnEvent(n0::n0Event *evt);
protected:
	bool OnMouseEvent(n0::n0Event *_evt) ;
	bool OnKeyEvent(n0::n0Event *_evt) ;
	bool OnMouseMoveEvent(n0::n0Event *_evt);

};