#pragma once
#ifndef _SHADOWMANAGER_
#define _SHADOWMANAGER_
#include "ShadowClass.h"
#include "vector"
class ShadowManager
{
public:
	void addShadow(ShadowInfo info);
	void Render();
	void clear();
	static ShadowManager* getInstance();
private:
	ShadowManager();
	~ShadowManager();
	static ShadowManager* _instance;
	std::vector<ShadowClass*> _elems;
};
#endif
