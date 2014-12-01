#include "TextureClass.h"

TextureClass::TextureClass(const char *fileName)
:_Texture(nullptr), _Device(nullptr)
{
	_Device = DeviceManager::getInstance()->getDevice();
	if (fileName != nullptr)
	{
		setTexture(fileName);
	}
}
TextureClass::~TextureClass()
{
	textureClear();
}
bool TextureClass::setTexture(const char *fileName)
{
	if (_Texture != nullptr)
		textureClear();
	if (fileName == nullptr)
	{
		_Texture = nullptr;
		return false;
	}
	D3DXCreateTextureFromFile(_Device, fileName, &_Texture);
	return true;
}
void TextureClass::textureClear()
{
	if (_Texture != nullptr)
	{
		_Texture->Release();
		_Texture = nullptr;
	}
}
IDirect3DTexture9* TextureClass::getTexture()
{
	return _Texture;
}