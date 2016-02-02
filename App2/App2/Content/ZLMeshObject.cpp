#include "pch.h"
#include "ZLMeshObject.h"
#include "../Common/DirectXHelper.h"

using namespace std;
using namespace DirectX;

ZLMeshObject::ZLMeshObject() {
}
ZLMeshObject::ZLMeshObject(std::shared_ptr<DX::DeviceResources> deviceResources) {
	m_deviceResources = deviceResources;
}
ZLMeshObject::~ZLMeshObject() {
}
void ZLMeshObject::MeshLoader() {
}

void ZLMeshObject::Draw()
{
	auto context = m_deviceResources->GetD3DDeviceContext();

	ZLBufferManager::m_constantBufferData.model = m_Model;

	// 准备常量缓冲区以将其发送到图形设备。
	context->UpdateSubresource(
		ZLBufferManager::m_constantBuffer.Get(),
		0,
		NULL,
		&ZLBufferManager::m_constantBufferData,
		0,
		0
		);

	// 每个顶点都是 VertexPositionColor 结构的一个实例。
	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;
	context->IASetVertexBuffers(
		0,
		1,
		m_vertexBuffer.GetAddressOf(),
		&stride,
		&offset
		);

	context->IASetIndexBuffer(
		m_indexBuffer.Get(),
		DXGI_FORMAT_R16_UINT, // 每个索引都是一个 16 位无符号整数(short)。
		0
		);

	// 绘制对象。
	context->DrawIndexed(
		m_Indies.size(),
		0,
		0
		);
}

void ZLMeshObject::SetVBIB() {
	VertexPositionColor *cubeVertices = new VertexPositionColor[m_Verties.size()];
	unsigned short *cubeIndices = new unsigned short[m_Indies.size()];

	for (unsigned i = 0; i < m_Verties.size(); i++)
		cubeVertices[i] = m_Verties[i];

	for (unsigned i = 0; i < m_Indies.size(); i++)
		cubeIndices[i] = m_Indies[i];

	D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
	vertexBufferData.pSysMem = cubeVertices;
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(VertexPositionColor) * m_Verties.size(), D3D11_BIND_VERTEX_BUFFER);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&vertexBufferDesc,
			&vertexBufferData,
			&m_vertexBuffer
			)
		);

	D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
	indexBufferData.pSysMem = cubeIndices;
	indexBufferData.SysMemPitch = 0;
	indexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC indexBufferDesc(sizeof(unsigned short) * m_Indies.size(), D3D11_BIND_INDEX_BUFFER);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&indexBufferDesc,
			&indexBufferData,
			&m_indexBuffer
			)
		);
}
