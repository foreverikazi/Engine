#include "pch.h"
#include "Input.h"

Input::Input() :
	mDirectInput(nullptr),
	mKeyboard(nullptr),
	mMouse(nullptr)
{
	ZeroMemory(mKeyboardState, sizeof(mKeyboardState));
	ZeroMemory(&mMouseState, sizeof(DIMOUSESTATE));
}

Input::~Input()
{
	ReleaseInput();
}

bool Input::InitializeInput(HINSTANCE hinstance, HWND hwnd)
{
	if (FAILED(DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mDirectInput, NULL)))
	{
		return false;
	}
	
	if (FAILED(InitializeKeyboard(hwnd)))
	{
		return false;
	}

	if (FAILED(InitializeMouse(hwnd)))
	{
		return false;
	}

	return true;
}

bool Input::InitializeKeyboard(HWND hwnd)
{
	if (FAILED(mDirectInput->CreateDevice(GUID_SysKeyboard, &mKeyboard, NULL)))
	{
		return false;
	}
	if (FAILED(mKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return false;
	}
	if (FAILED(mKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
	{
		return false;
	}
	if (FAILED(mKeyboard->Acquire()))
	{
		return false;
	}

	return true;
}

bool Input::InitializeMouse(HWND hwnd)
{
	if (FAILED(mDirectInput->CreateDevice(GUID_SysMouse, &mMouse, NULL)))
	{
		return false;
	}
	if (FAILED(mMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return false;
	}
	if (FAILED(mMouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return false;
	}
	if (FAILED(mMouse->Acquire()))
	{
		return false;
	}

	return true;
}

void Input::UpdateInput()
{
	HRESULT result;

	if (mKeyboard)
	{
		result = mKeyboard->GetDeviceState(sizeof(mKeyboardState), mKeyboardState);
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			mKeyboard->Acquire();
		}
	}
	
	if (mMouse)
	{
		result = mMouse->GetDeviceState(sizeof(mMouseState), &mMouseState);
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			mMouse->Acquire();
		}
	}
}

void Input::ReleaseInput()
{
	if (mKeyboard)
	{
		mKeyboard->Release();
		mKeyboard = nullptr;
	}

	if (mMouse)
	{
		mMouse->Release();
		mMouse = nullptr;
	}

	if (mDirectInput)
	{
		mDirectInput->Release();
		mDirectInput = nullptr;
	}
}
