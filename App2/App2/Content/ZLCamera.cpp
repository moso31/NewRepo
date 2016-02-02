#include "pch.h"
#include "ZLCamera.h"

using namespace Windows::Foundation;

ZLCamera::ZLCamera()
{
}

ZLCamera::ZLCamera(const std::shared_ptr<DX::DeviceResources>& deviceResources)
{
	m_deviceResources = deviceResources;
}

void ZLCamera::CameraBuild(float eyeX, float eyeY, float eyeZ, float atX, float atY, float atZ, float upX, float upY, float upZ)
{
	Size outputSize = m_deviceResources->GetOutputSize();
	float aspectRatio = outputSize.Width / outputSize.Height;
	float fovAngleY = 70.0f * XM_PI / 180.0f;

	// 这是一个简单的更改示例，当应用程序在纵向视图或对齐视图中时，可以进行此更改
	// 。
	if (aspectRatio < 1.0f)
	{
		fovAngleY *= 2.0f;
	}

	// 请注意，OrientationTransform3D 矩阵在此处是后乘的，
	// 以正确确定场景的方向，使之与显示方向匹配。
	// 对于交换链的目标位图进行的任何绘制调用
	// 交换链呈现目标。对于到其他目标的绘制调用，
	// 不应应用此转换。

	// 此示例使用行主序矩阵利用右手坐标系。
	XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovRH(
		fovAngleY,
		aspectRatio,
		0.01f,
		100.0f
		);

	XMFLOAT4X4 orientation = m_deviceResources->GetOrientationTransform3D();

	XMMATRIX orientationMatrix = XMLoadFloat4x4(&orientation);

	XMStoreFloat4x4(
		&ZLBufferManager::m_constantBufferData.projection,
		XMMatrixTranspose(perspectiveMatrix * orientationMatrix)
		);

	// 眼睛位于(0,0.7,1.5)，并沿着 Y 轴使用向上矢量查找点(0,-0.1,0)。
	m_eye = { eyeX, eyeY, eyeZ, 0.0f };
	m_at = { atX, atY, atZ, 0.0f };
	m_up = { upX, upY, upZ, 0.0f };

	Doit();
}

ZLCamera::~ZLCamera()
{
}

void ZLCamera::CameraTranslation(XMFLOAT3 v)
{
	m_eye.x += v.x;
	m_eye.y += v.y;
	m_eye.z += v.z;
	m_at.x += v.x;
	m_at.y += v.y;
	m_at.z += v.z;

	Doit();
}

void ZLCamera::Doit()
{
	XMVECTORF32 eye = { m_eye.x, m_eye.y, m_eye.z, m_eye.w };
	XMVECTORF32 at = { m_at.x, m_at.y, m_at.z, m_at.w };
	XMVECTORF32 up = { m_up.x, m_up.y, m_up.z, m_up.w };

	XMStoreFloat4x4(&ZLBufferManager::m_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));
}