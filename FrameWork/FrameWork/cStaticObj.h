#pragma once
#include "cGameObject.h"

class cStaticMesh;
class cStaticObj : public cGameObject
{
public:
	virtual void Update();
	virtual void Render() override;

public:
	cStaticObj(char* szFolder, char* szFilename);
	cStaticObj();
	~cStaticObj();
};

