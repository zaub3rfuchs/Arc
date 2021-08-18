#pragma once

#include "Core.h"

#include "Window.h"

#include "Events/Event.h"
#include "Arc/Events/ApplicationEvent.h"

#include "Arc/Core/Timestep.h"

#include "Arc/LayerStack.h"
#include "Arc/ImGui/ImGuiLayer.h"

namespace ArcEngine {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; };
		inline Window& GetWindow() { return *m_Window; };
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		Timestep m_TimeStep;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}
