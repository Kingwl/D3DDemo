#pragma once
#ifndef _LIGHT_MANAGER_
#define _LIGHT_MANAGER_
#include "d3dx9.h"
#include "Light.h"
#include "DeviceManager.h"
class LightManager
{
public:
	static enum LightType
	{
		unknow = 0,
		Directional = 1,
		Point = 2,
		Spot = 3,
	};
	static LightManager* getInstance();
	void getPos(D3DXVECTOR3 *pos);
	void setPos(D3DXVECTOR3 *pos);
	void getDir(D3DXVECTOR3 *direction);
	void setDir(D3DXVECTOR3 *direction);
	void getColor(D3DXCOLOR *color);
	void setColor(D3DXCOLOR *color);
	void setLightState(bool s);
	bool getLightState();
	bool setLight(LightType type, D3DXVECTOR3 *pos, D3DXVECTOR3 *dir, D3DXCOLOR *color, IDirect3DDevice9 *device = nullptr);
	const D3DLIGHT9* getLight();
private:
	LightManager();
	~LightManager();
	static LightManager* _instance;
	D3DLIGHT9 *_light;
	LightType _type;
	IDirect3DDevice9 *_Device;
	bool _lightEnable;
};
#endif

