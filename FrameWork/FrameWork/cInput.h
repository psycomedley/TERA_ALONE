#pragma once
#include "cSingleton.h"
#include "cMouse.h"
#include "cKeyBoard.h"

//class iKeyState;
class cInput : public cSingleton<cInput>
{
private:
	LPDIRECTINPUT8			m_pInput;

	cMouse*					m_pMouse;
	cKeyBoard*				m_pKeyboard;

public:
	cMouse*		GetMouse() { return m_pMouse; }
	cKeyBoard*	GetKeyBoard() { return m_pKeyboard; }

public:
	HRESULT Setup(HINSTANCE hInst);
	void Update();
	void Release();

public:
	cInput();
	~cInput();
};

#define MOUSE cInput::GetInst()->GetMouse()
#define KEYBOARD cInput::GetInst()->GetKeyBoard()
