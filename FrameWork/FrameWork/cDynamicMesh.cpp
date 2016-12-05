#include "stdafx.h"
#include "cDynamicMesh.h"
#include "cMtlTex.h"
#include "cAnimationController.h"


cDynamicMesh::cDynamicMesh(char* szFolder, char* szFilename)
	: m_pRootFrame(NULL)
	, m_pAnimController(NULL)
	, m_dwWorkingPaletteSize(0)
	, m_pmWorkingPalette(NULL)
	, m_pEffect(NULL)
{
	cDynamicMesh* pDynamicdMesh = GETSINGLE(cMeshMgr)->GetDynamicMesh(szFolder, szFilename);

	m_pRootFrame = pDynamicdMesh->m_pRootFrame;
	m_dwWorkingPaletteSize = pDynamicdMesh->m_dwWorkingPaletteSize;
	m_pmWorkingPalette = pDynamicdMesh->m_pmWorkingPalette;
	m_pEffect = pDynamicdMesh->m_pEffect;
	m_pBox = pDynamicdMesh->m_pBox;
	m_pSphere = pDynamicdMesh->m_pSphere;

	m_pAnimController = new cAnimationController;
	m_pAnimController->m_fAnimBlendTime = pDynamicdMesh->m_pAnimController->m_fAnimBlendTime;
	m_pAnimController->m_fPassedAnimBlendTime = pDynamicdMesh->m_pAnimController->m_fPassedAnimBlendTime;

	pDynamicdMesh->m_pAnimController->m_pController->CloneAnimationController(
		pDynamicdMesh->m_pAnimController->m_pController->GetMaxNumAnimationOutputs(),
		pDynamicdMesh->m_pAnimController->m_pController->GetMaxNumAnimationSets(),
		pDynamicdMesh->m_pAnimController->m_pController->GetMaxNumTracks(),
		pDynamicdMesh->m_pAnimController->m_pController->GetMaxNumEvents(),
		&m_pAnimController->m_pController);
}


cDynamicMesh::cDynamicMesh()
	: m_pRootFrame(NULL)
	, m_pAnimController(NULL)
	, m_dwWorkingPaletteSize(0)
	, m_pmWorkingPalette(NULL)
	, m_pEffect(NULL)
{
}


cDynamicMesh::~cDynamicMesh()
{
	//	SAFE_DELETE(m_pFrame);
}


HRESULT cDynamicMesh::Load(char* szFolder, char* szFile)
{
	m_pAnimController = new cAnimationController;

	m_pEffect = LoadEffect("MultiAnimation.hpp");

	int nPaletteSize = 0;
	m_pEffect->GetInt("MATRIX_PALETTE_SIZE", &nPaletteSize);

	cHierarchyLoader ah;
	ah.SetDirectory(szFolder);
	ah.SetDefaultPaletteSize(nPaletteSize);

	std::string sFullPath(szFolder);
	sFullPath += std::string("/");
	sFullPath += std::string(szFile);

	D3DXLoadMeshHierarchyFromX(sFullPath.c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&ah,
		NULL,
		(LPD3DXFRAME*)&m_pRootFrame,
		&m_pAnimController->m_pController);

	if (m_pmWorkingPalette)
		delete[] m_pmWorkingPalette;

	m_dwWorkingPaletteSize = ah.GetMaxPaletteSize();
	m_pmWorkingPalette = new D3DXMATRIX[m_dwWorkingPaletteSize];
	if (m_pmWorkingPalette == NULL)
	{
		m_dwWorkingPaletteSize = 0;
	}

	if (m_pRootFrame)
		SetupBoneMatrixPtrs(m_pRootFrame);

	//임시 바운딩 만들어야하는데 나중에 변경합시다
//	dlatl(m_pRootFrame);
	
	SetupBounding(ah.GetvMin(), ah.GetvMax());

	return S_OK;
}


