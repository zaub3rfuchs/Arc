#include <Arc.h>

//#include "imgui/imgui.h"

class ExampleLayer : public ArcEngine::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
	}


	void OnUpdate() override
	{
	}
	virtual void OnImGuiRender() override
	{
		//ImGui::Begin("Test");
		//ImGui::Text("Hello World");
		//ImGui::End();
	}


	void OnEvent(ArcEngine::Event& e) override
	{
		if (e.GetEventType() == ArcEngine::EventType::KeyPressed)
		{

		}
	}



};

class Sandbox : public ArcEngine::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox() 
	{

	}
};

ArcEngine::Application* ArcEngine::CreateApplication()
{
	return new Sandbox();
}