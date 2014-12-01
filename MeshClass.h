#pragma once
#ifndef _MESHCLASS_
#define _MESHCLASS_
#include "d3dx9.h"
#include "TextureManager.h"
#include "DeviceManager.h"
#include "Mtrl.h"
#include "vector"
class MeshClass
{
public:
	MeshClass();
	bool initWithMesh(ID3DXMesh *Mesh, std::vector<UINT> *textures, std::vector<D3DMATERIAL9> *mtrls);
	bool initWithXFile(const char *filename);
	void setPos(D3DXMATRIX *pos);
	bool Render();
	bool RenderPMesh();
	bool GetPMesh();
	ID3DXMesh* getMeshPointer();
	~MeshClass();
private:
	std::vector<D3DMATERIAL9> *_mtrls;
	std::vector<UINT> _textures;
	ID3DXMesh *_mesh;
	ID3DXPMesh *_pmesh;
	IDirect3DDevice9 *_Device;
	D3DXMATRIX _Pos;
	ID3DXBuffer *_adjBuffer = nullptr;
	bool _hasTex;
	bool _hasMtrl;
	bool _isInit;
	bool _hasPMesh;
};

#endif