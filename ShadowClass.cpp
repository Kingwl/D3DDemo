#include "ShadowClass.h"
#include "iostream"
ShadowClass::ShadowClass(IDirect3DDevice9 *Device)
:_Device(Device), _isInit(false), _Mesh(nullptr)
{

}

ShadowClass::~ShadowClass()
{
	if (_Mesh != nullptr)
	{
		_Mesh->Release();
		_Mesh = nullptr;
	}
}
bool ShadowClass::initContext(D3DXVECTOR4 *lightDirection, D3DXPLANE *Plane, D3DXVECTOR3 *Position, ID3DXMesh *Mesh)
{

	setContext();
	_LightDir =  *lightDirection;
	_ObjPosition = *Position;
	_shadowPlane = *Plane;
	_Mesh = Mesh;
	_isInit = true;
	return true;
}

bool ShadowClass::drawShadowMesh()
{
	if (_Mesh == nullptr || _isInit == false) return false;
	initShadow();
	_Device->SetTransform(D3DTS_WORLD, &_shadowMatrix);

	D3DMATERIAL9 mtrl = d3d::InitMtrl(d3d::BLACK, d3d::BLACK, d3d::BLACK, d3d::BLACK, 0.0f);
	mtrl.Diffuse.a = 0.5f;

	_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	_Device->SetRenderState(D3DRS_ZENABLE, true);

	_Device->SetMaterial(&mtrl);
	_Device->SetTexture(0, 0);
	_Mesh->DrawSubset(0);

	_Device->SetRenderState(D3DRS_ZENABLE, true);
	_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	_Device->SetRenderState(D3DRS_STENCILENABLE, false);
	return true;
}
bool ShadowClass::initShadow()
{
	D3DXMATRIX S;
	D3DXMatrixShadow(
		&S,
		&_LightDir,
		&_shadowPlane);
	D3DXMATRIX T;
	D3DXMatrixTranslation(
		&T,
		_ObjPosition.x,
		_ObjPosition.y,
		_ObjPosition.z);

	_shadowMatrix = T * S;
	return true;
}
void ShadowClass::setContext()
{
	_Device->SetRenderState(D3DRS_STENCILENABLE, true);
	_Device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	_Device->SetRenderState(D3DRS_STENCILREF, 0x0);
	_Device->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
	_Device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
	_Device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	_Device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	_Device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
}
