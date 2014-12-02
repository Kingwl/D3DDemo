#pragma once
#ifndef _CUBE_
#define _CUBE_
#include "d3dx9.h"
#include "Vertex.hpp"
#include "DeviceManager.h"
class Cube
{
public:

	Cube();
	~Cube();
	void drawCube(D3DXMATRIX *World = nullptr, D3DMATERIAL9 *Mtrl = nullptr, IDirect3DTexture9 *Texture = nullptr);
	void getMesh(ID3DXMesh **Mesh);
	static const int NumVertex = 24;
	static const int NumIndex = 36;
	
private:
	IDirect3DDevice9 *_Device;
	IDirect3DVertexBuffer9 *_VertexBuffer;
	IDirect3DIndexBuffer9 *_IndexBuffer;
	ID3DXMesh *_Mesh;

};
#endif