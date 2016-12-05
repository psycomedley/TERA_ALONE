#include "stdafx.h"
#include "cFontMgr.h"


cFontMgr::cFontMgr()
{
}


cFontMgr::~cFontMgr()
{
}


LPD3DXFONT cFontMgr::GetFont(E_FONT_TYPE eFontType)
{
	if (m_mapFont.find(eFontType) == m_mapFont.end())
	{
		D3DXFONT_DESC fd;
		ZeroMemory(&fd, sizeof(D3DXFONT_DESC));

		switch (eFontType)
		{
		case E_FONT_BOSS:
			fd.Height = 25;
			fd.Width = 12;
			fd.Weight = FW_NORMAL;
			fd.Italic = false;
			fd.CharSet = DEFAULT_CHARSET;
			fd.OutputPrecision = OUT_DEFAULT_PRECIS;
			fd.PitchAndFamily = FF_DONTCARE;
			strcpy_s(fd.FaceName, "±Ã¼­Ã¼");
//			AddFontResource("umberto.ttf");
//			strcpy_s(fd.FaceName, "umberto");
			D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[eFontType]);
			break;
		}
	}
	return m_mapFont[eFontType];
}


void cFontMgr::Release()
{
	for each(auto it in m_mapFont)
		SAFE_RELEASE(it.second);

	cSingleton::Release();
}