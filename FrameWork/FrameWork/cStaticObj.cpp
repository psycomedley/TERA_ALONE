#include "stdafx.h"
#include "cStaticObj.h"
#include "cStaticMesh.h"


cStaticObj::cStaticObj(char* szFolder, char* szFilename)
{
	m_pMesh = new cStaticMesh(szFolder, szFilename);
	SetBoundingPos();
}


cStaticObj::cStaticObj()
{
}


cStaticObj::~cStaticObj()
{
}


void cStaticObj::Update()
{
	if (m_pMesh)
		((cStaticMesh*)m_pMesh)->Update();
}


void cStaticObj::Render()
{
	//D3DXMATRIXA16 matS, matT, matI, mat;
	//D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	//D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
	//mat = matS * matT;

	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);

	if (m_pMesh)
		((cStaticMesh*)m_pMesh)->Render();

	//D3DXMatrixIdentity(&matI);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
}