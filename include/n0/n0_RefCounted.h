#ifndef __N0_REFCOUNTED_H__
#define __N0_REFCOUNTED_H__


class n0RefCounted
{
	u32 _count;
	friend class n0RefManager;
public:
	n0RefCounted();

#ifdef _DEBUG
	u32 GetCount() { return _count;}
	bool wasDestroyed;
#endif

	void Drop();
	void Retain();


protected:
	virtual ~n0RefCounted() { }


};


class n0RefManager
{
	friend class n0RefCounted;
	std::vector<n0RefCounted*> m_objects;

#ifdef _DEBUG
	std::vector<n0RefCounted*> m_oldObjects;
#endif

private:
	n0RefManager();

	void RegisterForDelete(n0RefCounted *_Object);
public:
	~n0RefManager();

	void Purge();
	static n0RefManager * GetInstance();
};


#endif //__N0_REFCOUNTED_H__