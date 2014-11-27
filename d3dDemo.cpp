#include "windows.h"
#include "d3dx9.h"
#include "initD3D.h"
#include "Vertex.hpp"
#include "Cube.h"
#include "LightManager.h"
#include "Mtrl.h"
Cube *cube;
const int Width = 800;
const int Height = 600;
IDirect3DDevice9 *Device = nullptr;
IDirect3DVertexBuffer9 *VertexBuffer = nullptr;
LightManager *lightManager;
bool Display(float timeDelta)
{
	static float angle = 0.0f;

	D3DXVECTOR3 pos(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 look(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &pos, &look, &up);
	Device->SetTransform(D3DTS_VIEW, &V);

	Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0xff000000, 1.0f, 0);
	Device->BeginScene();
	D3DXMATRIX C;
	D3DXMatrixTranslation(&C, -1.0f, 0.0f, 0.0f);
	Device->SetTransform(D3DTS_WORLD, &C);
	Device->SetStreamSource(0, VertexBuffer, 0, sizeof(ColorVertex));
	Device->SetFVF(ColorVertex::FVF);
	Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
	D3DXMATRIX CU;

	D3DXMatrixTranslation(&CU, 1.0f, 0.0f, 0.0f);
	Device->SetTransform(D3DTS_WORLD, &CU);
	D3DMATERIAL9 mtrl = d3d::RED_MTRL;
	cube->drawCube(0,&mtrl,0);
	Device->EndScene();
	Device->Present(0, 0, 0, 0);
	return true;
}

bool Setup()
{
	D3DXVECTOR3 dir(0.717f,0.0f,0.717f);
	D3DXCOLOR color = d3d::WHITE;
	lightManager->getInstance().setLight(LightManager::LightType::Directional,nullptr,&dir,&color);

	Device->SetRenderState(D3DRS_LIGHTING, true);
	Device->SetLight(0, lightManager->getInstance().getLight());
	Device->LightEnable(0, true);
	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, false);

	cube = new Cube(Device);
	Device->CreateVertexBuffer(
		6 * sizeof (ColorVertex),
		D3DUSAGE_WRITEONLY,
		ColorVertex::FVF,
		D3DPOOL_MANAGED,
		&VertexBuffer,
		0);
	ColorVertex *v = nullptr;
	VertexBuffer->Lock(0, 0, (void**)&v, 0);
	v[0] = ColorVertex(0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255,0,0));
	v[1] = ColorVertex(0.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(0,255,0));
	v[2] = ColorVertex(1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0,0,255));

	v[3] = ColorVertex(0.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0));
	v[4] = ColorVertex(1.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0));
	v[5] = ColorVertex(1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255));
	VertexBuffer->Unlock();


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
	d3d::Release<IDirect3DVertexBuffer9*>(VertexBuffer);
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