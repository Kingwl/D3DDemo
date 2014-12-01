#include "Cube.h"


Cube::Cube()
:_Device(nullptr), _VertexBuffer(nullptr), _IndexBuffer(nullptr)
{
	_Device = DeviceManager::getInstance()->getDevice();
	_Device->CreateVertexBuffer(
		NumVertex * sizeof(TexVertex),
		D3DUSAGE_WRITEONLY,
		TexVertex::FVF,
		D3DPOOL_MANAGED,
		&_VertexBuffer,0);

	_Device->CreateIndexBuffer(
		NumIndex * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&_IndexBuffer,0);

	TexVertex *v = nullptr;
	_VertexBuffer->Lock(0, 0, (void**)&v, 0);
	
	createCubeVertex(v);

	_VertexBuffer->Unlock();

	WORD *i = nullptr;
	_IndexBuffer->Lock(0, 0, (void**)&i, 0);

	//front
	i[0] = 0; i[1] = 1; i[2] = 3;
	i[3] = 1; i[4] = 2; i[5] = 3;
	//back
	i[6] = 4; i[7] = 5; i[8] = 7;
	i[9] = 5; i[10] = 6; i[11] = 7;
	//left
	i[12] = 8; i[13] = 9; i[14] = 11;
	i[15] = 9; i[16] = 10; i[17] = 11;
	//right
	i[18] = 12; i[19] = 13; i[20] = 15;
	i[21] = 13; i[22] = 14; i[23] = 15;
	//top
	i[24] = 16; i[25] = 17; i[26] = 19;
	i[27] = 17; i[28] = 18; i[29] = 19;
	//bottom
	i[30] = 20; i[31] = 21; i[32] = 23;
	i[33] = 21; i[34] = 22; i[35] = 23;
	_IndexBuffer->Unlock();
}

Cube::~Cube()
{
	_VertexBuffer->Release();
	_VertexBuffer = nullptr;
	_IndexBuffer->Release();
	_IndexBuffer = nullptr;
}

void Cube::drawCube(D3DXMATRIX *World, D3DMATERIAL9 *Mtrl, IDirect3DTexture9 *Texture)
{
	if (World)
	{
		_Device->SetTransform(D3DTS_WORLD, World);
	}
	if (Mtrl)
	{
		_Device->SetMaterial(Mtrl);
	}
	if (Texture)
	{
		_Device->SetTexture(0, Texture);
	}
	_Device->SetFVF(TexVertex::FVF);
	_Device->SetStreamSource(0, _VertexBuffer, 0, sizeof(TexVertex));
	_Device->SetIndices(_IndexBuffer);
	_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);
}
DCube::DCube(D3DMATERIAL9 *Mtrl, IDirect3DTexture9 **Texture)
:_Device(nullptr), _Mtrl(Mtrl)
{
	_Device = DeviceManager::getInstance()->getDevice();
	_Device->CreateVertexBuffer(
		NumVertex * sizeof(TexVertex),
		D3DUSAGE_WRITEONLY,
		TexVertex::FVF,
		D3DPOOL_MANAGED,
		&_VertexBuffer,0);
	
	TexVertex *v = nullptr;

	_VertexBuffer->Lock(0, 0, (void**)&v, 0);

	createCubeVertex(v);

	_VertexBuffer->Unlock();

	for (int i = 0; i < 6; i++)
	{
		_Device->CreateIndexBuffer(
			6 * sizeof(WORD),
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&_IndexBuffer[i],
			0);
	}
	WORD *i = nullptr;

	_IndexBuffer[faceTo::front] ->Lock(0,0,(void**)&i,0);
	i[0] = 0; i[1] = 1; i[2] = 3;
	i[3] = 1; i[4] = 2; i[5] = 3;
	_IndexBuffer[faceTo::front]->Unlock();

	_IndexBuffer[faceTo::back]->Lock(0, 0, (void**)&i, 0);
	i[0] = 4; i[1] = 5; i[2] = 7;
	i[3] = 5; i[4] = 6; i[5] = 7;
	_IndexBuffer[faceTo::back]->Unlock();

	_IndexBuffer[faceTo::left]->Lock(0, 0, (void**)&i, 0);
	i[0] = 8; i[1] = 9; i[2] = 11;
	i[3] = 9; i[4] = 10; i[5] = 11;
	_IndexBuffer[faceTo::left]->Unlock();

	_IndexBuffer[faceTo::right]->Lock(0, 0, (void**)&i, 0);
	i[0] = 12; i[1] = 13; i[2] = 15;
	i[3] = 13; i[4] = 14; i[5] = 15;
	_IndexBuffer[faceTo::right]->Unlock();

	_IndexBuffer[faceTo::top]->Lock(0, 0, (void**)&i, 0);
	i[0] = 16; i[1] = 17; i[2] = 19;
	i[3] = 17; i[4] = 18; i[5] = 19;
	_IndexBuffer[faceTo::top]->Unlock();

	_IndexBuffer[faceTo::bottom]->Lock(0, 0, (void**)&i, 0);
	i[0] = 20; i[1] = 21; i[2] = 23;
	i[3] = 21; i[4] = 22; i[5] = 23;
	_IndexBuffer[faceTo::bottom]->Unlock();


}
void DCube::setTexture(IDirect3DTexture9 **Texture)
{
	if (Texture != nullptr)
	{
		for (int i = 0; i < 6; i++)
		{
			_Texture[i] = Texture[i];
		}
	}
}
void DCube::setTexture(faceTo to, IDirect3DTexture9 *Texture)
{
	_Texture[to] = Texture;
}

