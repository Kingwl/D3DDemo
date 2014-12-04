#include "windows.h"
#include "d3dx9.h"
#include "Cube.h"
#include "Mtrl.h"
#include "vector"
#include "Camera.h"
#include "initD3D.h"
#include "Vertex.hpp"

#include "MeshManager.h"
#include "LightManager.h"
#include "ShadowManager.h"
#include "DeviceManager.h"
#include "TextureManager.h"
#include "Terrain.h"
void fuck()
{
	::MessageBox(0, "fuck", 0, 0);
}
const int Width = 800;
const int Height = 600;
Terrain *terrain = nullptr;
D3DXMATRIX World;
bool Display(float timeDelta)
{
	IDirect3DDevice9 *Device = DeviceManager::getInstance()->getDevice();

	if (::GetAsyncKeyState(VK_UP) & 0x8000f)
		Camera::getInstance()->pitch(-1.0f * timeDelta);
	if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
		Camera::getInstance()->pitch(1.0f * timeDelta);
	if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
		Camera::getInstance()->yaw(-4.0f * timeDelta);
	//if (::GetAsyncKeyState(VK_SHIFT) & 0x8000f)
	//	Camera::getInstance()->fly(4.0f * timeDelta);
	//if (::GetAsyncKeyState(VK_CONTROL) & 0x8000f)
	//	Camera::getInstance()->fly(-4.0f * timeDelta);
	if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
		Camera::getInstance()->yaw(4.0f * timeDelta);
	if (::GetAsyncKeyState('W') & 0x8000f)
		Camera::getInstance()->walk(8.0f * timeDelta);
	if (::GetAsyncKeyState('S') & 0x8000f)
		Camera::getInstance()->walk(-4.0f * timeDelta);
	if (::GetAsyncKeyState('A') & 0x8000f)
		Camera::getInstance()->strafe(-4.0f * timeDelta);
	if (::GetAsyncKeyState('D') & 0x8000f)
		Camera::getInstance()->strafe(4.0f * timeDelta);
	
	D3DXVECTOR3 pos;
	Camera::getInstance()->getPosition(&pos);
	pos.y = terrain->getHeight(pos.x, pos.z);
	Camera::getInstance()->setPosition(&pos);


	D3DXMATRIX V;
	Camera::getInstance()->getViewMatrix(&V);
	Device->SetTransform(D3DTS_VIEW, &V);

	Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0xffffffff, 1.0f, 0);
	Device->BeginScene();

	MeshManager::getInstance()->RenderPMesh();
	ShadowManager::getInstance()->Render();

	D3DXMatrixIdentity(&World);
	D3DXMatrixTranslation(&World, 0.0f, -10.0f, 0.0f);
	Device->SetTransform(D3DTS_WORLD, &World);
	Device->SetMaterial(&d3d::RED_MTRL);
	terrain->Render();
	Device->EndScene();
	Device->Present(0, 0, 0, 0);
	return true;
}

bool Setup()
{
	IDirect3DDevice9 *Device = DeviceManager::getInstance()->getDevice();
	D3DXVECTOR3 dir(0.717f, -0.707f, 0.717f);
	D3DXCOLOR color = d3d::WHITE;
	LightManager::getInstance()->setLight(LightManager::LightType::Directional, nullptr, &dir, &color,Device);
	LightManager::getInstance()->setLightState(true);
	Device->SetLight(0, LightManager::getInstance()->getLight());
	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, false);
	Device->SetRenderState(D3DRS_LIGHTING, true);
	
	D3DXVECTOR3 d;
	D3DXMATRIX cp;
	D3DXPLANE p(0.0f, -1.0f, 0.0f, 0.0f);
	LightManager::getInstance()->getDir(&d);
	D3DXVECTOR4 light(d.x, d.y, d.z, 0.0f);
	D3DXVECTOR3 cubePos(0.0f, 1.0f, 2.0f);
	D3DXMatrixTranslation(&cp, cubePos.x, cubePos.y, cubePos.z);
	UINT P = MeshManager::getInstance()->addMesh("tiger.x",&cp);
	ShadowManager::getInstance()->addShadow(ShadowInfo(&light, &p, &cubePos, MeshManager::getInstance()->getMesh(P)->getMeshPointer()));


	terrain = new Terrain("height.raw", 128, 128, 3.0f, 1.0f);
	terrain->genTexture();

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
	IDirect3DDevice9 *Device = nullptr;

	if (!d3d::initD3D(hInstance, Width, Height, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "initD3d failed", "error",0);
		return 0;
	}
	DeviceManager::getInstance()->initDevice(Device);
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