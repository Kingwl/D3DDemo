#include "TextureClass.h"

TextureClass::TextureClass(IDirect3DDevice9 *Device, const char* fileName)
:_Texture(nullptr), _Device(Device)
{
	if (fileName != nullptr)
	{
		setTexture(fileName);
	}
}
TextureClass::~TextureClass()
{
	textureClear();
}
bool TextureClass::setTexture(const char* fileName)
{
	if (_Texture != nullptr)
		textureClear();
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
const IDirect3DTexture9* TextureClass::getTexture()
{
	return _Texture;
}