#include "stdafx.h"
#include "cMeshMgr.h"
#include "cStaticMesh.h"
#include "cDynamicMesh.h"

cMeshMgr::cMeshMgr()
{
}


cMeshMgr::~cMeshMgr()
{
}


cStaticMesh* cMeshMgr::GetStaticMesh(char* szFolder, char* szFile)
{
	string sFullPath(szFolder);
	sFullPath += string("/");
	sFullPath += string(szFile);

	if (m_mapStaticMesh.find(sFullPath) == m_mapStaticMesh.end())
	{
		cStaticMesh* pStaticMesh = new cStaticMesh();
		pStaticMesh->Load(szFolder, szFile);
		m_mapStaticMesh[sFullPath] = pStaticMesh;
	}
	return m_mapStaticMesh[sFullPath];
}


cDynamicMesh* cMeshMgr::GetDynamicMesh(char* szFolder, char* szFile)
{
	string sFullPath(szFolder);
	sFullPath += string("/");
	sFullPath += string(szFile);

	if (m_mapDynamicMesh.find(sFullPath) == m_mapDynamicMesh.end())
	{
		cDynamicMesh* pDynamicMesh = new cDynamicMesh();
		pDynamicMesh->Load(szFolder, szFile);
		m_mapDynamicMesh[sFullPath] = pDynamicMesh;
	}
	return m_mapDynamicMesh[sFullPath];
}


void cMeshMgr::Release()
{
	for each(auto it in m_mapDynamicMesh)
		it.second->Release();

	for each(auto it in m_mapStaticMesh)
		it.second->Release();

	cSingleton::Release();
}


D3DXMATRIXA16* cMeshMgr::GetMatrix(string sKey, string sBoneKey)
{
	auto p = m_mapDynamicMesh.find(sKey);
	if (p == m_mapDynamicMesh.end())
		return NULL;

	return p->second->GetMatrix(sBoneKey);
}