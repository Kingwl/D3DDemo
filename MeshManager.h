#pragma once
#ifndef _MESHMANAGER_
#define _MESHMANAGER_
#include "MeshClass.h"
class MeshManager
{
public:
	static MeshManager* getInstance();
	UINT addMesh(ID3DXMesh *mesh, std::vector<UINT> *textures = nullptr, std::vector<D3DMATERIAL9> *mtrls = nullptr, D3DXMATRIX *p = nullptr);
	UINT addMesh(const char *filename, D3DXMATRIX *p = nullptr);
	MeshClass* getMesh(UINT index);
	void clear();
	void Render();
	void RenderPMesh();
private:
	static MeshManager *_instance;
	MeshManager();
	~MeshManager();
	std::vector<MeshClass*> _elems;
};

#endif