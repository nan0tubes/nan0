#include "n0/n0.h"

namespace n0
{


n0StaticBuffer n0StaticBuffer_Create(const u32 size, const u32 name)
{
	n0_ASSERT(size > 0,"Trying to create buffer of size 0");
	n0StaticBuffer buff;
	buff.pData = (byte*)n0_MALLOC(size);
	n0_ASSERT(buff.pData, "Couldn't Alloc buffer");
	memzero(buff.sections,sizeof(n0BufferSection)*kMaxStaticBufferSections);
	buff.numSections = 0;
	buff.leftPos = 0;
	buff.rightPos = size;
	buff.name = name;
	
	buff.maxSize = size;
	
	return buff;
}

n0BufferSection * n0StaticBuffer_Alloc(n0StaticBuffer &buffer, const u32 size , u32 name)
{
	if(buffer.rightPos - buffer.leftPos < size)
	{
		char buf[kStrLen_Huge];
		snprintf(buf,kStrLen_Huge,"UNABLE To allocate %u btyes for %u from static buffer %ui",size,name,buffer.name);
		//GetGame()->GetBlackBox()->Log("ENGINE",2,buf);
		return NULL;
	}
	n0BufferSection &bufSec = buffer.sections[buffer.numSections++];
	bufSec.name = name;
	bufSec.size = size;
	bufSec.offset = buffer.leftPos;
	bufSec.pData = &buffer.pData[buffer.leftPos];
	buffer.leftPos +=size;

	return &bufSec;
}

n0BufferSection * n0StaticBuffer_MaxAlloc(n0StaticBuffer &buffer, u32 &size, u32 name )
{
	size = buffer.rightPos - buffer.leftPos;
	return n0StaticBuffer_Alloc(buffer,size,name);
}

ErrorCode n0StaticBuffer_Free(n0StaticBuffer &buffer, u32 name)
{
	n0_FREE(buffer.pData);
	return kSuccess;
}

u32 n0StaticBuffer_MaxPossibleAlloc(n0StaticBuffer &buffer)
{
	return (buffer.rightPos - buffer.rightPos);
}




};