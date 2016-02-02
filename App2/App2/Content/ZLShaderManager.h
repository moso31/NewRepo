#pragma once
#include "ZLFileLoader.h"

class ZLShaderManager {
public:
	ZLShaderManager();
	ZLShaderManager(std::shared_ptr<DX::DeviceResources> deviceResources);
	~ZLShaderManager()
	{

	}

	void Loader();
	void Addons();

private:
	// 缓存的设备资源指针。
	std::shared_ptr<DX::DeviceResources> m_deviceResources;

	// Direct3D 资源。
	Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_pixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_inputLayout;

	ZLFileLoader *fileLoader;
};