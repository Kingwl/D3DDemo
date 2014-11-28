#pragma once
#ifndef _SHADOW_CLASS_
#define _SHADOW_CLASS_
#include "d3dx9.h"
#include "LightManager.h"
#include "Mtrl.h"
#include "Vertex.hpp"
class ShadowClass
{
public:

	ShadowClass(IDirect3DDevice9 *Device);
	~ShadowClass();
	bool initContext(D3DXVECTOR4 *lightDirection, D3DXPLANE *Plane, D3DXVECTOR3 *Position, ID3DXMesh *Mesh);
	bool drawShadowMesh();
	bool initShadow();
	void setContext();

private:
	bool _isInit;
	IDirect3DDevice9 *_Device;
	ID3DXMesh *_Mesh;
	D3DXVECTOR4 _LightDir;
	D3DXVECTOR3 _ObjPosition;
	D3DXPLANE _shadowPlane;
	D3DXMATRIX _shadowMatrix;
	D3DMATERIAL9 _Mtrl;
};
#endif
