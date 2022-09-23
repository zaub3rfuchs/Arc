#include <Arc.h>
#include <Arc/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace ArcEngine {



	class Arcanist : public Application
	{
	public:
		Arcanist(const ApplicationSpecification& spec)
			: Application(spec)
		{
			PushLayer(new EditorLayer());
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "Arcanist";
		spec.CommandLineArgs = args;

		return new Arcanist(spec);
	}

}
