#include "skypch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Sky {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle) 
	{
		SKY_CORE_ACCERT(windowHandle, "Window handle us null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SKY_CORE_ACCERT(status, "Falied to intialize GLAD!");
	}

	void OpenGLContext::SwapBuffers() 
	{

		glfwSwapBuffers(m_WindowHandle);
	}
}