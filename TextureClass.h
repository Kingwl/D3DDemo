#pragma once
#ifndef _TEXTURE_CLASS_
#define _TEXTURE_CLASS_
#include "d3dx9.h"
#include "windows.h"
class TextureClass
{
public:
	TextureClass(IDirect3DDevice9 *Device, const char* fileName = nullptr);
	bool setTexture(const char* fileName);
	~TextureClass();
	void textureClear();
	const IDirect3DTexture9* getTexture();
private:
	IDirect3DTexture9 *_Texture;
	IDirect3DDevice9 *_Device;
};
#endif