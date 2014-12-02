#pragma once
#ifndef _CAMERA_
#define _CAMERA_
#include "d3dx9.h"
#include "DeviceManager.h"
class Camera
{
public:
	void fly(float units);
	void walk(float units);
	void strafe(float units);
	void getViewMatrix(D3DXMATRIX *V);
	void getPosition(D3DXVECTOR3 *pos);
	void getRight(D3DXVECTOR3 *right);
	void getUp(D3DXVECTOR3 *up);
	void getLook(D3DXVECTOR3 *look);
	void setPosition(D3DXVECTOR3 *pos);

	void pitch(float angle);
	void yaw(float angle);
	void roll(float angle);
	static Camera* getInstance();
private:
	Camera();
	~Camera();
	D3DXVECTOR3 _pos;
	D3DXVECTOR3 _up;
	D3DXVECTOR3 _look;
	D3DXVECTOR3 _right;
	static Camera* _instance;
	void reset();
};

#endif