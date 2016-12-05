#include "stdafx.h"
#include "cDevice.h"


cDevice::cDevice()
	: m_pD3D(NULL)
	, m_pD3DDevice(NULL)
{
}


cDevice::~cDevice()
{
}


HRESULT cDevice::Setup()
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9	stCaps;
	int			nVertexProcessing;

	if (FAILED(m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stCaps)))
	{
		MSGBOX("DeviceCaps Get Fail");
		return E_FAIL;
	}

	if (stCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS stD3DPP;
	ZeroMemory(&stD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	stD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stD3DPP.Windowed = TRUE;
	stD3DPP.BackBufferFormat = D3DFMT_UNKNOWN;
	stD3DPP.EnableAutoDepthStencil = TRUE;
	stD3DPP.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hWnd,
		nVertexProcessing,
		&stD3DPP,
		&m_pD3DDevice)))
	{
		MSGBOX("Device Create Fail");
		return E_FAIL;
	}

	return S_OK;
}


void cDevice::Release()
{
	SAFE_RELEASE(m_pD3D);

	ULONG ul = m_pD3DDevice->Release();
	assert(ul == 0 && "COM객체 메모리 릭");

	cSingleton::Release();
}


void cDevice::BeginRender()
{
	m_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER /*| D3DCLEAR_STENCIL*/,
		D3DCOLOR_XRGB(128, 128, 128),
		1.0f, 0);
	m_pD3DDevice->BeginScene();
}


void cDevice::EndRender()
{
	m_pD3DDevice->EndScene();
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}