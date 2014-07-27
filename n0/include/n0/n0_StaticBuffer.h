


#ifndef __FW_STATIC_BUFFER_H__
#define __FW_STATIC_BUFFER_H__

static const u32 kMaxStaticBufferSections = 32;

struct bufferSection
{
	void *pStaticBuffer;
	btye *pData;
	u32 size;
	u32 offset;
	u32 name;
};
struct fwStaticBuffer
{
	bufferSection sections[kMaxStaticBufferSections];
	btye *pData;
	u32 maxSize;
	
	u32 leftPos;	// tracker of byte of free space
	u32 rightPos;	// tracker of end of buffer offset
	u32 name;
	u32 numSections;

};

u32 fwStaticBuffer_MaxPossibleAlloc(fwStaticBuffer &buffer);

//! Brief Creates a static buffer
//! Inputs size of the buffer, Name for the buffer
fwStaticBuffer fwStaticBuffer_Create(const u32 size, const u32 name);

//! Brief Allocate some space from the static buffer
//! Input, buffer to alloc from, size of allocation, name of allocation.
bufferSection * fwStaticBuffer_Alloc(fwStaticBuffer &buffer, const u32 size , u32 name);


//! Brief  Allocates the Remaining space from a static buffer
//! Input, buffer to alloc from, container for size, name of the buffer
bufferSection * fwStaticBuffer_MaxAlloc(fwStaticBuffer &buffer, u32 &size, u32 name );

//! Brief Frees some section from the buffer
//! input, buffer to alloc from, the name of the section
ErrorCode fwStaticBuffer_Free(fwStaticBuffer &buffer, u32 name);



#endif // __FW_STATIC_BUFFER_H__