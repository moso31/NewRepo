#include "pch.h"
#include "ZLCamera.h"

using namespace Windows::Foundation;

ZLCamera::ZLCamera()
{
}

ZLCamera::ZLCamera(const std::shared_ptr<DX::DeviceResources>& deviceResources)
{
	zl_math = new ZL3DMath();
	m_deviceResources = deviceResources;
}

void ZLCamera::CameraBuild(float eyeX, float eyeY, float eyeZ, float atX, float atY, float atZ, float upX, float upY, float upZ)
{
	Size outputSize = m_deviceResources->GetOutputSize();
	float aspectRatio = outputSize.Width / outputSize.Height;
	float fovAngleY = 70.0f * XM_PI / 180.0f;

	// 这是一个简单的更改示例，当应用程序在纵向视图或对齐视图中时，可以进行此更改
	// 
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

void ZLCamera::CameraTranslation(XMFLOAT3 v, bool isLR)
{
	XMFLOAT4 direction;
	//计算出移动方向direction
	if (isLR)
	{
		direction = zl_math->FLOAT4xFLOAT4Cross(m_at - m_eye, m_up);
		v = { direction.x * v.x, v.y, direction.z * v.x };
	}
	else
	{
		direction = m_eye - m_at;
		v = { direction.x * v.z, v.y, direction.z * v.z };
	}

	m_eye += v;

	if (isLR)
	{
		m_at += v;
	}

	Doit();
}

void ZLCamera::CameraRotation(XMFLOAT3 v)
{ 
	//v代表鼠标的移动量。
	//eye围绕轴(at, at + up)进行旋转。 
	XMFLOAT3 eye = { m_eye.x, m_eye.y, m_eye.z };
	XMFLOAT3 v1 = { m_at.x, m_at.y, m_at.z };
	XMFLOAT3 v2 = { m_at.x + m_up.x, m_at.y + m_up.y, m_at.z + m_up.z };

	eye = zl_math->RotateAroundAxis(&eye, &v1, &v2, v.x * 3.0f);

	m_eye = { eye.x, eye.y, eye.z, m_eye.w };

	Doit();
}

void ZLCamera::Doit()
{
	XMVECTORF32 eye = { m_eye.x, m_eye.y, m_eye.z, m_eye.w };
	XMVECTORF32 at = { m_at.x, m_at.y, m_at.z, m_at.w };
	XMVECTORF32 up = { m_up.x, m_up.y, m_up.z, m_up.w };

	XMStoreFloat4x4(&ZLBufferManager::m_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));
}