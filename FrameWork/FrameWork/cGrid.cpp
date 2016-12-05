#include "StdAfx.h"
#include "cGrid.h"
#include "cPyramid.h"

cGrid::cGrid(void)
	: m_pVB(NULL)
	, m_nLineNum(0)
{
}

cGrid::~cGrid(void)
{
	for each(auto p in m_vecPyramid)
		SAFE_DELETE(p);

	SAFE_RELEASE(m_pVB);
}

void cGrid::Setup(int nNumLine)
{
	float fWidth = 1.0f;
	int nHalf = nNumLine / 2;
	float fMax = nHalf * fWidth;

	D3DCOLOR c = D3DCOLOR_XRGB(128, 128, 128);
	for (int i = 1; i <= nHalf; ++i)
	{
		c = D3DCOLOR_XRGB(128, 128, 128);
		if (i % 5 == 0)
		{
			c = D3DCOLOR_XRGB(255, 255, 255);
		}
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-fMax, 0, i * fWidth), c));
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(fMax, 0, i * fWidth), c));

		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-fMax, 0, -i * fWidth), c));
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(fMax, 0, -i * fWidth), c));

		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(i * fWidth, 0, -fMax), c));
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(i * fWidth, 0, fMax), c));

		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-i * fWidth, 0, -fMax), c));
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-i * fWidth, 0, fMax), c));
	}

	c = D3DCOLOR_XRGB(255, 0, 0);
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-fMax, 0, 0), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(fMax, 0, 0), c));

	c = D3DCOLOR_XRGB(0, 255, 0);
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(0, -fMax, 0), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(0, fMax, 0), c));

	c = D3DCOLOR_XRGB(0, 0, 255);
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(0, 0, -fMax), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(0, 0, fMax), c));

	m_nLineNum = m_vecVertex.size() / 2;

	g_pD3DDevice->CreateVertexBuffer(
		m_vecVertex.size() * sizeof(ST_PC_VERTEX),
		0,
		ST_PC_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVB,
		0);

	void* pV;

	m_pVB->Lock(0, 0, &pV, 0);
	memcpy(pV, &m_vecVertex[0], m_vecVertex.size() * sizeof(ST_PC_VERTEX));
	m_pVB->Unlock();

	D3DXMATRIXA16 matS, matR, mat;
	D3DXMatrixScaling(&matS, 0.1f, 2.0f, 0.1f);
	cPyramid* pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI / 2.0f);
	mat = matS * matR;
	pPyramid->Setup(D3DCOLOR_XRGB(255, 0, 0), &mat);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new cPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI);
	mat = matS * matR;
	pPyramid->Setup(D3DCOLOR_XRGB(0, 255, 0), &mat);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new cPyramid;
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	mat = matS * matR;
	pPyramid->Setup(D3DCOLOR_XRGB(0, 0, 255), &mat);
	m_vecPyramid.push_back(pPyramid);
}

void cGrid::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTexture(0, NULL);

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	/*g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
	m_vecVertex.size() / 2,
	&m_vecVertex[0],
	sizeof(ST_PC_VERTEX));*/
	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PC_VERTEX));
	g_pD3DDevice->DrawPrimitive(D3DPT_LINELIST, 0, m_nLineNum);

	for each(auto p in m_vecPyramid)
	{
		p->Render();
	}
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}
