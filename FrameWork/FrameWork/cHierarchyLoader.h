#pragma once

class cHierarchyLoader : public ID3DXAllocateHierarchy
{
protected:
	SYNTHESIZE(std::string, m_sDirectory, Directory);

	SYNTHESIZE(D3DXVECTOR3, m_vMin, vMin);
	SYNTHESIZE(D3DXVECTOR3, m_vMax, vMax);
	SYNTHESIZE(DWORD, m_dwDefaultPaletteSize, DefaultPaletteSize);
	SYNTHESIZE(DWORD, m_dwMaxPaletteSize, MaxPaletteSize);

public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame) override;
	STDMETHOD(CreateMeshContainer)(THIS_
		LPCSTR Name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer) override;
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree) override;
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree) override;

public:
	cHierarchyLoader();
	~cHierarchyLoader();
};

