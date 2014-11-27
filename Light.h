#pragma once
#ifndef _LIGHT_
#define _LIGHT_
#include "d3dx9.h"
#include "Color.h"
static const float LIGHT_AMBIENT = 0.4f;
static const float LIGHT_DIFFUSE = 1.0f;
static const float LIGHT_SPECULAR = 0.6f;
static const float LIGHT_RANGE = 1000.0f;
static const float LIGHT_FALLOFF = 1.0f;
static const float LIGHT_ATT_0 = 1.0f;
static const float LIGHT_ATT_1 = 0.0f;
static const float LIGHT_ATT_2  = 0.0f;
static const float LIGHT_THETA = 0.4f;
static const float LIGHT_PHI = 0.9f;

namespace d3d{

	D3DLIGHT9 InitDirectionalLight(D3DXVECTOR3 *direction, D3DXCOLOR *color);
	D3DLIGHT9 InitPointLight(D3DXVECTOR3 *position, D3DXCOLOR *color);
	D3DLIGHT9 InitSoptLight(D3DXVECTOR3 *posotion, D3DXVECTOR3 *direction, D3DXCOLOR *color);
}
#endif


