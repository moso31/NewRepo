#pragma once

using namespace App2;

class ZLBufferManager {
public:
	ZLBufferManager();
	ZLBufferManager(std::shared_ptr<DX::DeviceResources> deviceResources);
	~ZLBufferManager()
	{

	}

private:
	// 缓存的设备资源指针。
	std::shared_ptr<DX::DeviceResources> m_deviceResources;
public:
	static Microsoft::WRL::ComPtr<ID3D11Buffer>	m_constantBuffer; 
	//系统资源。
	static ModelViewProjectionConstantBuffer	m_constantBufferData;

private:
};