

#ifndef __FW_FILE_H__
#define __FW_FILE_H__


namespace n0
{

struct n0FileSection
{
	u32 name;			// indentifer to the section.
	u32 size; 
	u32 hash;			// to use as a checksum
	u32 offset;			// from the beginning of data
	u32 timestamp;		// Seconds from a reference date, that can be used to compare vs other sections(for soft updating)
	u32 version;		// Version of the type of file
	u32 type;			// Type of file
};

struct n0FileHeader
{
	u32 sectionCount;
};
struct n0Pack
{
	byte * pData;
	std::vector<n0FileSection> sections;
	FILE * pFile;
};
ErrorCode OpenPack(const char *path);



};

#endif //__FW_FILE_H__