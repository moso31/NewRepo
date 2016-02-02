#include "pch.h"
#include "ZLShaderManager.h"
#include "ZLBufferManager.h"
#include "../Common/DirectXHelper.h"

using namespace App2;

ZLShaderManager::ZLShaderManager()
{
	fileLoader = new ZLFileLoader();
}

ZLShaderManager::ZLShaderManager(std::shared_ptr<DX::DeviceResources> deviceResources)
	:ZLShaderManager()
{
	m_deviceResources = deviceResources;
}

void ZLShaderManager::Loader()
{
	auto fileVSData = fileLoader->ReadData(L"SampleVertexShader.cso");
	auto filePSData = fileLoader->ReadData(L"SamplePixelShader.cso");

	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateVertexShader(
			&fileVSData[0],
			fileVSData->Length,
			nullptr,
			&m_vertexShader
			)
		);		
	
	static const D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateInputLayout(
			vertexDesc,
			ARRAYSIZE(vertexDesc),
			&fileVSData[0],
			fileVSData->Length,
			&m_inputLayout
			)
		);

	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreatePixelShader(
			&filePSData[0],
			filePSData->Length,
			nullptr,
			&m_pixelShader
			)
		);

	CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&constantBufferDesc,
			nullptr,
			&ZLBufferManager::m_constantBuffer
			)
		);
}

void ZLShaderManager::Addons() {
	auto context = m_deviceResources->GetD3DDeviceContext();

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->IASetInputLayout(m_inputLayout.Get());

	// 附加我们的顶点着色器。
	context->VSSetShader(
		m_vertexShader.Get(),
		nullptr,
		0
		);

	// 将常量缓冲区发送到图形设备。
	context->VSSetConstantBuffers(
		0,
		1,
		ZLBufferManager::m_constantBuffer.GetAddressOf()
		);

	// 附加我们的像素着色器。
	context->PSSetShader(
		m_pixelShader.Get(),
		nullptr,
		0
		);
}