#pragma once
#include "cGameObject.h"
#include "cBoundingBox.h"
#include "cBoundingSphere.h"

class cMesh
{
protected:
	SYNTHESIZE(D3DXVECTOR3, m_vMin, vMin);
	SYNTHESIZE(D3DXVECTOR3, m_vMax, vMax);

	cBoundingBox* m_pBox;
	cBoundingSphere* m_pSphere;

public:
	virtual HRESULT Load(char* szFolder, char* szFile) PURE;

public:
	HRESULT SetupBounding(D3DXVECTOR3 vMin, D3DXVECTOR3 vMax);
	cBoundingBox GetBox(D3DXVECTOR3 vPosition);
	cBoundingSphere GetSphere(D3DXVECTOR3 vPosition, float fScale);

public:
	virtual void Render();
	void Bounding_Render(D3DXVECTOR3 vPos, D3DXVECTOR3 vScale);
	virtual void Release();

public:
	cMesh();
	~cMesh();
};

