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
	// ������豸��Դָ�롣
	std::shared_ptr<DX::DeviceResources> m_deviceResources;

	// Direct3D ��Դ��
	Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_pixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_inputLayout;

	ZLFileLoader *fileLoader;
};