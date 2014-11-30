#include "TextureManager.h"
TextureManager* TextureManager::_instance = nullptr;

TextureManager::TextureManager()
{
}
TextureManager::~TextureManager()
{
	clear();
}
TextureManager* TextureManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new TextureManager();
	}
	return _instance;
}
bool TextureManager::addTexture(IDirect3DDevice9 *Device, const char *fileName, UINT *identity)
{
	TextureClass *texture = new TextureClass(Device);
	if (fileName != nullptr)
	{
		if (!texture->setTexture(fileName))
		return false;
	}
	_elemts.push_back(texture);
	*identity = _elemts.end() - _elemts.begin() -1;
	return true;
}
TextureClass* TextureManager::getTexture(std::size_t index)
{
	if (index >= _elemts.size())
	{
		return nullptr;
	}
	return _elemts[index];
}
void TextureManager::clear()
{
	for (auto &p : _elemts)
	{
		delete p;
		p = nullptr;
	}
	_elemts.clear();
}