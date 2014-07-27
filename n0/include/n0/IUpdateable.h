#ifndef __IUPDATEABLE_H__
#define __IUPDATEABLE_H__

class IUpdateable
{
public:
	virtual void Update(u32 delta) = 0;
};



#endif //IUPDATEABLE_H__