#include "StdAfx.h"
#include "cPyramid.h"


cPyramid::cPyramid(void)
	: m_pVB(NULL)
	, m_nTriNum(NULL)
{
}


cPyramid::~cPyramid(void)
{
	SAFE_RELEASE(m_pVB);
}

void cPyramid::Setup(D3DCOLOR c, D3DXMATRIXA16* pmat /*= NULL*/)
{
	D3DXVECTOR3 p;
	p = D3DXVECTOR3(0, 0, 0); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3(1, -1, -1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));

	p = D3DXVECTOR3(0, 0, 0); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3(1, -1, 1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3(1, -1, -1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));

	p = D3DXVECTOR3(0, 0, 0); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3(-1, -1, 1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3(1, -1, 1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));

	p = D3DXVECTOR3(0, 0, 0); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3(-1, -1, 1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));

	p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3(1, -1, -1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3(1, -1, 1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));

	p = D3DXVECTOR3(-1, -1, -1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3(1, -1, 1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));
	p = D3DXVECTOR3(-1, -1, 1); m_vecVertex.push_back(ST_PC_VERTEX(p, c));

	if (pmat)
	{
		for (size_t i = 0; i < m_vecVertex.size(); ++i)
		{
			D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, pmat);
		}
	}

	m_nTriNum = m_vecVertex.size() / 3;

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
}

void cPyramid::Render()
{
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	/*g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
	m_vecVertex.size() / 3,
	&m_vecVertex[0],
	sizeof(ST_PC_VERTEX));*/
	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PC_VERTEX));
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_nTriNum);
}
