#pragma once
#include"cStaticMesh.h"
#include"cStaticObj.h"

class cMap:public cStaticObj
{
private:
	D3DXMATRIXA16			m_matWorld;


public:
	cMap(char* szFolder, char* szFilename);
	~cMap();

	virtual void Update() override;
	virtual void Render() override;

	bool GetHeight(IN float x, OUT float& y, IN float z);

private:
	cMap();
};

