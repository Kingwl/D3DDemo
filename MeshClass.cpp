#include "MeshClass.h"

MeshClass::MeshClass(IDirect3DDevice9 *Device)
:_Device(Device), _mesh(nullptr), _isInit(false), _hasMtrl(false), _hasTex(false), _mtrls(nullptr)
{
	D3DXMatrixIdentity(&_Pos);
}
MeshClass::~MeshClass()
{
	if (_mesh != nullptr)
	{
		_mesh->Release();
		_mesh = nullptr;
	}
}
bool MeshClass::initWithMesh(ID3DXMesh *Mesh, std::vector<UINT> *textures = nullptr, std::vector<D3DMATERIAL9> *mtrls = nullptr)
{
	if (_isInit) return false;
	_mesh = Mesh;
	if (textures != nullptr)
	{
		_hasTex = true;
		_textures = *textures;
	}
	if (mtrls != nullptr)
	{
		_hasMtrl = true;
		_mtrls = mtrls;
	}
	_isInit = true;
	return true;
}
bool MeshClass::initWithXFile(const char *filename)
{
	if (_isInit || filename == nullptr) return false;
	_mtrls = new std::vector<D3DMATERIAL9>();
	ID3DXBuffer *adjBuffer = nullptr;
	ID3DXBuffer *MtrlBuffer = nullptr;
	DWORD Number;
	HRESULT hr = D3DXLoadMeshFromX(
		filename,
		D3DXMESH_MANAGED,
		_Device,
		&adjBuffer,
		&MtrlBuffer,
		nullptr,
		&Number,
		&_mesh);
	if (FAILED(hr))
	{
		::MessageBox(0,filename, 0, 0);
		return false;
	}
	D3DXMATERIAL *mtrls = (D3DXMATERIAL*)MtrlBuffer->GetBufferPointer();
	for (int i = 0; i < Number; i++)
	{
		mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;
		_mtrls->push_back(mtrls[i].MatD3D);

		if (mtrls[i].pTextureFilename != nullptr)
		{
			UINT index;
			TextureManager::getInstance()->addTexture(_Device, mtrls[i].pTextureFilename, &index);
			_textures.push_back(index);
		}
		else{
			_textures.push_back(0);
		}
	}
	MtrlBuffer->Release();
	_hasTex = true;
	_hasMtrl = true;
	_isInit = true;
	return true;
}
bool MeshClass::Render()
{
	if (_isInit == false) return false;
	_Device->SetTransform(D3DTS_WORLD, &_Pos);
	for (int i = 0; i < _mtrls->size(); i++)
	{
		if (_hasMtrl)
		{
			auto p = *(_mtrls);
			_Device->SetMaterial(&p[i]);
		}
		if (_hasTex)
		{
			_Device->SetTexture(0, TextureManager::getInstance()->getTexture(_textures[i])->getTexture());
		}
		_mesh->DrawSubset(i);
	}
	return true;
}
ID3DXMesh* MeshClass::getMeshPointer()
{
	return _mesh;
}
void MeshClass::setPos(D3DXMATRIX *pos)
{
	_Pos = *pos;
}