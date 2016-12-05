#pragma once
#include "cAction.h"

class cMesh;
class cGameObject : public cObject
{
protected:
	cMesh* m_pMesh;
	
	D3DXVECTOR3 m_vPosition;
	SYNTHESIZE(float, m_fAngle, Angle);
	SYNTHESIZE(D3DXVECTOR3, m_vScale, Scale);

	D3DXVECTOR3	m_vPrevPosition;
	SYNTHESIZE_ADD_REF(cAction*, m_pAction, Action);
	SYNTHESIZE(D3DXVECTOR3, m_vDirection, Direction);
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matWorld, WorldTM);

	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matRevision, Revision);

public:
	void Move(float fSpeed);

public:
	virtual cBoundingSphere GetSphere();
	virtual cBoundingBox GetBox();

public:
	D3DXVECTOR3 GetPosition() { return m_vPosition; }
	void SetPosition(D3DXVECTOR3 vPos);
	void SetBoundingPos();

public:
	virtual void Update();
	virtual void Render();
	void Bounding_Render();

public:
	cGameObject(void);
	virtual ~cGameObject(void);
};
