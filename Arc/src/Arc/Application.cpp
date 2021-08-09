#include "apch.h"

#include "Application.h"


#include "Arc/Log.h"

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace ArcEngine {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		//if the event of e is a WindowCloseEvent call the Event Function OnWindowClose
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		ARC_CORE_TRACE("{0}", e);
	}


	void Application::Run()
	{
		while (m_Running)
			m_Window->OnUpdate();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}