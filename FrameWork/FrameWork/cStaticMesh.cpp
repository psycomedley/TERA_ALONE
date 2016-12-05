#include "stdafx.h"
#include "cStaticMesh.h"


cStaticMesh::cStaticMesh(char* szFolder, char* szFilename)
{
	cStaticMesh* pStaticdMesh = GETSINGLE(cMeshMgr)->GetStaticMesh(szFolder, szFilename);

	m_pMesh = pStaticdMesh->m_pMesh;
	m_pSubSetBuffer = pStaticdMesh->m_pSubSetBuffer;
	m_dwSubSetCnt = pStaticdMesh->m_dwSubSetCnt;
	m_pMaterials = pStaticdMesh->m_pMaterials;
	vecTexture = pStaticdMesh->vecTexture;
	vecMaterial = pStaticdMesh->vecMaterial;

	m_pBox = pStaticdMesh->m_pBox;
	m_pSphere = pStaticdMesh->m_pSphere;

	m_vecVertaxies = pStaticdMesh->m_vecVertaxies;
}


cStaticMesh::cStaticMesh()
{
}


cStaticMesh::~cStaticMesh()
{	
}


HRESULT cStaticMesh::Load(char* szFolder, char* szFile)
{
	std::string sFullPath(szFolder);
	sFullPath += std::string("/");
	sFullPath += std::string(szFile);

	if (FAILED(D3DXLoadMeshFromX(sFullPath.c_str(), D3DXMESH_MANAGED, g_pD3DDevice, NULL, &m_pSubSetBuffer
		, NULL, &m_dwSubSetCnt, &m_pMesh)))
	{
		MSGBOX("Static Mesh Load Fail");
		return E_FAIL;
	}

	m_pMaterials = (D3DXMATERIAL*)m_pSubSetBuffer->GetBufferPointer();

	vecMaterial.resize(m_dwSubSetCnt);
	vecTexture.resize(m_dwSubSetCnt);

	for (DWORD i = 0; i < m_dwSubSetCnt; ++i)
	{
		std::string szTmp;

		vecMaterial[i] = m_pMaterials[i].MatD3D;

		if (m_pMaterials[i].pTextureFilename)
		{
			std::string sFilename(m_pMaterials[i].pTextureFilename);
			std::string sPath = szFolder + string("/") + sFilename;
			LPDIRECT3DTEXTURE9 pTex = GETSINGLE(cTextureMgr)->GetTexture(sPath);
			vecTexture[i] = pTex;
		}
	}

	void*		pVtx = NULL;
	m_pMesh->LockVertexBuffer(0, &pVtx);
	DWORD dwVtxCnt = m_pMesh->GetNumVertices();
	D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE];
	m_pMesh->GetDeclaration(decl);
	UINT nSize = D3DXGetDeclVertexSize(decl, 0);
	m_pMesh->UnlockVertexBuffer();

	if (FAILED(D3DXComputeBoundingBox((D3DXVECTOR3*)pVtx, dwVtxCnt, nSize, &m_vMin, &m_vMax)))
	{
		MSGBOX("Static Mesh BoundingBox Make Fail");
		return E_FAIL;
	}

	SetupBounding(m_vMin, m_vMax);

	//스테틱매쉬 버텍스및 인덱스 얻기
	vector<ST_PNT_VERTEX>		m_vecPNTVertaxies;
	vector<WORD>				m_vecIndecies;
	WORD* index;

	ST_PNT_VERTEX* vertices;
	m_pMesh->GetVertexBuffer(&m_VB);
	vertices = new ST_PNT_VERTEX[m_pMesh->GetNumVertices()];


	void* pVerties;
	m_VB->Lock(0, 0, (void**)&pVerties, 0);
	memcpy(vertices, pVerties, sizeof(ST_PNT_VERTEX)*m_pMesh->GetNumVertices());

	m_vecPNTVertaxies.resize(m_pMesh->GetNumVertices());
	for (int i = 0; i < m_pMesh->GetNumVertices(); ++i)
	{
		m_vecPNTVertaxies[i] = vertices[i];
	}
	m_VB->Unlock();


	m_pMesh->GetIndexBuffer(&m_IB);
	index = new WORD[m_pMesh->GetNumFaces() * 3];

	void* pInedex;
	m_IB->Lock(0, 0, (void**)&pInedex, 0);
	memcpy(index, pInedex, sizeof(WORD)*m_pMesh->GetNumFaces());

	for (int i = 0; i < m_pMesh->GetNumFaces(); ++i)
	{
		m_vecIndecies.push_back(index[i]);
	}
	m_IB->Unlock();

	//와인딩된 버텍스 넘기기
	m_vecVertaxies.resize(m_vecIndecies.size());
	for (int i = 0; i < m_vecIndecies.size(); ++i)
	{
		m_vecVertaxies[i] = m_vecPNTVertaxies[m_vecIndecies[i]].p;
	}

	return S_OK;
}


void cStaticMesh::Update()
{

}


void cStaticMesh::Render()
{
	for (DWORD i = 0; i < m_dwSubSetCnt; ++i)
	{
		g_pD3DDevice->SetTexture(0, vecTexture[i]);
		g_pD3DDevice->SetMaterial(&vecMaterial[i]);
		m_pMesh->DrawSubset(i);
	}
}


void cStaticMesh::Release()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pSubSetBuffer);
	SAFE_RELEASE(m_VB);
	SAFE_RELEASE(m_IB);
	cMesh::Release();
}