void cDynamicMesh::UpdateAndRender(D3DXMATRIXA16* pmat)
{
	if (m_pAnimController)
	{
		m_pAnimController->Update();
	//	if (m_pAnimController->m_bPlayOnce)
	//	{
	//		D3DXTRACK_DESC td;
	//		m_pAnimController->m_pController->GetTrackDesc(0, &td);
	//		if (td.Position <= m_pAnimController->m_dPeriod)
	//			m_pAnimController->m_pController->AdvanceTime(GETSINGLE(cTimeMgr)->getElapsedTime(), NULL);
	//	}
	//	else
	//		m_pAnimController->m_pController->AdvanceTime(GETSINGLE(cTimeMgr)->getElapsedTime(), NULL);
	//}

	////Blend
	//if (m_pAnimController->m_fPassedAnimBlendTime < m_pAnimController->m_fAnimBlendTime)
	//{
	//	m_pAnimController->m_fPassedAnimBlendTime += GETSINGLE(cTimeMgr)->getElapsedTime(); //블랜딩 시작
	//	if (m_pAnimController->m_fPassedAnimBlendTime > m_pAnimController->m_fAnimBlendTime) //블랜딩 시간이 끝나면
	//	{
	//		m_pAnimController->m_pController->SetTrackWeight(0, 1.0f); //0번의 웨이트 고정
	//		m_pAnimController->m_pController->SetTrackEnable(1, false); //1번 트랙은 꺼줌
	//	}
	//	else
	//	{
	//		float f = m_pAnimController->m_fPassedAnimBlendTime / m_pAnimController->m_fAnimBlendTime; //비율을 구해서
	//		m_pAnimController->m_pController->SetTrackWeight(0, f);      //0번 트랙의 가중치를 0->1로
	//		m_pAnimController->m_pController->SetTrackWeight(1, 1 - f);  //1번 트랙의 가중치를 1->0으로
	//	}
	}

	if (m_pRootFrame)
	{
		Update(m_pRootFrame, pmat);
		Render(m_pRootFrame);
	}
}


void cDynamicMesh::Render(ST_BONE* pBone /*= NULL*/)
{
	assert(pBone);

	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.
	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;

		// get bone combinations
		LPD3DXBONECOMBINATION pBoneCombos =
			(LPD3DXBONECOMBINATION)(pBoneMesh->pBufBoneCombos->GetBufferPointer());

		D3DXMATRIXA16 matViewProj, matView, matProj;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
		matViewProj = matView * matProj;

		D3DXMATRIXA16 mView, mInvView;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &mView);
		D3DXMatrixInverse(&mInvView, 0, &mView);
		D3DXVECTOR3 vEye = D3DXVECTOR3(0, 0, 0);
		D3DXVec3TransformCoord(&vEye, &vEye, &mInvView);

		// for each palette
		for (DWORD dwAttrib = 0; dwAttrib < pBoneMesh->dwNumAttrGroups; ++dwAttrib)
		{
			// set each transform into the palette
			for (DWORD dwPalEntry = 0; dwPalEntry < pBoneMesh->dwNumPaletteEntries; ++dwPalEntry)
			{
				DWORD dwMatrixIndex = pBoneCombos[dwAttrib].BoneId[dwPalEntry];
				if (dwMatrixIndex != UINT_MAX)
				{
					m_pmWorkingPalette[dwPalEntry] =
						pBoneMesh->pBoneOffsetMatrices[dwMatrixIndex] *
						(*pBoneMesh->ppBoneMatrixPtrs[dwMatrixIndex]);
				}
			}

			// set the matrix palette into the effect
			m_pEffect->SetMatrixArray("amPalette",
				m_pmWorkingPalette,
				pBoneMesh->dwNumPaletteEntries);

			m_pEffect->SetMatrix("g_mViewProj", &matViewProj);
			m_pEffect->SetVector("vLightDiffuse", &D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
			m_pEffect->SetVector("vWorldLightPos", &D3DXVECTOR4(500.0f, 500.0f, 500.0f, 1.0f));
			m_pEffect->SetVector("vWorldCameraPos", &D3DXVECTOR4(vEye, 1.0f));
			m_pEffect->SetVector("vMaterialAmbient", &D3DXVECTOR4(0.53f, 0.53f, 0.53f, 0.53f));
			m_pEffect->SetVector("vMaterialDiffuse", &D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

			// we're pretty much ignoring the materials we got from the x-file; just set
			// the texture here
			m_pEffect->SetTexture("g_txScene", pBoneMesh->vecTexture[pBoneCombos[dwAttrib].AttribId]);

			// set the current number of bones; this tells the effect which shader to use
			m_pEffect->SetInt("CurNumBones", pBoneMesh->dwMaxNumFaceInfls - 1);

			// set the technique we use to draw
			m_pEffect->SetTechnique("Skinning20");

			UINT uiPasses, uiPass;

			// run through each pass and draw
			m_pEffect->Begin(&uiPasses, 0);
			for (uiPass = 0; uiPass < uiPasses; ++uiPass)
			{
				m_pEffect->BeginPass(uiPass);
				pBoneMesh->pWorkingMesh->DrawSubset(dwAttrib);
				m_pEffect->EndPass();
			}
			m_pEffect->End();
		}
	}

	//재귀적으로 모든 프레임에 대해서 실행.
	if (pBone->pFrameSibling)
		Render((ST_BONE*)pBone->pFrameSibling);

	if (pBone->pFrameFirstChild)
		Render((ST_BONE*)pBone->pFrameFirstChild);
}


