#include "stdafx.h"
#include "cTextureMgr.h"


cTextureMgr::cTextureMgr()
{
}


cTextureMgr::~cTextureMgr()
{
}


LPDIRECT3DTEXTURE9 cTextureMgr::GetTexture(string s)
{
	if (m_mapTexture.find(s) == m_mapTexture.end())
		D3DXCreateTextureFromFile(g_pD3DDevice, s.c_str(), &m_mapTexture[s]);
	return m_mapTexture[s];
}


LPDIRECT3DTEXTURE9 cTextureMgr::GetTexture(string s, D3DXIMAGE_INFO* pII)
{
	if (m_mapTexture.find(s) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			s.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_mapImageInfo[s],
			NULL,
			&m_mapTexture[s]);
	}
	else if (m_mapImageInfo.find(s) == m_mapImageInfo.end())
	{
		SAFE_RELEASE(m_mapTexture[s]);
		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			s.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_mapImageInfo[s],
			NULL,
			&m_mapTexture[s]);
	}

	if (pII)
		*pII = m_mapImageInfo[s];

	return m_mapTexture[s];
}


void cTextureMgr::Release()
{
	for each(auto it in m_mapTexture)
		SAFE_RELEASE(it.second);

	cSingleton::Release();
}