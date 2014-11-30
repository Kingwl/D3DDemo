#pragma once
#ifndef _MESHCLASS_
#define _MESHCLASS_
#include "d3dx9.h"
#include "TextureManager.h"
#include "vector"
class MeshClass
{
public:
	MeshClass(IDirect3DDevice9 *Device);
	bool initWithMesh(ID3DXMesh *Mesh, std::vector<UINT> *textures, std::vector<D3DMATERIAL9> *mtrls);
	bool initWithXFile(const char *filename);
	bool Render();
	~MeshClass();
private:
	std::vector<D3DMATERIAL9> *_mtrls;
	std::vector<UINT> _textures;
	ID3DXMesh *_mesh;
	IDirect3DDevice9 *_Device;
	bool _hasTex;
	bool _hasMtrl;
	bool _isInit;
};

#endif