void DCube::setMtrl(D3DMATERIAL9 *Mtrl)
{
	_Mtrl = Mtrl;
}
DCube::~DCube()
{
	_VertexBuffer->Release();
	_VertexBuffer = nullptr;
	for (int i = 0; i < 6; i++)
	{
		_IndexBuffer[i]->Release();
		_IndexBuffer[i] = nullptr;
		_Texture[i]->Release();
		_Texture[i] = nullptr;
	}
}
void DCube::drawPlane(faceTo to,D3DXMATRIX *World)
{
	if (World)
	{
		_Device->SetTransform(D3DTS_WORLD, World);
	}
	_Device->SetFVF(TexVertex::FVF);
	_Device->SetStreamSource(0,_VertexBuffer,0,sizeof(TexVertex));
	_Device->SetMaterial(_Mtrl);
	_Device->SetIndices(_IndexBuffer[to]);
	_Device->SetTexture(0,_Texture[to]);
	_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 2);
}
void DCube::drawCube(D3DXMATRIX *World)
{
	if (World)
	{
		_Device->SetTransform(D3DTS_WORLD, World);
	}
	if (_Mtrl)
	{
		_Device->SetMaterial(_Mtrl);
	}
	_Device->SetFVF(TexVertex::FVF);
	_Device->SetStreamSource(0, _VertexBuffer, 0, sizeof(TexVertex));
	
	for (int i = 0; i < 6; i++)
	{
		_Device->SetIndices(_IndexBuffer[i]);
		_Device->SetTexture(0, _Texture[i]);
		_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 2);
	}
	
}
void createCubeVertex(TexVertex *v)
{
	//front
	v[0] = TexVertex(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[1] = TexVertex(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[2] = TexVertex(1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
	v[3] = TexVertex(1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	//back
	v[4] = TexVertex(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	v[5] = TexVertex(1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	v[6] = TexVertex(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	v[7] = TexVertex(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	//left
	v[8] = TexVertex(-1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[9] = TexVertex(-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[10] = TexVertex(-1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	v[11] = TexVertex(-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//right
	v[12] = TexVertex(1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[13] = TexVertex(1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[14] = TexVertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	v[15] = TexVertex(1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//top

	v[16] = TexVertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	v[17] = TexVertex(-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	v[18] = TexVertex(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
	v[19] = TexVertex(1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

	//bottom

	v[20] = TexVertex(-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
	v[21] = TexVertex(1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
	v[22] = TexVertex(1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
	v[23] = TexVertex(-1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
}
void Cube::getMesh(ID3DXMesh **Mesh)
{
	if (_Mesh == nullptr) D3DXCreateMeshFVF(12, 24, D3DXMESH_MANAGED,TexVertex::FVF,_Device,&_Mesh);
	TexVertex *v = nullptr;
	TexVertex *p = nullptr;
	_Mesh->LockVertexBuffer(0,(void**)&v);
	createCubeVertex(v);
	_Mesh->UnlockVertexBuffer();

	WORD *ii = nullptr;
	WORD *ip = nullptr;

	_Mesh->LockIndexBuffer(0, (void**)&ii);
	_IndexBuffer->Lock(0, 0, (void**)&ip, 0);
	for (int i = 0; i < 36; i++)
	{
		ii[i] = ip[i];
	}
	_Mesh->UnlockIndexBuffer();
	_IndexBuffer->Unlock();

	DWORD *adj = nullptr;
	_Mesh->LockAttributeBuffer(0, &adj);
	for (int i = 0; i < 12; i++)
	{
		adj[i] = 0;
	}
	_Mesh->UnlockAttributeBuffer();

	*Mesh = _Mesh;
}