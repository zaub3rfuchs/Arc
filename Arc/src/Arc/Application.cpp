#include "apch.h"

#include "Application.h"

#include "Arc/Events/ApplicationEvent.h"
#include "Arc/Log.h"



namespace ArcEngine {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
			m_Window->OnUpdate();
	}

}