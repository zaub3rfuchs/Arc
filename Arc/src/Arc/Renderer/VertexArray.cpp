#include "apch.h"
#include "Arc/Renderer/VertexArray.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Arc/Renderer/Renderer.h"

namespace ArcEngine {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    ARC_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

		ARC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}