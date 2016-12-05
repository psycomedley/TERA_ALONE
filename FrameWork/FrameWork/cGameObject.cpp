#include "stdafx.h"
#include "cGameObject.h"
#include "cMesh.h"


cGameObject::cGameObject(void)
	: m_pMesh(NULL)
	, m_vScale(1, 1, 1)
	, m_vPosition(0, 0, 0)
	, m_fAngle(0)
	, m_vDirection(0, 0, 1)
	, m_pAction(NULL)
	, m_vPrevPosition(0, 0, 0)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matRevision);
}


cGameObject::~cGameObject(void)
{
	SAFE_RELEASE(m_pAction);
}

void cGameObject::Update()
{
	if (m_pAction)
		m_pAction->Update();
}

void cGameObject::Render()
{

}


void cGameObject::Bounding_Render()
{
	m_pMesh->Bounding_Render(m_vPosition, m_vScale);
}


void cGameObject::SetPosition(D3DXVECTOR3 vPos)
{
	m_vPosition = vPos;

//	if (m_pMesh)
//		m_pMesh->GetSphere()->SetCenter(D3DXVECTOR3(vPos.x, vPos.y + m_pMesh->GetSphere()->GetOriginalY(), vPos.z));
}


void cGameObject::SetBoundingPos()
{
	/*m_pMesh->GetBox()->SetPosition(m_vPosition);
	m_pMesh->GetSphere()->SetPosition(m_vPosition);*/
}

//임시  조금 변형할 것
void cGameObject::Move(float fSpeed)
{
	m_vPosition = m_vPosition - m_vDirection * fSpeed;
}


cBoundingBox cGameObject::GetBox()
{
	return m_pMesh->GetBox(m_vPosition);
}


cBoundingSphere cGameObject::GetSphere()
{
	return m_pMesh->GetSphere(m_vPosition, m_vScale.x);
}