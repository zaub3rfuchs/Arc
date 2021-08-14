#pragma once

#include "Arc/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace ArcEngine {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void SwapBuffers() override;
		virtual void Init() override;
	private:
		GLFWwindow* m_Window;
	};

}