#pragma once
#include "Arc/Core/Core.h"
#include "Arc/Core/Application.h"

#ifdef ARC_PLATFORM_WINDOWS

extern ArcEngine::Application* ArcEngine::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	ArcEngine::Log::Init();

	ARC_PROFILE_BEGIN_SESSION("Startup", "../logs/ArcProfile-Startup.json");
	auto app = ArcEngine::CreateApplication({ argc, argv });
	ARC_PROFILE_END_SESSION();

	ARC_PROFILE_BEGIN_SESSION("Runtime", "../logs/ArcProfile-Runtime.json");
	app->Run();
	ARC_PROFILE_END_SESSION();

	ARC_PROFILE_BEGIN_SESSION("Shutdown", "../logs/ArcProfile-Shutdown.json");
	delete app;
	ARC_PROFILE_END_SESSION();
}
#endif
