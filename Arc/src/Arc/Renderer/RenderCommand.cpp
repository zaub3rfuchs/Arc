#include "apch.h"
#include "Arc/Renderer/RenderCommand.h"


namespace ArcEngine {

	//Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
