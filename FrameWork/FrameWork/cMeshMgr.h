#pragma once

class cMesh;
class cStaticMesh;
class cDynamicMesh;
class cBoundingSphere;
class cMeshMgr : public cSingleton<cMeshMgr>
{
private:
	map<string, cStaticMesh*>		m_mapStaticMesh;
	map<string, cDynamicMesh*>		m_mapDynamicMesh;
	map<string, cBoundingSphere*>	m_mapBoundingSphere;

public:
	cStaticMesh*	GetStaticMesh(char* szFolder, char* szFile);
	cDynamicMesh*	GetDynamicMesh(char* szFolder, char* szFile);

	D3DXMATRIXA16*	GetMatrix(string sKey, string sBoneKey);

	void Release();

public:
	cMeshMgr();
	~cMeshMgr();
};

