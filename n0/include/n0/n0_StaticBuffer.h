
#ifndef __FW_STATIC_BUFFER_H__
#define __FW_STATIC_BUFFER_H__


namespace n0
{

static const u32 kMaxStaticBufferSections = 32;

struct n0BufferSection
{
	void *pStaticBuffer;
	byte *pData;
	u32 size;
	u32 offset;
	u32 name;
};
struct n0StaticBuffer
{
	n0BufferSection sections[kMaxStaticBufferSections];
	byte *pData;
	u32 maxSize;
	
	u32 leftPos;	// tracker of byte of free space
	u32 rightPos;	// tracker of end of buffer offset
	u32 name;
	u32 numSections;

};

u32 n0StaticBuffer_MaxPossibleAlloc(n0StaticBuffer &buffer);

//! Brief Creates a static buffer
//! Inputs size of the buffer, Name for the buffer
n0StaticBuffer n0StaticBuffer_Create(const u32 size, const u32 name);

//! Brief Allocate some space from the static buffer
//! Input, buffer to alloc from, size of allocation, name of allocation.
n0BufferSection * n0StaticBuffer_Alloc(n0StaticBuffer &buffer, const u32 size , u32 name);


//! Brief  Allocates the Remaining space from a static buffer
//! Input, buffer to alloc from, container for size, name of the buffer
n0BufferSection * n0StaticBuffer_MaxAlloc(n0StaticBuffer &buffer, u32 &size, u32 name );

//! Brief Frees some section from the buffer
//! input, buffer to alloc from, the name of the section
ErrorCode n0StaticBuffer_Free(n0StaticBuffer &buffer, u32 name);


};

#endif // __FW_STATIC_BUFFER_H__