LPD3DXEFFECT cDynamicMesh::LoadEffect(char* szFilename)
{
	LPD3DXEFFECT pEffect = NULL;

	D3DXMACRO mac[2] =
	{
		{ "MATRIX_PALETTE_SIZE_DEFAULT", "35" },
		{ NULL, NULL }
	};

	D3DCAPS9 caps;
	D3DXMACRO *pmac = NULL;
	g_pD3DDevice->GetDeviceCaps(&caps);
	if (caps.VertexShaderVersion > D3DVS_VERSION(1, 1))
		pmac = mac;

	DWORD dwShaderFlags = 0;

#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DXSHADER_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

#ifdef DEBUG_VS
	dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
	dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif

	ID3DXBuffer* pBuffer = NULL;
	if (FAILED(D3DXCreateEffectFromFile(g_pD3DDevice,
		szFilename,
		pmac,
		NULL,
		dwShaderFlags,
		NULL,
		&pEffect,
		&pBuffer)))
	{
		// if creation fails, and debug information has been returned, output debug info
		if (pBuffer)
		{
			OutputDebugStringA((char*)pBuffer->GetBufferPointer());
			SAFE_RELEASE(pBuffer);
		}

		return NULL;
	}

	return pEffect;
}


void cDynamicMesh::Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent)
{
	pCurrent->CombinedTransformationMatrix = pCurrent->TransformationMatrix;
	if (pmatParent)
	{
		pCurrent->CombinedTransformationMatrix =
			pCurrent->CombinedTransformationMatrix * (*pmatParent);
	}

	if (pCurrent->pFrameSibling)
		Update((ST_BONE*)pCurrent->pFrameSibling, pmatParent);

	if (pCurrent->pFrameFirstChild)
		Update((ST_BONE*)pCurrent->pFrameFirstChild, &(pCurrent->CombinedTransformationMatrix));
}


void cDynamicMesh::SetupBoneMatrixPtrs(ST_BONE* pBone)
{
	assert(pBone);

	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.
	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		if (pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			// pSkinInfo->GetNumBones() 으로 영향받는 본의 개수를 찾음.
			// pSkinInfo->GetBoneName(i) 로 i번 프레임의 이름을 찾음
			// D3DXFrameFind(루트 프레임, 프레임 이름) 로 프레임을 찾음.
			// 찾아서 월드매트릭스를 걸어줘라.
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				LPCSTR szBoneName = pSkinInfo->GetBoneName(i);
				if (szBoneName == NULL || strlen(szBoneName) == 0)
					continue;
				ST_BONE* pInfluence = (ST_BONE*)D3DXFrameFind(m_pRootFrame, szBoneName);
				pBoneMesh->ppBoneMatrixPtrs[i] = &(pInfluence->CombinedTransformationMatrix);
			}
		}
	}

	//재귀적으로 모든 프레임에 대해서 실행.
	if (pBone->pFrameSibling)
		SetupBoneMatrixPtrs((ST_BONE*)pBone->pFrameSibling);

	if (pBone->pFrameFirstChild)
		SetupBoneMatrixPtrs((ST_BONE*)pBone->pFrameFirstChild);
}


void cDynamicMesh::Release()
{
	cHierarchyLoader ah;
	D3DXFrameDestroy((LPD3DXFRAME)m_pRootFrame, &ah);
	SAFE_DELETE_ARRAY(m_pmWorkingPalette);
	SAFE_RELEASE(m_pEffect);

	cMesh::Release();
}

//안씀
void cDynamicMesh::SetRandomTrackPosition()
{
	m_pAnimController->m_pController->SetTrackPosition(0, (rand() % 100) / 10.0f);
}


void cDynamicMesh::AddAnimation(ST_ANIMATION_INFO stAnimationInfo)
{
	m_pAnimController->AddAnimation(stAnimationInfo);
}


