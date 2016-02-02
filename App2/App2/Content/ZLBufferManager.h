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
	// ������豸��Դָ�롣
	std::shared_ptr<DX::DeviceResources> m_deviceResources;
public:
	static Microsoft::WRL::ComPtr<ID3D11Buffer>	m_constantBuffer; 
	//ϵͳ��Դ��
	static ModelViewProjectionConstantBuffer	m_constantBufferData;

private:
};