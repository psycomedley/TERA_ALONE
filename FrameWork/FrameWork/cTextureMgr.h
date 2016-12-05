#pragma once
#include "cSingleton.h"

class cTextureMgr : public cSingleton<cTextureMgr>
{
private:
	map<string, LPDIRECT3DTEXTURE9> m_mapTexture;
	map<string, D3DXIMAGE_INFO>		m_mapImageInfo;

public:
	LPDIRECT3DTEXTURE9 GetTexture(string s);
	LPDIRECT3DTEXTURE9 GetTexture(string s, D3DXIMAGE_INFO* pII);

public:
	void Release();

public:
	cTextureMgr();
	~cTextureMgr();
};

