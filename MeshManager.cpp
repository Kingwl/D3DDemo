#include "MeshManager.h"

MeshManager* MeshManager::_instance = nullptr;

MeshManager::MeshManager()
{
}
MeshManager::~MeshManager()
{
	clear();
}
MeshManager* MeshManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new MeshManager();
	}
	return _instance;
}
UINT MeshManager::addMesh(ID3DXMesh *mesh, std::vector<UINT> *textures, std::vector<D3DMATERIAL9> *mtrls, D3DXMATRIX *pos)
{
	MeshClass *p = new MeshClass();
	bool flag = p->initWithMesh(mesh, textures, mtrls);
	if (flag == false) return -1;
	if (pos != nullptr) p->setPos(pos);
	_elems.push_back(p);
	return _elems.end() - _elems.begin() - 1;
}
UINT MeshManager::addMesh(const char *filename, D3DXMATRIX *pos)
{
	MeshClass *p = new MeshClass();
	bool flag = p->initWithXFile(filename);
	if (flag == false) return -1;
	if (pos != nullptr) p->setPos(pos);
	_elems.push_back(p);
	return _elems.end() - _elems.begin() - 1;
}
MeshClass* MeshManager::getMesh(UINT index)
{
	return _elems[index];
}
void MeshManager::clear()
{
	for (auto &p : _elems)
	{
		delete p;
		p = nullptr;
	}
	_elems.clear();
}
void MeshManager::Render()
{
	for (auto &p : _elems)
	{
		p->Render();
	}
}
void MeshManager::RenderPMesh()
{
	for (auto &p : _elems)
	{
		p->RenderPMesh();
	}
}