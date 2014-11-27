#pragma once
#ifndef _MTRL_
#define _MTRL_
#include "d3dx9.h"
#define CREATE_MTRL(NAME,COLOR) const D3DMATERIAL9 (NAME) = d3d::InitMtrl((COLOR),(COLOR),(COLOR),BLACK,8.0f)
namespace d3d{
	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, D3DXCOLOR p)
	{
		D3DMATERIAL9 mtrl;
		mtrl.Ambient = a;
		mtrl.Diffuse = d;
		mtrl.Emissive = e;
		mtrl.Power = p;
		mtrl.Specular = s;
		return mtrl;
	}
	CREATE_MTRL(WHITE_MTRL, WHITE);
	CREATE_MTRL(RED_MTRL, RED);
	CREATE_MTRL(GREEN_MTRL,GREEN);
	CREATE_MTRL(BLUE_MTRL, BLUE);
	CREATE_MTRL(YELLOW_MTRL, YELLOW);
}
#endif

