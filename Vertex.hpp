#pragma once
#ifndef _VERTEX_
#define _VERTEX_
#include "d3dx9.h"
#include "windows.h"
class Vertex
{
public:
	Vertex(){}
	Vertex(float x, float y, float z)
		:_x(x), _y(y), _z(z)
	{}
	~Vertex(){}
	float _x, _y, _z;
	static const DWORD FVF = D3DFVF_XYZ;
};
class TexVertex
{
public:
	TexVertex(){};
	TexVertex(float x, float y, float z, float nx, float ny, float nz, float u, float v)
		:_x(x), _y(y), _z(z), _nx(nx), _ny(ny), _nz(nz), _u(u), _v(v){}
	~TexVertex(){};
	float _x, _y, _z;
	float _nx, _ny, _nz;
	float _u, _v;
	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
};
class ColorVertex
{
public :
	ColorVertex(){};
	ColorVertex(float x, float y, float z, D3DCOLOR color)
		:_x(x), _y(y), _z(z),_color(color){}
	~ColorVertex(){};
	float _x, _y, _z;
	D3DCOLOR _color;
	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
};
class TerrainVertex
{
public:
	TerrainVertex(){};
	TerrainVertex(float x, float y, float z, float u, float v)
	:_x(x),_y(y),_z(z),_u(u),_v(v){};
	~TerrainVertex(){};
	float _x, _y, _z;
	float _u, _v;
	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
};
#endif

