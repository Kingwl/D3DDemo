#include "DeviceManager.h"
DeviceManager *DeviceManager::_instance = nullptr;
DeviceManager* DeviceManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new DeviceManager();
	}
	return _instance;
}
DeviceManager::DeviceManager()
:_Device(nullptr), _isInit(false)
{
}
DeviceManager::~DeviceManager()
{
}
void DeviceManager::initDevice(IDirect3DDevice9 *Device)
{
	_Device = Device;
	_isInit = true;
}
IDirect3DDevice9* DeviceManager::getDevice()
{
	return _Device;
}