#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"

EXTERN class SYSTEM_DLL Input
{
	DECLARE_SINGLE(Input);
public :
	bool InitializeInput(HINSTANCE hinstance, HWND hwnd);
	bool InitializeKeyboard(HWND hwnd);
	bool InitializeMouse(HWND hwnd);
	void UpdateInput();
	void ReleaseInput();

public :
	BOOL GetKeyBoardState(BYTE keyID) 
		{ return int(mKeyboardState[keyID] & 0x80);}
	const DIMOUSESTATE* GetMouseState() const
		{ return &mMouseState; }

public :
	Input();
	~Input();

private :
	IDirectInput8*			mDirectInput;
	IDirectInputDevice8*	mKeyboard;
	IDirectInputDevice8*	mMouse;
	BYTE					mKeyboardState[256];
	DIMOUSESTATE 			mMouseState;
};

