#pragma once
#include "cHierarchyLoader.h"
#include "cMesh.h"

class cAnimationController;
class cDynamicMesh : public cMesh
{
	friend class cMeshMgr;

protected:
	//�ϳ��� ����
	ST_BONE*					m_pRootFrame;
	DWORD						m_dwWorkingPaletteSize;
	D3DXMATRIX*					m_pmWorkingPalette;
	LPD3DXEFFECT				m_pEffect;

	// ��ü���� ����
	SYNTHESIZE(cAnimationController*, m_pAnimController, AnimController);
	
	/*LPD3DXANIMATIONCONTROLLER	m_pAnimController;

	float						m_fAnimBlendTime;
	float						m_fPassedAnimBlendTime;

	SYNTHESIZE(double, m_dPeriod, Period);
	SYNTHESIZE(bool, m_bPlayOnce, PlayOnce);*/

public:
//	bool IsExistAniController() { if (m_pAnimController) return true; return false; }
//	LPD3DXANIMATIONCONTROLLER GetAniController() { return m_pAnimController; }

	virtual void UpdateAndRender(D3DXMATRIXA16* pmat = NULL);

	D3DXMATRIXA16* GetMatrix(string sKey);

	void SetRandomTrackPosition(); // �׽�Ʈ��

	cDynamicMesh(char* szFolder, char* szFilename);
	~cDynamicMesh(void);

protected:
	cDynamicMesh();
	HRESULT Load(char* szDirectory, char* szFilename);
	LPD3DXEFFECT LoadEffect(char* szFilename);
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	void Render(ST_BONE* pBone = NULL);
	void SetupBoneMatrixPtrs(ST_BONE* pBone);
	void Release();

	void dlatl(ST_BONE* pBone, D3DXMATRIXA16* pmatParent = NULL);

public:
	void AddAnimation(ST_ANIMATION_INFO stAnimationInfo);
	void SetAnimationIdx(int nIdx, bool bPlayOnce = false);
	void SetAnimationIdxBlend(int nIdx, bool bPlayOnce = false);

	void AnimationStart();
	void AnimationNext();
	void AnimationRemove();
};

