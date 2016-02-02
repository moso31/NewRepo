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
	//direction：最后一次左键按下后鼠标的偏移量。
	//objL(R)记录左右手的实际位置，用来显示在屏幕上。
	XMFLOAT3 objL, objR;

	//如果是左手移动指令，修改相对应的左手偏移量。
	if (isMovingLeft)
	{
		m_moveL = direction;
		objL.x = m_posL.x + m_moveL.x;
		objL.y = m_posL.y + m_moveL.y;
		objL.z = m_posL.z + m_moveL.z;
		zl_mover->translation(left, objL);
	}
	//如果是右手……
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