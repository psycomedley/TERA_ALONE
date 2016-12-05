#include "stdafx.h"
#include "cWeapon.h"
#include "cStaticObj.h"


cWeapon::cWeapon(char* szFolder, char* szFilename) //: cStaticMesh(szDirectory, szFilename) 
	: m_sHolderKey("")
	, m_sParentKey("")
{
	m_pMesh = new cStaticMesh(szFolder, szFilename);
	m_matParent = NULL;

	D3DXMatrixIdentity(&m_matWorld);
}


cWeapon::cWeapon()
	: m_sHolderKey("")
	, m_sParentKey("")
{
	m_matParent = NULL;
	D3DXMatrixIdentity(&m_matWorld);
}


cWeapon::~cWeapon()
{
}


void cWeapon::Update()
{
//	m_matParent = GETSINGLE(cMeshMgr)->GetMatrix(m_sHolderKey, m_sParentKey);
//	m_matWorld = m_matParent;

	SetWorldMat();
}


void cWeapon::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	cStaticObj::Render();
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
}


HRESULT cWeapon::SetParentMat()
{
	if (m_sHolderKey == "" || m_sParentKey == "")
	{
		MSGBOX("SetParentMat Fail");
		return E_FAIL;
	}
	m_matParent = GETSINGLE(cMeshMgr)->GetMatrix(m_sHolderKey, m_sParentKey);
	return S_OK;
}


void cWeapon::SetWorldMat()
{
//	m_matWorld = *m_matParent;

	D3DXMATRIXA16 matR;
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2);
	m_matWorld = matR * *m_matParent;

	//float angleX = asinf(m_matParent->_23);
	//float angleY = asinf(m_matParent->_31);
	//float angleZ = asinf(m_matParent->_12);

	//m_matWorld._22 = cosf(angleX);
	//m_matWorld._23 = sinf(angleX);
	//m_matWorld._32 = -sinf(angleX);
	//m_matWorld._33 = cosf(angleX);

	//m_matWorld._11 = cosf(angleY);
	//m_matWorld._13 = -sinf(angleY);
	//m_matWorld._31 = sinf(angleY);
	//m_matWorld._33 = cosf(angleY);

	//m_matWorld._11 = cosf(angleZ);
	//m_matWorld._12 = -sinf(angleZ);
	//m_matWorld._21 = sinf(angleZ);
	//m_matWorld._22 = cosf(angleZ);

	//m_matWorld._41 = m_matParent->_41;
	//m_matWorld._42 = m_matParent->_42;
	//m_matWorld._43 = m_matParent->_43;
}