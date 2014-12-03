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
IDirect3DTexture9* TextureClass::getTexturePointer()
{
	return _Texture;
}
bool TextureClass::setEmpty(int width, int height)
{
	if (_Texture != nullptr)
		textureClear();
	HRESULT hr = D3DXCreateTexture(_Device, width, height, 0, 0, D3DFMT_X8R8G8B8, D3DPOOL_MANAGED, &_Texture);
	if (FAILED(hr))
		return false;
	return true;
}