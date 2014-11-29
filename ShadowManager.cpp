#include "ShadowManager.h"
ShadowManager* ShadowManager::_instance = nullptr;

ShadowManager::ShadowManager()
{
}

ShadowManager::~ShadowManager()
{
	clear();
}
void ShadowManager::addShadow(IDirect3DDevice9 *Device, ShadowInfo info)
{
	auto shadow = new ShadowClass(Device);
	shadow->initContext(info);
	_elems.push_back(shadow);
}
void ShadowManager::Render()
{
	for (auto &e : _elems)
	{
		e->drawShadowMesh();
	}
}
void ShadowManager::clear()
{
	for (auto &p : _elems)
	{
		delete p;
		p = nullptr;
	}
	_elems.clear();
}
ShadowManager* ShadowManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new ShadowManager();
	}
	return _instance;
}