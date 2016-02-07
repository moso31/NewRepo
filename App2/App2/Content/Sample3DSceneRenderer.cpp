#include "pch.h"
#include "Sample3DSceneRenderer.h"

#include "..\Common\DirectXHelper.h"

using namespace App2;

using namespace DirectX;
using namespace Windows::Foundation;
using namespace Windows::System;

// 从文件中加载顶点和像素着色器，然后实例化立方体几何图形。
Sample3DSceneRenderer::Sample3DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
	m_loadingComplete(false),
	m_tracking(false),
	m_deviceResources(deviceResources)
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}

// 当窗口的大小改变时初始化视图参数。
void Sample3DSceneRenderer::CreateWindowSizeDependentResources()
{
	zl_camera = new ZLCamera(m_deviceResources);
	zl_camera->CameraBuild(0.0f, 0.7f, 1.5f, 0.0f, -0.1f, 0.0f, 0.0f, 1.0f, 0.0f);
}

// 每个帧调用一次，旋转立方体，并计算模型和视图矩阵。
void Sample3DSceneRenderer::Update(DX::StepTimer const& timer)
{
	if (!m_tracking)
	{
	}
}

// 将 3D 立方体模型旋转一定数量的弧度。
void Sample3DSceneRenderer::Rotate(float radians)
{
}

void Sample3DSceneRenderer::StartTracking(float positionX, float positionY)
{
	m_tracking = true;
	m_lastClick = { positionX, positionY };
	m_move = { 0.0f, 0.0f, 0.0f };
	mod_hands->StartTracking();
}

// 进行跟踪时，可跟踪指针相对于输出屏幕宽度的位置，从而让 3D 立方体围绕其 Y 轴旋转。
void Sample3DSceneRenderer::TrackingUpdate(float positionX, float positionY, bool lPress, bool rPress)
{
	m_leftPressed = lPress;
	m_rightPressed = rPress;
	m_move.x = positionX - m_lastMousePosition.x;
	m_move.y = positionY - m_lastMousePosition.y;
	m_move.x *= -0.001f;
	m_move.y *= 0.001f;
	m_move.z = 0.0f;

	// 如果是在按下Ctrl时进行的鼠标操作，就改换摄像机的相对位置
	if (m_KeyPressed == VirtualKey::Control)
	{
		zl_camera->CameraRotation(m_move);
	}

	if (m_KeyPressed == VirtualKey::Shift)
	{
		zl_camera->CameraTranslation(m_move, true);
	}

	if (m_tracking)
	{
		//一开始就在中间放个大正方体--测试用。
		zl_mover->rotation(mod_centerObj, 0.2f, 0.0f, 0.0f);

		//记录本次鼠标按下后的位移量
		m_move.x = positionX - m_lastClick.x;
		m_move.y = positionY - m_lastClick.y;
		m_move.x *= 0.001f;
		m_move.y *= -0.001f;

		if (m_leftPressed) 
		{
			mod_hands->MoveHand(m_move, true);
		}
		if (m_rightPressed)
		{
			mod_hands->MoveHand(m_move, false);
		}
	}

	m_lastMousePosition = { positionX, positionY };
}

void Sample3DSceneRenderer::StopTracking()
{
	m_tracking = false;
	mod_hands->recordNewCoordinate(mod_hands->LeftHand(), true);
	mod_hands->recordNewCoordinate(mod_hands->RightHand(), false);
} 

void App2::Sample3DSceneRenderer::WheelChanged(float positionX, float positionY, int delta)
{
	if (m_KeyPressed == VirtualKey::Shift)
	{
		m_move.z = delta / 120.0f * -0.05f;
		zl_camera->CameraTranslation(m_move, false);
	}

	if (m_leftPressed) {
		m_move = { 0.0f, 0.0f, delta / 120.0f * -0.05f };

		mod_hands->MoveHand(m_move, true);
		mod_hands->recordNewCoordinate(m_move, true);
	}
	if (m_rightPressed) {
		m_move = { 0.0f, 0.0f, delta / 120.0f * -0.05f };

		mod_hands->MoveHand(m_move, false);
		mod_hands->recordNewCoordinate(m_move, false);
	}
}

// 使用顶点和像素着色器呈现一个帧。
void Sample3DSceneRenderer::Render()
{
	// 加载是异步的。仅在加载几何图形后才会绘制它。
	if (!m_loadingComplete)
	{
		return;
	}

	zl_shader->Addons();

	mod_hands->Render();

	mod_centerObj->Draw();
}

void Sample3DSceneRenderer::CreateDeviceDependentResources()
{
	zl_shader = new ZLShaderManager(m_deviceResources);
	zl_shader->Loader();

	zl_buffer = new ZLBufferManager(m_deviceResources);

	// 创建模拟手。模拟手是基本操作元件，默认构造函数中创建好对象。所以不需要zl_builder创建模型。
	mod_hands = new ZLMoniHands(m_deviceResources);

	// 创建中心物体。
	mod_centerObj = new ZLMeshObject(m_deviceResources);

	zl_builder->CreateCube(mod_centerObj, 0.5f);
	m_loadingComplete = true;
}

void Sample3DSceneRenderer::ReleaseDeviceDependentResources()
{
	m_loadingComplete = false;
}

void Sample3DSceneRenderer::OnKeyDown(VirtualKey key)
{
	m_KeyPressed = key;
}

void Sample3DSceneRenderer::OnKeyUp(VirtualKey key)
{
	m_KeyPressed = VirtualKey::None;
}