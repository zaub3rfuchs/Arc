#include <Arc.h>
#include <Arc/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include "ExampleLayer.h"
#include "Sandbox2D.h"


class Sandbox : public ArcEngine::Application
{
public:
	Sandbox(const ArcEngine::ApplicationSpecification& specification)
		: ArcEngine::Application(specification)
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	~Sandbox() 
	{

	}
};

ArcEngine::Application* ArcEngine::CreateApplication(ArcEngine::ApplicationCommandLineArgs args)
{
	ApplicationSpecification spec;
	spec.Name = "Sandbox";
	spec.WorkingDirectory = "../Arcanist";
	spec.CommandLineArgs = args;
}