void cDynamicMesh::SetAnimationIdx(int nIdx, bool bPlayOnce)
{
	m_pAnimController->SetAnimationIdx(nIdx, bPlayOnce);
	/*if (!m_pAnimController)
		return;

	m_pAnimController->m_bPlayOnce = bPlayOnce;

	LPD3DXANIMATIONSET pAnimationSet = NULL;
	m_pAnimController->m_pController->GetAnimationSet(nIdx, &pAnimationSet);

	if (pAnimationSet)
		m_pAnimController->m_dPeriod = pAnimationSet->GetPeriod();


	m_pAnimController->m_pController->GetAnimationSet(nIdx, &pAnimationSet);
	m_pAnimController->m_pController->SetTrackAnimationSet(0, pAnimationSet);
	SAFE_RELEASE(pAnimationSet);*/
}


void cDynamicMesh::SetAnimationIdxBlend(int nIdx, bool bPlayOnce)
{
	m_pAnimController->SetAnimationIdxBlend(nIdx, bPlayOnce);
	/*if (!m_pAnimController)
		return;

	m_pAnimController->m_bPlayOnce = bPlayOnce;

	LPD3DXANIMATIONSET pAnimationSet = NULL;
	m_pAnimController->m_pController->GetAnimationSet(nIdx, &pAnimationSet);

	if (pAnimationSet)
		m_pAnimController->m_dPeriod = pAnimationSet->GetPeriod();


	LPD3DXANIMATIONSET pPrevAnimSet = NULL;
	LPD3DXANIMATIONSET pNextAnimSet = NULL;

	m_pAnimController->m_pController->GetTrackAnimationSet(0, &pPrevAnimSet);
	m_pAnimController->m_pController->GetAnimationSet(nIdx, &pNextAnimSet);

	D3DXTRACK_DESC stTrackDest;
	m_pAnimController->m_pController->GetTrackDesc(0, &stTrackDest);
	m_pAnimController->m_pController->SetTrackDesc(1, &stTrackDest);

	m_pAnimController->m_pController->SetTrackAnimationSet(0, pNextAnimSet);
	m_pAnimController->m_pController->SetTrackAnimationSet(1, pPrevAnimSet);

	m_pAnimController->m_pController->SetTrackWeight(0, 0.0f);
	m_pAnimController->m_pController->SetTrackWeight(1, 1.0f);

	SAFE_RELEASE(pPrevAnimSet);
	SAFE_RELEASE(pNextAnimSet);

	m_pAnimController->m_fPassedAnimBlendTime = 0.0f;
	m_pAnimController->m_pController->SetTrackPosition(0, 0);*/
}


void cDynamicMesh::AnimationStart()
{
	m_pAnimController->AnimationStart();
}


void cDynamicMesh::AnimationNext()
{
	m_pAnimController->AnimationNext();
}


void cDynamicMesh::AnimationRemove()
{
	m_pAnimController->AnimationRemove();
}


D3DXMATRIXA16* cDynamicMesh::GetMatrix(string sKey)
{
	ST_BONE* pBone = (ST_BONE*)D3DXFrameFind(m_pRootFrame, sKey.c_str());
	if (pBone)
		return &pBone->CombinedTransformationMatrix;
	return NULL;
}

//임시
void cDynamicMesh::dlatl(ST_BONE* pBone, D3DXMATRIXA16* pmatParent)
{
	D3DXVECTOR3 vMin(FLT_MAX, FLT_MAX, FLT_MAX);
	D3DXVECTOR3 vMax(FLT_MIN, FLT_MIN, FLT_MIN);

	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		
		LPVOID pV = NULL;
		pBoneMesh->pOrigMesh->LockVertexBuffer(0, &pV);
		
		D3DXComputeBoundingBox((D3DXVECTOR3*)pV,
			pBoneMesh->pOrigMesh->GetNumVertices(),
			D3DXGetFVFVertexSize(pBoneMesh->pOrigMesh->GetFVF()),
			&vMin,
			&vMax);
		
		D3DXVec3Minimize(&m_vMin, &m_vMin, &vMin);
		D3DXVec3Maximize(&m_vMax, &m_vMax, &vMax);
		pBoneMesh->pOrigMesh->UnlockVertexBuffer();
	}

	if (pBone->pFrameSibling)
		dlatl((ST_BONE*)pBone->pFrameSibling, pmatParent);

	if (pBone->pFrameFirstChild)
		dlatl((ST_BONE*)pBone->pFrameFirstChild, pmatParent);
}


