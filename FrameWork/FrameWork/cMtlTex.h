#pragma once

class cMtlTex : public cObject
{
private:
	SYNTHESIZE(DWORD, m_dwAttrID, AttrID);
	SYNTHESIZE(D3DMATERIAL9, m_stMtl, Mtl);
	SYNTHESIZE(LPDIRECT3DTEXTURE9, m_pTexture, Texture);

public:
	cMtlTex();
	~cMtlTex();
};

