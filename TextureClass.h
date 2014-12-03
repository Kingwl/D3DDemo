#pragma once
#ifndef _TEXTURE_CLASS_
#define _TEXTURE_CLASS_
#include "d3dx9.h"
#include "DeviceManager.h"
class TextureClass
{
public:
	TextureClass(const char *fileName = nullptr);
	bool setTexture(const char *fileName);
	bool setEmpty(int width, int height);
	~TextureClass();
	void textureClear();
	IDirect3DTexture9* getTexturePointer();
private:
	IDirect3DTexture9 *_Texture;
	IDirect3DDevice9 *_Device;
};
#endif
