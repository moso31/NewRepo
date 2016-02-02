#include "pch.h"
#include "ZLBufferManager.h"

using namespace App2;

Microsoft::WRL::ComPtr<ID3D11Buffer>	ZLBufferManager::m_constantBuffer;
ModelViewProjectionConstantBuffer	ZLBufferManager::m_constantBufferData;

ZLBufferManager::ZLBufferManager() {}
ZLBufferManager::ZLBufferManager(std::shared_ptr<DX::DeviceResources> deviceResources) {
	m_deviceResources = deviceResources;
}