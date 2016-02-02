#include "pch.h"
#include "ZLMoniHands.h"

ZLMoniHands::ZLMoniHands()
{
}

ZLMoniHands::ZLMoniHands(std::shared_ptr<DX::DeviceResources> deviceResources)
{
	m_deviceResources = deviceResources;
	Create();
}

void ZLMoniHands::Create()
{
	left = new ZLMeshObject(m_deviceResources);
	right = new ZLMeshObject(m_deviceResources);
	zl_builder->CreateCube(left, 0.05f);
	zl_builder->CreateCube(right, 0.05f);
	m_posL = { -1.0f, 0.0f, 0.0f };
	m_posR = { 1.0f, 0.0f, 0.0f };
}

void ZLMoniHands::Render()
{
	left->Draw();
	right->Draw();
}

void ZLMoniHands::Update()
{
}

void ZLMoniHands::StartTracking()
{
	m_moveL = m_moveR = { 0.0f, 0.0f, 0.0f };
}

void ZLMoniHands::MoveHand(XMFLOAT3 direction, bool isMovingLeft)
{
	//direction�����һ��������º�����ƫ������
	//objL(R)��¼�����ֵ�ʵ��λ�ã�������ʾ����Ļ�ϡ�
	XMFLOAT3 objL, objR;

	//����������ƶ�ָ��޸����Ӧ������ƫ������
	if (isMovingLeft)
	{
		m_moveL = direction;
		objL.x = m_posL.x + m_moveL.x;
		objL.y = m_posL.y + m_moveL.y;
		objL.z = m_posL.z + m_moveL.z;
		zl_mover->translation(left, objL);
	}
	//��������֡���
	else
	{
		m_moveR = direction;
		objR.x = m_posR.x + m_moveR.x;
		objR.y = m_posR.y + m_moveR.y;
		objR.z = m_posR.z + m_moveR.z;
		zl_mover->translation(right, objR);
	}
}

void ZLMoniHands::recordNewCoordinate(XMFLOAT3 move, bool isLeftPressed)
{
	if (isLeftPressed) {
		m_posL.x += move.x;
		m_posL.y += move.y;
		m_posL.z += move.z;
	}
	else
	{
		m_posR.x += move.x;
		m_posR.y += move.y;
		m_posR.z += move.z;
	}
}