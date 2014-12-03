#include "Terrain.h"

Terrain::Terrain(const char *fileName,int numVertesPerRow,int numVertesPerCol,int cellSpacing,float heightScaling)
:_numVertesPerCol(numVertesPerCol), _numVertesPerRow(numVertesPerRow), _cellSpacing(cellSpacing), _heightScaling(heightScaling), _textureId(-1)

{
	_numCellPerCol = _numVertesPerCol - 1;
	_numCellPerRow = _numVertesPerRow - 1;
	_width = _numCellPerRow * _cellSpacing;
	_depth = _numCellPerCol * _cellSpacing;
	_numVertices = _numVertesPerCol * _numVertesPerRow;
	_numTriangles = _numCellPerCol * _numCellPerRow * 2;
	_Device = DeviceManager::getInstance()->getDevice();
	if (!readRawFile(fileName))
	{
		::MessageBox(0, "readRawFile - FAILED", 0, 0);
		::PostQuitMessage(0);
	}

	compuleVertices();
	compuleIndies();

}

Terrain::~Terrain()
{
}
bool Terrain::readRawFile(const char *fileName)
{
	std::vector<BYTE> in(_numVertices);
	std::fstream fin(fileName, std::ios::binary);
	fin.read((char*)&in[0], in.size());
	fin.close();
	_heightMap.resize(_numVertices);
	for (int i = 0; i < in.size(); i++)
	{
		_heightMap[i] = in[i];
	}
	return true;
}
bool Terrain::compuleVertices()
{
	HRESULT hr = _Device->CreateVertexBuffer(
		_numTriangles * sizeof(TerrainVertex),
		D3DUSAGE_WRITEONLY,
		TerrainVertex::FVF,
		D3DPOOL_MANAGED,
		&_VertexBuffer,
		0);
	if (FAILED(hr))
	{
		return false;
	}
	int startX = -_width / 2;
	int startZ = _depth / 2;
	int endX = _width / 2;
	int endZ = -_depth / 2;
	float uCoodIncrementSize = 1.0f / (float)_numCellPerRow;
	float vCoodIncrementSize = 1.0f / (float)_numCellPerCol;

	TerrainVertex *v = nullptr;
	_VertexBuffer->Lock(0, 0, (void**)&v, 0);
	int i = 0;
	for (int z = startZ; z >= endZ; z -= _cellSpacing)
	{
		int j = 0;
		for (int x = startX; x <= endX; x += _cellSpacing)
		{
			int index = i * _numVertesPerRow + j;
			v[index] = TerrainVertex((float)x, (float)_heightMap[index], (float)z, (float)j * uCoodIncrementSize, (float)i * vCoodIncrementSize);
			j++;
		}
		i++;
	}
	_VertexBuffer->Unlock();
	return true;
}
bool Terrain::compuleIndies()
{
	HRESULT hr = _Device->CreateIndexBuffer(
		_numTriangles * 3 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&_IndexBuffer,
		0);
	if (FAILED(hr))
	{
		::MessageBox(0, "fuck failed", 0, 0);

		return false;
	}
	WORD *index = nullptr;
	_IndexBuffer->Lock(0, 0, (void**)&index, 0);
	int baseIndex = 0;
	for (int i = 0; i < _numCellPerCol; i++)
	{
		for (int j = 0; j < _numCellPerRow; j++)
		{
			index[baseIndex + 0] = i * _numVertesPerRow + j;
			index[baseIndex + 1] = i * _numVertesPerRow + j + 1;
			index[baseIndex + 2] = (i + 1) * _numVertesPerRow + j;

			index[baseIndex + 3] = (i + 1) * _numVertesPerRow + j;
			index[baseIndex + 4] = i * _numVertesPerRow + j + 1;
			index[baseIndex + 5] = (i + 1) * _numVertesPerRow + j + 1;

			baseIndex += 6;
		}
	}
	_IndexBuffer->Unlock();
	return true;
}

bool Terrain::loadTexture(const char *fileName)
{
	TextureManager::getInstance()->addTexture(fileName,&_textureId);
	if (_textureId == -1)
	{
		::MessageBox(0, "load failed", 0, 0);
		return false;
	}
	return true;
}
bool Terrain::genTexture()
{
	int texWidth = _numVertesPerRow;
	int texHeight = _numVertesPerCol;
	TextureManager::getInstance()->addTextureEmpty(texWidth, texHeight, &_textureId);
	D3DSURFACE_DESC textureDesc;
	TextureManager::getInstance()->getTexture(_textureId)->getTexturePointer()->GetLevelDesc(0, &textureDesc);
	if (textureDesc.Format != D3DFMT_X8R8G8B8)
	{
		::MessageBox(0, "Filter failed", 0, 0);
		return false;
	}
	D3DLOCKED_RECT lockedRect;
	TextureManager::getInstance()->getTexture(_textureId)->getTexturePointer()->LockRect(0, &lockedRect, 0, 0);
	DWORD *imgData = (DWORD*)lockedRect.pBits;
	for (int i = 0; i < texWidth; i++)
	{
		for (int j = 0; j < texHeight; j++)
		{
			D3DXCOLOR C;
			float height = (float)getHeightMapEntry(i, j) / _heightScaling;

			if (height < 42.5f) C = d3d::BEACH_SAND;
			else if (height < 85.0f) C = d3d::LIGHT_YELLOW_GREEN;
			else if (height < 127.5) C = d3d::PUREGREEN;
			else if (height < 170.f) C = d3d::DARK_YELLOW_GREEN;
			else if (height < 212.5f) C = d3d::DARKBROWN;
			else C = d3d::WHITE;
			imgData[i * lockedRect.Pitch / 4 + j] = (D3DCOLOR)C;
		}
	}
	TextureManager::getInstance()->getTexture(_textureId)->getTexturePointer()->UnlockRect(0);
	D3DXVECTOR3 light;
	LightManager::getInstance()->getDir(&light);
	HRESULT hr = D3DXFilterTexture(TextureManager::getInstance()->getTexture(_textureId)->getTexturePointer(), 0, 0, D3DX_DEFAULT);
	if (FAILED(hr))
	{
		::MessageBox(0, "Filter failed", 0, 0);
		return false;
	}

	return true;
}
int Terrain::getHeightMapEntry(int x, int y)
{
	return _heightMap[x * _numVertesPerRow + y];
}
void Terrain::Render()
{
	_Device->SetStreamSource(0, _VertexBuffer, 0, sizeof(TerrainVertex));
	_Device->SetFVF(TerrainVertex::FVF);
	_Device->SetIndices(_IndexBuffer);
	_Device->SetTexture(0,TextureManager::getInstance()->getTexture(_textureId)->getTexturePointer());
	_Device->SetRenderState(D3DRS_LIGHTING, false);
	_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _numVertices, 0, _numTriangles);
	_Device->SetRenderState(D3DRS_LIGHTING, true);
	_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _numVertices, 0, _numTriangles);
	_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

}