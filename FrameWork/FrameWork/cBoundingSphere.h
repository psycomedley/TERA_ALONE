#pragma once
#include "cBounding.h"

class cBoundingSphere : public cBounding
{
private:
	LPD3DXMESH		m_pSphereMesh;

	SYNTHESIZE(D3DXVECTOR3, m_vCenter, Center);
	SYNTHESIZE(float, m_fRadius, Radius);
	SYNTHESIZE(float, m_fOriginalY, OriginalY);
	SYNTHESIZE(float, m_fOriginalRadius, OriginalRadius);

public:
	HRESULT Setup(D3DXVECTOR3* pCenter = &D3DXVECTOR3(0, 0, 0), float fRadius = 0,
		UINT nSlices = 20, UINT nStacks = 20);
	void Render(D3DXVECTOR3 vPos, D3DXVECTOR3 vScale);
	void Release();

public:
	cBoundingSphere();
	~cBoundingSphere();
};

