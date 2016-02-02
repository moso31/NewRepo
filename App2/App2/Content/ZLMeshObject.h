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
	// ������豸��Դָ�롣
	std::shared_ptr<DX::DeviceResources> m_deviceResources;

	Microsoft::WRL::ComPtr<ID3D11Buffer>		m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer>		m_indexBuffer;

	//���ڴ洢��ģ�;���
public:
	XMFLOAT4X4 m_Model;
	
public:
	vector<VertexPositionColor> m_Verties;
	vector<unsigned short> m_Indies;
};