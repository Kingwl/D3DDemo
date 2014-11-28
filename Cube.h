#pragma once
#ifndef _CUBE_
#define _CUBE_
#include "d3dx9.h"
#include "windows.h"
#include "assert.h"
#include "Vertex.hpp"
class Cube
{
public:

	Cube(IDirect3DDevice9 *Device);

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

class DCube{
public:
	static enum faceTo
	{
		front = 0,
		back = 1,
		left = 2,
		right = 3,
		top = 4,
		bottom = 5
	};
	DCube(IDirect3DDevice9 *Device, D3DMATERIAL9 *Mtrl = nullptr, IDirect3DTexture9 **Texture = nullptr);
	void setTexture(IDirect3DTexture9 **Texture);
	void setTexture(faceTo to, IDirect3DTexture9 *Texture);
	void setMtrl(D3DMATERIAL9 *Mtrl);
	~DCube();
	void drawPlane(faceTo to, D3DXMATRIX *World);
	void drawCube(D3DXMATRIX *World);
	static const int NumVertex = 24;
	static const int NumIndex = 36;
private:
	IDirect3DDevice9 *_Device;
	IDirect3DVertexBuffer9 *_VertexBuffer;
	IDirect3DIndexBuffer9 *_IndexBuffer[6];
	IDirect3DTexture9 *_Texture[6];
	D3DMATERIAL9 *_Mtrl;
};
void createCubeVertex(TexVertex *v);
#endif