#ifndef __SCENE_H_
#define __SCENE_H__

class Scene : public IUpdateable, public IDrawable,  public IEventHandler<32>, public IEventListener
{

public:
	
protected:
	std::list<IUpdateable*> m_UpdateStack;

	bool m_bAlive;
	u32 m_sceneName;
public:
	//Scene are given a identifier in which they can be asked for from the game engine.
	//This is separate from a Scene ID which is a Type of scene
	Scene(u32 sceneName);
	virtual ~Scene();

	virtual bool Init();
	virtual void CleanUp();

	virtual void Update(unsigned int delta);
	virtual void Draw();
//	virtual bool OnEvent(const irr::SEvent& event) { return false;}
	virtual bool OnEvent(Event *e) { return kFalse; }
	inline bool IsAlive() { return m_bAlive; }
	std::list<IUpdateable*> & GetUpdateStack() { return m_UpdateStack; }
	u32 GetSceneName() { return m_sceneName; }
	static u32 GetSceneType() { return s_sceneID; }
protected:

private:

	static u32 s_sceneID;
};

#endif //__SCENE_H__