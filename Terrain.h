#pragma once
#ifndef _TERRAIN_
#define _TERRAIN_
#include "d3dx9.h"
#include "vector"
#include "DeviceManager.h"
#include "TextureManager.h"
#include "Vertex.hpp"
#include "iostream"
#include "fstream"
#include "Color.h"
#include "LightManager.h"
class Terrain
{
public:
	Terrain(
			const char *fileName,
			int numVertesPerRow,
			int numVertesPerCol,
			int cellSpacing,
			float heightScaling);
	~Terrain();
	bool readRawFile(const char *fileName);
	bool loadTexture(const char *fileName);
	bool genTexture();
	bool compuleVertices();
	bool compuleIndies();
	void Render();
	int getHeightMapEntry(int x, int y);
private:

	std::vector<int> _heightMap;
	IDirect3DDevice9 *_Device;
	int _numVertesPerRow;
	int _numVertesPerCol;
	int _cellSpacing;
	float _heightScaling;

	int _numCellPerRow;
	int _numCellPerCol;
	int _width;
	int _depth;
	int _numVertices;
	int _numTriangles;
	UINT _textureId;
	IDirect3DVertexBuffer9 *_VertexBuffer;
	IDirect3DIndexBuffer9 *_IndexBuffer;


};

#endif