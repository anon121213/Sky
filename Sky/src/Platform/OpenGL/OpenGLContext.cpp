#include "skypch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Sky {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle) 
	{
		SKY_CORE_ASSERT(windowHandle, "Window handle us null!");
	}

	void OpenGLContext::Init()
	{
		SKY_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SKY_CORE_ASSERT(status, "Falied to intialize GLAD!");

		SKY_CORE_INFO(" Vendor: {0}", (char*)(glGetString(GL_VENDOR)));
		SKY_CORE_INFO(" Renderer: {0}", (char*)(glGetString(GL_RENDERER)));
		SKY_CORE_INFO(" Version: {0}", (char*)(glGetString(GL_VERSION)));
	}

	void OpenGLContext::SwapBuffers() 
	{
		SKY_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);
	}
}