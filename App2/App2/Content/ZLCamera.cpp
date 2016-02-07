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

	// ����һ���򵥵ĸ���ʾ������Ӧ�ó�����������ͼ�������ͼ��ʱ�����Խ��д˸���
	// 
	if (aspectRatio < 1.0f)
	{
		fovAngleY *= 2.0f;
	}

	// ��ע�⣬OrientationTransform3D �����ڴ˴��Ǻ�˵ģ�
	// ����ȷȷ�������ķ���ʹ֮����ʾ����ƥ�䡣
	// ���ڽ�������Ŀ��λͼ���е��κλ��Ƶ���
	// ����������Ŀ�ꡣ���ڵ�����Ŀ��Ļ��Ƶ��ã�
	// ��ӦӦ�ô�ת����

	// ��ʾ��ʹ�����������������������ϵ��
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

	// �۾�λ��(0,0.7,1.5)�������� Y ��ʹ������ʸ�����ҵ�(0,-0.1,0)��
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
	//������ƶ�����direction
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
	//v���������ƶ�����
	//eyeΧ����(at, at + up)������ת�� 
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