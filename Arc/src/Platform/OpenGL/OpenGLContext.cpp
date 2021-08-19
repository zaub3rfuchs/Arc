#include "apch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace ArcEngine {



	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_Window(window)
	{
		ARC_CORE_ASSERT(window, "Window is null!")
	}

	void OpenGLContext::Init()
	{
		ARC_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ARC_CORE_ASSERT(status, "Failed to initialize Glad!");

		ARC_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		ARC_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
		
		#ifdef ARC_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		ARC_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Arc Engine requires at least OpenGL version 4.5!");
#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}