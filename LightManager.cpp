#include "LightManager.h"
LightManager* LightManager::_instance = nullptr;

LightManager::LightManager()
:_light(nullptr), _type(LightType::unknow), _lightEnable(true)
{
	_Device = DeviceManager::getInstance()->getDevice();
}
LightManager::~LightManager()
{

}

LightManager* LightManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new LightManager();
	}
	return _instance;
}
void LightManager::getPos(D3DXVECTOR3 *pos)
{
	*pos = _light->Position;
}
void LightManager::setPos(D3DXVECTOR3 *pos)
{
	_light->Position = *pos;
}
void LightManager::getDir(D3DXVECTOR3 *direction)
{
	*direction = _light->Direction;
}
void LightManager::setDir(D3DXVECTOR3 *direction)
{
	_light->Direction = *direction;
}
void LightManager::getColor(D3DXCOLOR *color)
{
	*color = _light->Diffuse;
}
void LightManager::setColor(D3DXCOLOR *color)
{
	if (_type == unknow) return;
	if (_type == Directional)
	{
		_light->Ambient = *color * LIGHT_AMBIENT;
		_light->Diffuse = *color * LIGHT_DIFFUSE;
		_light->Specular = *color * LIGHT_SPECULAR;
	}
	if (_type == Point)
	{
		_light->Ambient = *color * LIGHT_AMBIENT;
		_light->Diffuse = *color * LIGHT_DIFFUSE;
		_light->Specular = *color * LIGHT_SPECULAR;
		_light->Range = LIGHT_RANGE;
		_light->Falloff = LIGHT_FALLOFF;
		_light->Attenuation0 = LIGHT_ATT_0;
		_light->Attenuation1 = LIGHT_ATT_1;
		_light->Attenuation2 = LIGHT_ATT_2;
	}
	if (_type == Spot)
	{
		_light->Ambient = *color * LIGHT_AMBIENT;
		_light->Diffuse = *color * LIGHT_DIFFUSE;
		_light->Specular = *color * LIGHT_SPECULAR;
		_light->Range = LIGHT_RANGE;
		_light->Falloff = LIGHT_FALLOFF;
		_light->Attenuation0 = LIGHT_ATT_0;
		_light->Attenuation1 = LIGHT_ATT_1;
		_light->Attenuation2 = LIGHT_ATT_2;
		_light->Theta = LIGHT_THETA;
		_light->Phi = LIGHT_PHI;
	}
}

bool LightManager::setLight(LightType type, D3DXVECTOR3 *pos, D3DXVECTOR3 *dir, D3DXCOLOR *color,IDirect3DDevice9 *device)
{
	if (color == nullptr) return false;
	if (device != nullptr) _Device = device;
	if (type == unknow)
	{
		return false;
	}
	else if (type == Directional)
	{
		if (dir != nullptr)
			_light = new D3DLIGHT9(d3d::InitDirectionalLight(dir, color));
	}
	else if (type == Point)
	{
		if (pos != nullptr)
			_light = new D3DLIGHT9(d3d::InitPointLight(pos, color));
	}
	else if (type == Spot)
	{
		if (dir != nullptr && pos != nullptr)
		{
			_light = new D3DLIGHT9(d3d::InitSoptLight(pos, dir, color));
		}
	}
	_type = type;
	setLightState(true);
	return true;
}
const D3DLIGHT9* LightManager::getLight()
{
	if (_type == unknow) return nullptr;

	return _light;
}
void LightManager::setLightState(bool s)
{
	_Device->LightEnable(0, s);
	_lightEnable = s;
}
bool LightManager::getLightState()
{
	return _lightEnable;
}