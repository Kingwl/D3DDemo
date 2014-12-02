#include "Cube.h"

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