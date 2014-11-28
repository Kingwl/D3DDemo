#pragma once
#include "Mtrl.h"

D3DMATERIAL9 d3d::InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, D3DXCOLOR p)
{
	D3DMATERIAL9 mtrl;
	mtrl.Ambient = a;
	mtrl.Diffuse = d;
	mtrl.Emissive = e;
	mtrl.Power = p;
	mtrl.Specular = s;
	return mtrl;
}