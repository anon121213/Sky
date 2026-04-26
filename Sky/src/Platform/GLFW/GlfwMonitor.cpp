#include "skypch.h"
#include "GlfwMonitor.h"

#include <GLFW/glfw3.h>

namespace Sky
{
	Scope<Monitor> Monitor::CreatePrimary()
	{
		return CreateScope<GlfwMonitor>();
	}

	GlfwMonitor::GlfwMonitor()
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		if (!monitor)
			return;

		if (const GLFWvidmode* mode = glfwGetVideoMode(monitor))
		{
			m_Width = mode->width;
			m_Height = mode->height;
			m_RefreshRate = mode->refreshRate;
		}

		float xscale = 1.0f, yscale = 1.0f;
		glfwGetMonitorContentScale(monitor, &xscale, &yscale);
		m_ContentScale = xscale;

		if (const char* name = glfwGetMonitorName(monitor))
			m_Name = name;
	}
}
