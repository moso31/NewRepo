#pragma once
#include <vector>

using namespace std;
using namespace DirectX;
using namespace App2;

class ZLMeshObject {
public:
	ZLMeshObject();
	ZLMeshObject(std::shared_ptr<DX::DeviceResources> deviceResources);
	~ZLMeshObject();
	void MeshLoader();
	void Draw();

	void SetVBIB();

private:
	// 缓存的设备资源指针。
	std::shared_ptr<DX::DeviceResources> m_deviceResources;

	Microsoft::WRL::ComPtr<ID3D11Buffer>		m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer>		m_indexBuffer;

	//用于存储的模型矩阵
public:
	XMFLOAT4X4 m_Model;
	
public:
	vector<VertexPositionColor> m_Verties;
	vector<unsigned short> m_Indies;
};