#pragma once

#include "Core.h"

#include "Window.h"

#include "Events/Event.h"
#include "Arc/Events/ApplicationEvent.h"

#include "Arc/LayerStack.h"
#include "Arc/ImGui/ImGuiLayer.h"

#include "Arc/Renderer/Shader.h"
#include "Arc/Renderer/Buffer.h"
#include "Arc/Renderer/VertexArray.h"

#include "Arc/Renderer/OrthographicCamera.h"

namespace ArcEngine {

	class ARC_API Application
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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;


	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}
