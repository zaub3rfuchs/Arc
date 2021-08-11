#include <Arc.h>


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

	void OnEvent(ArcEngine::Event& e) override
	{
	}



};






class Sandbox : public ArcEngine::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new ArcEngine::ImGuiLayer());
	}
	~Sandbox() 
	{

	}
};

ArcEngine::Application* ArcEngine::CreateApplication()
{
	return new Sandbox();
}