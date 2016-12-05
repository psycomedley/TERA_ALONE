#include "stdafx.h"
#include "cCube.h"


cCube::cCube()
	: m_vPosition(0, 0, 0)
	, m_fAngle(0.f)
	, m_fSpeed(0.3f)
{
}


cCube::~cCube()
{
}


void cCube::Setup()
{
	/*g_pD3DDevice->CreateVertexBuffer(
	8 * sizeof(ST_PC_VERTEX),
	D3DUSAGE_WRITEONLY,
	ST_PC_VERTEX::FVF,
	D3DPOOL_MANAGED,
	&VB,
	0);

	g_pD3DDevice->CreateIndexBuffer(
	36 * sizeof(WORD),
	D3DUSAGE_WRITEONLY,
	D3DFMT_INDEX16,
	D3DPOOL_MANAGED,
	&IB,
	0);

	ST_PC_VERTEX* vertex;
	VB->Lock(0, 0, (void**)&vertex, 0);

	vertex[0] = { -1, -1, -1 };
	vertex[1] = { -1, 1, -1 };
	vertex[2] = { 1, 1, -1 };
	vertex[3] = { 1, -1, -1 };
	vertex[4] = { -1, -1, 1 };
	vertex[5] = { -1, 1, 1 };
	vertex[6] = { 1, 1, 1 };
	vertex[7] = { 1, -1, 1 };

	VB->Unlock();

	WORD* index = 0;
	IB->Lock(0, 0, (void**)&index, 0);

	index[0] = 0; index[1] = 1; index[2] = 2;
	index[3] = 0; index[4] = 2; index[5] = 3;
	index[6] = 4; index[7] = 6; index[8] = 5;
	index[9] = 4; index[10] = 7; index[11] = 6;
	index[12] = 4; index[13] = 5; index[14] = 1;
	index[15] = 4; index[16] = 1; index[17] = 0;
	index[18] = 3; index[19] = 2; index[20] = 6;
	index[21] = 3; index[22] = 6; index[23] = 7;
	index[24] = 1; index[25] = 5; index[26] = 6;
	index[27] = 1; index[28] = 6; index[29] = 2;
	index[30] = 4; index[31] = 0; index[32] = 3;
	index[33] = 4; index[34] = 3; index[35] = 7;

	IB->Unlock();*/

	vertex[0] = {D3DXVECTOR3(-1, -1, -1), D3DCOLOR_XRGB(122, 122, 122) };
	vertex[1] = {D3DXVECTOR3(-1, 1, -1), D3DCOLOR_XRGB(122, 122, 122) };
	vertex[2] = {D3DXVECTOR3(1, 1, -1), D3DCOLOR_XRGB(122, 122, 122) };

	vertex[3] = {D3DXVECTOR3(-1, -1, -1), D3DCOLOR_XRGB(122, 122, 122) };
	vertex[4] = {D3DXVECTOR3(1, 1, -1), D3DCOLOR_XRGB(122, 122, 122) };
	vertex[5] = {D3DXVECTOR3(1, -1, -1), D3DCOLOR_XRGB(122, 122, 122) };

	vertex[6] = { D3DXVECTOR3(-1, -1, 1), D3DCOLOR_XRGB(122, 30, 122) };
	vertex[7] = { D3DXVECTOR3(1, 1, 1), D3DCOLOR_XRGB(122, 30, 122) };
	vertex[8] = { D3DXVECTOR3(-1, 1, 1), D3DCOLOR_XRGB(122, 30, 122) };

	vertex[9] = { D3DXVECTOR3(-1, -1, 1), D3DCOLOR_XRGB(122, 30, 122) };
	vertex[10] = {D3DXVECTOR3( 1, -1, 1), D3DCOLOR_XRGB(122, 30, 122) };
	vertex[11] = {D3DXVECTOR3( 1, 1, 1), D3DCOLOR_XRGB(122, 30, 122) };

	vertex[12] = {D3DXVECTOR3(-1, -1, 1), D3DCOLOR_XRGB(200, 122, 122) };
	vertex[13] = {D3DXVECTOR3(-1, 1, 1), D3DCOLOR_XRGB(200, 122, 122) };
	vertex[14] = {D3DXVECTOR3(-1, 1, -1), D3DCOLOR_XRGB(200, 122, 122) };

	vertex[15] = { D3DXVECTOR3(-1, -1, 1), D3DCOLOR_XRGB(200, 122, 122) };
	vertex[16] = { D3DXVECTOR3(-1, 1, -1), D3DCOLOR_XRGB(200, 122, 122) };
	vertex[17] = { D3DXVECTOR3(-1, -1, -1), D3DCOLOR_XRGB(200, 122, 122) };

	vertex[18] = { D3DXVECTOR3(1, -1, -1), D3DCOLOR_XRGB(122, 122, 200) };
	vertex[19] = { D3DXVECTOR3(1, 1, -1), D3DCOLOR_XRGB(122, 122, 200) };
	vertex[20] = { D3DXVECTOR3(1, 1, 1), D3DCOLOR_XRGB(122, 122, 200) };

	vertex[21] = { D3DXVECTOR3(1, -1, -1), D3DCOLOR_XRGB(122, 122, 200) };
	vertex[22] = { D3DXVECTOR3(1, 1, 1), D3DCOLOR_XRGB(122, 122, 200) };
	vertex[23] = { D3DXVECTOR3(1, -1, 1), D3DCOLOR_XRGB(122, 122, 200) };

	vertex[24] = { D3DXVECTOR3(-1, 1, -1), D3DCOLOR_XRGB(122, 200, 30) };
	vertex[25] = { D3DXVECTOR3(-1, 1, 1), D3DCOLOR_XRGB(122, 200, 30) };
	vertex[26] = { D3DXVECTOR3(1, 1, 1), D3DCOLOR_XRGB(122, 200, 30) };

	vertex[27] = {D3DXVECTOR3(-1, 1, -1), D3DCOLOR_XRGB(122, 200, 30) };
	vertex[28] = {D3DXVECTOR3(1, 1, 1), D3DCOLOR_XRGB(122, 200, 30) };
	vertex[29] = {D3DXVECTOR3(1, 1, -1), D3DCOLOR_XRGB(122, 200, 30) };

	vertex[30] = { D3DXVECTOR3(-1, -1, 1), D3DCOLOR_XRGB(180, 70, 122) };
	vertex[31] = { D3DXVECTOR3(-1, -1, -1), D3DCOLOR_XRGB(180, 70, 122) };
	vertex[32] = { D3DXVECTOR3(1, -1, -1), D3DCOLOR_XRGB(180, 70, 122) };

	vertex[33] = { D3DXVECTOR3(-1, -1, 1), D3DCOLOR_XRGB(180, 70, 122) };
	vertex[34] = { D3DXVECTOR3(1, -1, -1), D3DCOLOR_XRGB(180, 70, 122) };
	vertex[35] = { D3DXVECTOR3(1, -1, 1), D3DCOLOR_XRGB(180, 70, 122) };
}


void cCube::Update()
{
	if (GetKeyState('A') & 0x8000)
	{
		m_fAngle -= 0.1f;
	}
	if (GetKeyState('D') & 0x8000)
	{
		m_fAngle += 0.1f;
	}

	if (GetKeyState('W') & 0x8000)
	{
		m_vPosition = m_vPosition + m_vDirection * m_fSpeed;
	}
	if (GetKeyState('S') & 0x8000)
	{
		m_vPosition = m_vPosition - m_vDirection * m_fSpeed;
	}

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_fAngle);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matR * matT;

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	//큐브 방향을 회전한 방향으로 저장
	D3DXVec3TransformCoord(&m_vDirection, &m_vDirection, &matR);
}


void cCube::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		12,
		&vertex[0],
		sizeof(ST_PC_VERTEX));
}