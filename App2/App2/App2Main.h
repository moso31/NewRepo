#pragma once

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "Content\Sample3DSceneRenderer.h"
#include "Content\SampleFpsTextRenderer.h"

// 在屏幕上呈现 Direct2D 和 3D 内容。
namespace App2
{
	class App2Main : public DX::IDeviceNotify
	{
	public:
		App2Main(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~App2Main();
		void CreateWindowSizeDependentResources();
		void StartTracking(float positionX, float positionY) { m_sceneRenderer->StartTracking(positionX, positionY); }
		void TrackingUpdate(float positionX, float positionY, bool lPress, bool rPress) { m_pointerLocationX = positionX; m_pointerLocationY = positionY; m_pointerPressedL = lPress; m_pointerPressedR = rPress; }
		void StopTracking() { m_sceneRenderer->StopTracking(); }
		bool IsTracking() { return m_sceneRenderer->IsTracking(); }
		void StartRenderLoop();
		void StopRenderLoop();
		void WheelChanged(float, float, int);
		Concurrency::critical_section& GetCriticalSection() { return m_criticalSection; }

		void OnKeyDown(Windows::System::VirtualKey key);
		void OnKeyUp(Windows::System::VirtualKey key);

		// IDeviceNotify
		virtual void OnDeviceLost();
		virtual void OnDeviceRestored();

	private:
		void ProcessInput();
		void Update();
		bool Render();

		// 缓存的设备资源指针。
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// TODO: 替换为你自己的内容呈现器。
		std::unique_ptr<Sample3DSceneRenderer> m_sceneRenderer;
		std::unique_ptr<SampleFpsTextRenderer> m_fpsTextRenderer;

		Windows::Foundation::IAsyncAction^ m_renderLoopWorker;
		Concurrency::critical_section m_criticalSection;

		// 渲染循环计时器。
		DX::StepTimer m_timer;

		//跟踪当前输入指针位置
		float m_pointerLocationX, m_pointerLocationY;

		//跟踪鼠标按下的状态
		bool m_pointerPressedL, m_pointerPressedR;
	};
}