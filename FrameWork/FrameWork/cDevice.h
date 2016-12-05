#pragma once
#include "cSingleton.h"

#define g_pD3DDevice cDevice::GetInst()->GetDevice()

class cDevice : public cSingleton<cDevice>
{
private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice;

public:
	void		BeginRender();
	void		EndRender();

public:
	const LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DDevice; }

public:
	HRESULT		Setup();
	void		Release();

public:
	cDevice();
	~cDevice();
};

