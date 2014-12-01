#pragma once
#ifndef _TEXTURE_MANAGER_
#define _TEXTURE_MANAGER_
#include "d3dx9.h"
#include "vector"
#include "TextureClass.h"
class TextureManager
{
public:
	static TextureManager* getInstance();
	bool addTexture(const char *fileName , UINT *identity);
	TextureClass* getTexture(std::size_t index);
	void clear();
private:
	static TextureManager *_instance ;
	TextureManager();
	~TextureManager();
	std::vector<TextureClass*> _elemts;
};
#endif