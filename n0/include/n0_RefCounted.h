#ifndef __N0_REFCOUNTED_H__
#define __N0_REFCOUNTED_H__


class n0_RefCounted
{
	u32 _count;
	friend class n0_RefManager;
public:
	n0_RefCounted();
#ifdef _DEBUG
	u32 GetCount() { return _count;}
	bool wasDestroyed;
#endif

	void Drop();
	void Retain();


private:
	virtual ~n0_RefCounted() { }


};


class n0_RefManager
{
	friend class n0_RefCounted;
	std::vector<n0_RefCounted*> m_objects;
	#ifdef _DEBUG
	std::vector<n0_RefCounted*> m_oldObjects;
	#endif
private:
	n0_RefManager();
	~n0_RefManager();

	void RegisterForDelete(n0_RefCounted *_Object);
public:

	void Purge();
	static n0_RefManager * GetInstance();
};


#endif //__N0_REFCOUNTED_H__