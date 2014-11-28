#include "windows.h"
#include "d3dx9.h"
#include "initD3D.h"
#include "Vertex.hpp"
#include "Cube.h"
#include "LightManager.h"
#include "Mtrl.h"
#include "ShadowClass.h"
Cube *cube,*cb;
const int Width = 800;
const int Height = 600;
IDirect3DDevice9 *Device = nullptr;
LightManager *lightManager;
ShadowClass *shadow;
D3DXVECTOR3 cubePos(5.0f, 0.0f, 0.0f);
D3DXVECTOR3 Cpos(5.0f, -2.0f, 0.0f);
D3DXMATRIX World;
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


	D3DXVECTOR3 position(cosf(angle) * radius, 1.0f, sinf(angle) * radius);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	Device->SetTransform(D3DTS_VIEW, &V);

	Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0xffffffff, 1.0f, 0);
	Device->BeginScene();
	D3DXMatrixIdentity(&World);
	Device->SetTransform(D3DTS_WORLD, &World);
	D3DXMATRIX CU;

	D3DXMatrixTranslation(&CU, cubePos.x, cubePos.y, cubePos.z);
	Device->SetTransform(D3DTS_WORLD, &CU);
	D3DMATERIAL9 mtrl = d3d::RED_MTRL;
	cube->drawCube(0,&mtrl,0);
	
	D3DXMATRIX sd;
	D3DXMatrixTranslation(&sd, Cpos.x, Cpos.y, Cpos.z);
	Device->SetTransform(D3DTS_WORLD, &sd);
	D3DMATERIAL9 cmtrl = d3d::BLUE_MTRL;
	cb->drawCube(0, &cmtrl, 0);
	
	D3DXMATRIX od;
	Device->SetTransform(D3DTS_WORLD, &CU);
	shadow->drawShadowMesh();
	

	Device->EndScene();
	Device->Present(0, 0, 0, 0);
	return true;
}

bool Setup()
{
	D3DXVECTOR3 dir(0.717f, -0.707f, 0.717f);
	D3DXCOLOR color = d3d::WHITE;
	lightManager->getInstance().setLight(LightManager::LightType::Directional,nullptr,&dir,&color);


	Device->SetRenderState(D3DRS_LIGHTING, true);
	Device->SetLight(0, lightManager->getInstance().getLight());
	Device->LightEnable(0, true);

	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, false);
	cube = new Cube(Device);
	cb = new Cube(Device);

	shadow = new ShadowClass(Device);
	D3DXVECTOR3 d;
	lightManager->getInstance().getDir(&d);

	D3DXVECTOR4 light(d.x, d.y, d.z, 0.0f);
	D3DXPLANE p(0.0f, -1.0f, 0.0f, 0.0f);
	ID3DXMesh *m;
	cube->getMesh(&m);
	shadow->initContext(&light, &p, &cubePos, m);





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