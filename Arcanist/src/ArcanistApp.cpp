#include <Arc.h>
#include <Arc/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace ArcEngine {



	class Arcanist : public Application
	{
	public:
		Arcanist(ApplicationCommandLineArgs args)
			: Application("Arcanist", args)
		{
			PushLayer(new EditorLayer());
		}
		~Arcanist()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "Arcanist";
		spec.CommandLineArgs = args;

		return new Arcanist(args);
	}

}
