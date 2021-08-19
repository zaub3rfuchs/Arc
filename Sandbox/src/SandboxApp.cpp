#include <Arc.h>
#include <Arc/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include "ExampleLayer.h"
#include "Sandbox2D.h"


class Sandbox : public ArcEngine::Application
{
public:
	Sandbox() 
		: Application()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	~Sandbox() 
	{

	}
};

ArcEngine::Application* ArcEngine::CreateApplication()
{
	return new Sandbox();
}