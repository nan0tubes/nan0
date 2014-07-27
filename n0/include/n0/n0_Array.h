#ifndef __FW_ARRAY_H__
#define __FW_ARRAY_H__

template<class T, u32 SIZE>
class fwArray 
{
public:

	T data[SIZE];
	
	fwArray() 
	{ 
		memzero(&data, sizeof(T)*SIZE); 
	}

	inline T& operator[] (u32 index)
	{
		FW_ASSERT((index < SIZE),"Array index out of Bounds!");
		return data[index];
	}

	ErrorCode removeAt(u32 index)
	{
		if(!(index < SIZE))
			return kErrorCode_InvalidData;

		for(u32 i = index; i < SIZE-1; i++)
		{
			data[i] = data[i+1];
		}
		return kErrorCode_Success;
	}
};

template<class T, u32 SIZE>
static ErrorCode removeAt(std::array<T, SIZE> &arr, u32 index, u32 topIndex = SIZE)
{
	if(!(index < SIZE))
		return kErrorCode_InvalidData;
	if(!(index < topIndex))
		return KErrorCode_SoftFailure;
	for(u32 i = index; i < topIndex && i < SIZE-1; i++)
	{
		arr[i] = arr[i+1];
	}
	return kErrorCode_Success;
}
#endif // __FW_ARRAY_H__
