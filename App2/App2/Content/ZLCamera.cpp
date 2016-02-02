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

	// ����һ���򵥵ĸ���ʾ������Ӧ�ó�����������ͼ�������ͼ��ʱ�����Խ��д˸���
	// ��
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