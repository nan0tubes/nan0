#ifndef __N0_MATERIAL_H__
#define __N0_MATERIAL_H__

namespace n0
{
class n0Material : public n0RefCounted
{
	friend class n0MaterialManager;
public:
	static const u32 kMaxMaterialTextures = 5;
private:
	u32 materialName;
	u32 glProgramID;
	n0Array<n0Texture*,kMaxMaterialTextures> texpArray;

public:
	n0Material(u32 _matName, n0Texture* _texture, u32 _progID);
	~n0Material();

	void SetTexture(u32 glSlot, n0Texture* texture);

	void Bind();

};

}

#endif __N0_MATERIAL_H__