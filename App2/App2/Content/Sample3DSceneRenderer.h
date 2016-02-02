#pragma once

#include "..\Common\DeviceResources.h"
#include "ShaderStructures.h"
#include "..\Common\StepTimer.h"

#include "ZLFileLoader.h"
#include "ZLMeshObject.h"
#include "ZLBufferManager.h"
#include "ZLShaderManager.h"
#include "ZLEasyBuilder.h"
#include "ZLCamera.h"
#include "ZLMoniHands.h"

namespace App2
{
	// 此示例呈现器实例化一个基本渲染管道。
	class Sample3DSceneRenderer
	{
	public:
		Sample3DSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void CreateDeviceDependentResources();
		void CreateWindowSizeDependentResources();
		void ReleaseDeviceDependentResources();
		void Update(DX::StepTimer const& timer);
		void Render();
		void StartTracking(float positionX, float positionY);
		void TrackingUpdate(float positionX, float positionY, bool lPress, bool rPress);
		void StopTracking();
		void WheelChanged(float positionX, float positionY, int delta);
		bool IsTracking() { return m_tracking; }
		void OnKeyDown(Windows::System::VirtualKey key);
		void OnKeyUp(Windows::System::VirtualKey key);

	private:
		void Rotate(float radians);

	private:
		// 缓存的设备资源指针。
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// 用于渲染循环的变量。
		bool	m_loadingComplete;
		bool	m_tracking;
		bool	m_leftPressed, m_rightPressed;

		// 记录鼠标在上一帧的位置
		XMFLOAT2 m_lastMousePosition;
		// 记录鼠标最后一次点击时的坐标。
		XMFLOAT2 m_lastClick;
		// 记录鼠标最后一次点击的位移量。
		// 用LR两个变量使得左右手的位移量能够区分开来。
		XMFLOAT3 m_move;

		//记录正在按下的键位
		Windows::System::VirtualKey m_KeyPressed;

		ZLFileLoader *m_fileLoader;

		ZLBufferManager *zl_buffer;
		ZLShaderManager *zl_shader;
		ZLEasyBuilder *zl_builder;
		ZLCamera *zl_camera;
		ZLObjectMover *zl_mover;

		ZLMeshObject *mod_centerObj;
		ZLMoniHands *mod_hands;
	};
}

