#pragma once
#ifndef _COLOR_
#define _COLOR_
#include "d3dx9.h"
namespace d3d{
	const D3DXCOLOR WHITE(D3DCOLOR_XRGB(0xff, 0xff, 0xff));
	const D3DXCOLOR BLACK(D3DCOLOR_XRGB(0x0, 0x0, 0x0));
	const D3DXCOLOR RED(D3DCOLOR_XRGB(0xff, 0x0, 0x0));
	const D3DXCOLOR GREEN(D3DCOLOR_XRGB(0x0, 0xff, 0x0));
	const D3DXCOLOR BLUE(D3DCOLOR_XRGB(0x0, 0x0, 0xff));
	const D3DXCOLOR YELLOW(D3DCOLOR_XRGB(0xff, 0xff, 0x0));
	const D3DXCOLOR CYAN(D3DCOLOR_XRGB(0x0, 0xff, 0xff));
	const D3DXCOLOR MAGENTA(D3DCOLOR_XRGB(0xff, 0x0, 0xff));
}
#endif 