#pragma once
#ifndef _DEVICEMANAGER_
#define _DEVICEMANAGER_
#include "d3dx9.h"
#include "DeviceManager.h"
class DeviceManager
{
public:
	static DeviceManager* getInstance();
	void initDevice(IDirect3DDevice9 *Device);
	IDirect3DDevice9* getDevice();
private:
	static DeviceManager *_instance;
	IDirect3DDevice9 *_Device;
	bool _isInit;
	DeviceManager();

	~DeviceManager();
};
#endif
