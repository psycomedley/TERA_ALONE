#include "stdafx.h"
#include "cBoundingSphere.h"


cBoundingSphere::cBoundingSphere()
	: m_vCenter(D3DXVECTOR3(0, 0, 0))
	, m_fRadius(0)
	, m_fOriginalY(0)
{
}


cBoundingSphere::~cBoundingSphere()
{
}


HRESULT cBoundingSphere::Setup(D3DXVECTOR3* pCenter, float fRadius, UINT nSlices, UINT nStacks)
{
	if (FAILED(D3DXCreateSphere(g_pD3DDevice, fRadius,
		nSlices, nStacks, &m_pSphereMesh, NULL)))
	{
		MSGBOX("Bounding Sphere Setup Fail");
		return E_FAIL;
	}

	m_vCenter = *pCenter;
	m_fRadius = fRadius;
	m_fOriginalY = m_vCenter.y;
	m_fOriginalRadius = m_fRadius;

	return S_OK;
}


void cBoundingSphere::Render(D3DXVECTOR3 vPos, D3DXVECTOR3 vScale)
{
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, vScale.x, vScale.y, vScale.z);
	D3DXMatrixTranslation(&matT,
		vPos.x,
		vPos.y + m_fOriginalY * vScale.y,
		vPos.z);
	mat = matS * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	m_pSphereMesh->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
}


void cBoundingSphere::Release()
{
	SAFE_RELEASE(m_pSphereMesh);
}