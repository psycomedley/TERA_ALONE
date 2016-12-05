#include "stdafx.h"

struct ST_PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;

	ST_PC_VERTEX() : p(0, 0, 0), c(D3DCOLOR_XRGB(0, 0, 0)) {}
	ST_PC_VERTEX(D3DXVECTOR3 _p, D3DCOLOR _c) : p(_p), c(_c) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE, };
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2	t;

	ST_PT_VERTEX() : p(0, 0, 0), t(0, 0) {}
	ST_PT_VERTEX(D3DXVECTOR3 _p, D3DXVECTOR2 _t) : p(_p), t(_t) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1, };
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2	t;

	ST_PNT_VERTEX() : p(0, 0, 0), n(0, 0, 0), t(0, 0) {}
	ST_PNT_VERTEX(D3DXVECTOR3 _p, D3DXVECTOR3 _n, D3DXVECTOR2 _t) : p(_p), n(_n), t(_t) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, };
};


struct ST_BONE : public D3DXFRAME
{
	D3DXMATRIXA16 CombinedTransformationMatrix;
};


struct ST_BONE_MESH : public D3DXMESHCONTAINER
{
	vector<LPDIRECT3DTEXTURE9>	vecTexture;
	vector<D3DMATERIAL9>		vecMaterial;

	LPD3DXMESH			pOrigMesh;
	LPD3DXMESH			pWorkingMesh;
	D3DXMATRIXA16**		ppBoneMatrixPtrs;
	D3DXMATRIXA16*		pBoneOffsetMatrices;

	DWORD				dwNumPaletteEntries;
	DWORD				dwMaxNumFaceInfls;
	DWORD				dwNumAttrGroups;
	LPD3DXBUFFER		pBufBoneCombos;

	ST_BONE_MESH() : pOrigMesh(NULL), pWorkingMesh(NULL) {}
};


struct ST_ANIMATION_INFO
{
	int		nIndex;
	bool	bPlayOnce;
	bool	bBlend;

	ST_ANIMATION_INFO() : nIndex(-1), bPlayOnce(false), bBlend(true) {}
	ST_ANIMATION_INFO(int _nIndex, bool _bPlayOnce, bool _bBlend = true) : nIndex(_nIndex), bPlayOnce(_bPlayOnce), bBlend(_bBlend) {}

	void SetInfo(int _nIndex, bool _bPlayOnce, bool _bBlend) { nIndex = _nIndex; bPlayOnce = _bPlayOnce; bBlend = _bBlend; }
};


struct ST_UNIT_INFO
{
	string	sName;

	int		nMaxHp;
	int		nHp;
	int		nMaxMp;
	int		nMp;

	float	fDamage;
	float	fDefence;
};


struct ST_SKILL_INFO
{
	float	fCoolTime;
	float	fPassedTime;
	float	fValue;
	string	sSpeech;

	void SetInfo(float _fCoolTime, float _fValue, string _sSpeech = "") { fCoolTime = _fCoolTime; fPassedTime = 0; fValue = _fValue; sSpeech = _sSpeech; }
};


struct ST_TEXT
{
	E_FONT_TYPE		eFontType;
	string			sText;
	float			fShowTime;
	float			fPassedTime;
	RECT			rect;

	ST_TEXT() : eFontType(E_FONT_END), sText(""), fShowTime(0.0f), fPassedTime(0.0f) {}
	ST_TEXT(E_FONT_TYPE _eType, string _sText, float _fShowTime, RECT _rect) : eFontType(_eType), sText(_sText), fShowTime(_fShowTime), fPassedTime(0.0f), rect(_rect) {}
};