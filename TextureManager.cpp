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
bool TextureManager::addTexture(const char *fileName, UINT *identity)
{
	TextureClass *texture = new TextureClass();
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
bool TextureManager::addTextureEmpty(int width, int height, UINT *identity)
{
	TextureClass *texture = new TextureClass();
	if (!texture->setEmpty(width, height))
	{
		return false;
	}
	_elemts.push_back(texture);
	*identity = _elemts.end() - _elemts.begin() - 1;
	return true;
}