#include "stdafx.h"
#include "cMap.h"


cMap::cMap(char* szFolder, char* szFilename)
{
	m_pMesh = new cStaticMesh(szFolder, szFilename);
	D3DXMatrixIdentity(&m_matWorld);
}


cMap::cMap()
{
	D3DXMatrixIdentity(&m_matWorld);
}
cMap::~cMap()
{
}
void cMap::Update()
{
	
}
void cMap::Render()
{
	D3DXMATRIXA16	mat, matS, matT;
	D3DXMatrixIdentity(&mat);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, -110, -77, -300);
	D3DXMatrixScaling(&matS, 0.03f, 0.03f, 0.03f);
	mat = matS*matT;
	//m_matWorld = m_matWorld* mat;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	cStaticObj::Render();
}
bool cMap::GetHeight(IN float x, OUT float& y, IN float z)
{
	
	D3DXVECTOR3 rayPos(x, 1000, z);
	D3DXVECTOR3 rayDir(0, -1, 0);
	float u, v, d;
	BOOL Hit;
	D3DXVECTOR3 p1;
	D3DXVECTOR3 p2;
	D3DXVECTOR3 p3;
	vector<D3DXVECTOR3> vecVertex = *((cStaticMesh*)m_pMesh)->GetVecVertaxies();

	for (int i = 0; i < vecVertex.size(); i += 3)
	{
		p1 = vecVertex[i];
		p2 = vecVertex[i + 1];
		p3 = vecVertex[i + 2];
		if (D3DXIntersectTri(&p1, &p2, &p3, &rayPos, &rayDir, &u, &v, &d))
		{
			y = 1000 - d;
			return true;

		}
	}
	y = 0;
	return false;
}