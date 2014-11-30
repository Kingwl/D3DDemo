#include "windows.h"
#include "d3dx9.h"
#include "initD3D.h"
#include "Vertex.hpp"
#include "Cube.h"
#include "LightManager.h"
#include "Mtrl.h"
#include "ShadowClass.h"
#include "TextureManager.h"
#include "vector"
#include "ShadowManager.h"
#include "MeshManager.h"

void fuck()
{
	::MessageBox(0, "fuck", 0, 0);
}
const int Width = 800;
const int Height = 600;

IDirect3DDevice9 *Device = nullptr;
D3DXVECTOR3 cubePos(0.0f, 3.0f, 5.0f);



bool Display(float timeDelta)
{
	static float radius = 10.0f;


	if (::GetAsyncKeyState(VK_UP) & 0x8000f)
		radius -= 2.0f * timeDelta;

	if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
		radius += 2.0f * timeDelta;


	static float angle = (3.0f * D3DX_PI) / 2.0f;

	if (::GetAsyncKeyState('A') & 0x8000f)
		angle -= 0.5f * timeDelta;

	if (::GetAsyncKeyState('S') & 0x8000f)
		angle += 0.5f * timeDelta;

	D3DXVECTOR3 position(cosf(angle) * radius, 5.0f, sinf(angle) * radius);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	Device->SetTransform(D3DTS_VIEW, &V);

	Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0xffffffff, 1.0f, 0);
	Device->BeginScene();

	MeshManager::getInstance()->Render();
	ShadowManager::getInstance()->Render();
	Device->EndScene();
	Device->Present(0, 0, 0, 0);
	return true;
}

bool Setup()
{
	D3DXVECTOR3 dir(0.717f, -0.707f, 0.717f);
	D3DXCOLOR color = d3d::WHITE;
	LightManager::getInstance()->setLight(LightManager::LightType::Directional, nullptr, &dir, &color,Device);
	LightManager::getInstance()->setLightState(true);
	Device->SetLight(0, LightManager::getInstance()->getLight());
	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, false);
	Device->SetRenderState(D3DRS_LIGHTING, true);
	
	D3DXVECTOR3 d;
	LightManager::getInstance()->getDir(&d);
	D3DXVECTOR4 light(d.x, d.y, d.z, 0.0f);
	D3DXPLANE p(0.0f, -1.0f, 0.0f, 0.0f);
	D3DXMATRIX cp;
	D3DXMatrixTranslation(&cp, cubePos.x, cubePos.y, cubePos.z);
	UINT P = MeshManager::getInstance()->addMesh(Device, "tiger.x",&cp);
	ShadowManager::getInstance()->addShadow(Device, ShadowInfo(&light, &p, &cubePos, MeshManager::getInstance()->getMesh(P)->getMeshPointer()));

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f,
		(float)Width / (float)Height,
		1.0f,
		1000.0);
	Device->SetTransform(D3DTS_PROJECTION, &proj);
	return true;
}
void Cleanup()
{
	MeshManager::getInstance()->clear();
}
LRESULT CALLBACK d3d::windProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			::DestroyWindow(hWnd);
		}
		else if (wParam == VK_SPACE)
		{
			bool s = LightManager::getInstance()->getLightState();
			LightManager::getInstance()->setLightState(!s);
		}
		break;
	default:
		break;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!d3d::initD3D(hInstance, Width, Height, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "initD3d failed", "error",0);
		return 0;
	}
	if (!Setup())
	{
		::MessageBox(0, "Setup failed", "error", 0);
		return 0;
	}
	d3d::EnterMsgLoop(Display);
	Cleanup();
	Device->Release();
	return 0;;
}