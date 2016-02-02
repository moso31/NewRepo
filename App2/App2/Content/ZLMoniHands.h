#pragma once
#include "ZLMeshObject.h"
#include "ZLEasyBuilder.h"
#include "ZLObjectMover.h"

class ZLMoniHands {
public:
	ZLMoniHands();
	ZLMoniHands(std::shared_ptr<DX::DeviceResources> deviceResources);
	void Create();
	void Render();
	void Update();
	void StartTracking();
	void MoveHand(XMFLOAT3, bool);
	void recordNewCoordinate(XMFLOAT3 move, bool isLeftPressed);

	void LeftHand(float x, float y, float z) { m_moveL = { x, y, z }; }
	void LeftHand(XMFLOAT3 v) { m_moveL = v; }
	void RightHand(float x, float y, float z) { m_moveR = { x, y, z }; }
	void RightHand(XMFLOAT3 v) { m_moveR = v; }
	XMFLOAT3 LeftHand() { return this->m_moveL; }
	XMFLOAT3 RightHand() { return this->m_moveR; }
private:
	// 缓存的设备资源指针。
	std::shared_ptr<DX::DeviceResources> m_deviceResources;

	ZLEasyBuilder *zl_builder;
	ZLObjectMover *zl_mover;

	ZLMeshObject *left, *right;

	// 存储双手在世界坐标系的位移量。
	XMFLOAT3 m_posL, m_posR;

	// 存储双手单次的相对位移量。
	XMFLOAT3 m_moveL, m_moveR;
};