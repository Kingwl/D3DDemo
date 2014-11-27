#pragma once
#include "Light.h"

D3DLIGHT9 d3d::InitDirectionalLight(D3DXVECTOR3 *direction, D3DXCOLOR *color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient = *color * LIGHT_AMBIENT;
	light.Diffuse = *color * LIGHT_DIFFUSE;
	light.Specular = *color * LIGHT_SPECULAR;
	light.Direction = *direction;
	return light;
}

D3DLIGHT9 d3d::InitPointLight(D3DXVECTOR3 *position, D3DXCOLOR *color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_POINT;
	light.Ambient = *color * LIGHT_AMBIENT;
	light.Diffuse = *color * LIGHT_DIFFUSE;
	light.Specular = *color * LIGHT_SPECULAR;
	light.Position = *position;
	light.Range = LIGHT_RANGE;
	light.Falloff = LIGHT_FALLOFF;
	light.Attenuation0 = LIGHT_ATT_0;
	light.Attenuation1 = LIGHT_ATT_1;
	light.Attenuation2 = LIGHT_ATT_2;
	return light;
}

D3DLIGHT9 d3d::InitSoptLight(D3DXVECTOR3 *posotion, D3DXVECTOR3 *direction, D3DXCOLOR *color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_SPOT;
	light.Ambient = *color * LIGHT_AMBIENT;
	light.Diffuse = *color * LIGHT_DIFFUSE;
	light.Specular = *color * LIGHT_SPECULAR;
	light.Position = *posotion;
	light.Range = LIGHT_RANGE;
	light.Falloff = LIGHT_FALLOFF;
	light.Attenuation0 = LIGHT_ATT_0;
	light.Attenuation1 = LIGHT_ATT_1;
	light.Attenuation2 = LIGHT_ATT_2;
	light.Theta = LIGHT_THETA;
	light.Phi = LIGHT_PHI;
	return light;
}