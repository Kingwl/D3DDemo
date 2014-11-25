#pragma once
#ifndef _INITD3D_
#define _INITD3D_
#include "d3dx9.h"
#include "windows.h"
namespace d3d{
	bool initD3D(HINSTANCE hInstance, int width, int height, bool isWindow, D3DDEVTYPE deviceType, IDirect3DDevice9 **device);
	int EnterMsgLoop(bool(*ptr_display)(float timeDelta));
	LRESULT CALLBACK windProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	template <class T> void Release(T t)
	{
		if (t)
		{
			t->Release();
			t = nullptr;
		}
	}
	template <class T> void Delete(T t)
	{
		if (t)
		{
			delete t;
			t = nullptr;
		}
	}


}


#endif

