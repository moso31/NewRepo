#pragma once

#include "ZL3DMath.h"

class ZLCamera {
public:
	ZLCamera();
	ZLCamera(const std::shared_ptr<DX::DeviceResources>& deviceResources);
	void CameraBuild(float eyeX, float eyeY, float eyeZ, float atX, float atY, float atZ, float upX, float upY, float upZ);
	~ZLCamera();

	void CameraTranslation(XMFLOAT3 v, bool isLR);
	void CameraRotation(XMFLOAT3 v);

	void Doit();

private:
	// 缓存的设备资源指针。
	std::shared_ptr<DX::DeviceResources> m_deviceResources;
	XMFLOAT4 m_eye, m_at, m_up;

	ZL3DMath *zl_math;
};
