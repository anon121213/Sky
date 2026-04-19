#include "skypch.h"
#include "WindowsWindow.h"

#include "Sky/Events/ApplicationEvent.h"
#include "Sky/Events/MouseEvent.h"
#include "Sky/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#define DWMWA_USE_IMMERSIVE_DARK_MODE 20
#endif

#ifndef DWMWA_WINDOW_CORNER_PREFERENCE
#define DWMWA_WINDOW_CORNER_PREFERENCE 33
#endif

#ifndef DWMWA_BORDER_COLOR
#define DWMWA_BORDER_COLOR 34
#endif

#ifndef DWMWA_CAPTION_COLOR
#define DWMWA_CAPTION_COLOR 35
#endif

#ifndef DWMWA_TEXT_COLOR
#define DWMWA_TEXT_COLOR 36
#endif

#ifndef DWMWA_SYSTEMBACKDROP_TYPE
#define DWMWA_SYSTEMBACKDROP_TYPE 38
#endif

#ifndef DWMWCP_ROUND
#define DWMWCP_ROUND 2
#endif

#ifndef DWMSBT_MAINWINDOW
#define DWMSBT_MAINWINDOW 2
#endif

namespace Sky {

	static void TrySetDwmWindowAttribute(HWND windowHandle, DWORD attribute, const void* value, DWORD size)
	{
		DwmSetWindowAttribute(windowHandle, attribute, value, size);
	}

	static void ApplyNativeTitleBarTheme(GLFWwindow* window)
	{
		HWND windowHandle = glfwGetWin32Window(window);
		if (!windowHandle)
			return;

		const BOOL darkModeEnabled = TRUE;
		const COLORREF captionColor = RGB(22, 28, 38);
		const COLORREF textColor = RGB(224, 230, 238);
		const COLORREF borderColor = RGB(52, 68, 90);
		const DWORD cornerPreference = DWMWCP_ROUND;
		const DWORD backdropType = DWMSBT_MAINWINDOW;

		TrySetDwmWindowAttribute(windowHandle, DWMWA_USE_IMMERSIVE_DARK_MODE, &darkModeEnabled, sizeof(darkModeEnabled));
		TrySetDwmWindowAttribute(windowHandle, DWMWA_CAPTION_COLOR, &captionColor, sizeof(captionColor));
		TrySetDwmWindowAttribute(windowHandle, DWMWA_TEXT_COLOR, &textColor, sizeof(textColor));
		TrySetDwmWindowAttribute(windowHandle, DWMWA_BORDER_COLOR, &borderColor, sizeof(borderColor));
		TrySetDwmWindowAttribute(windowHandle, DWMWA_WINDOW_CORNER_PREFERENCE, &cornerPreference, sizeof(cornerPreference));
		TrySetDwmWindowAttribute(windowHandle, DWMWA_SYSTEMBACKDROP_TYPE, &backdropType, sizeof(backdropType));
	}

	static bool s_GLFWInitialized = false;
	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		SKY_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Scope<Window> Window::Create(const WindowProps& props)
	{
		return CreateScope<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		SKY_PROFILE_FUNCTION();
		WindowsWindow::Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		SKY_PROFILE_FUNCTION();
		WindowsWindow::ShutDown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		SKY_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
		
		if (!s_GLFWInitialized)
		{
			SKY_PROFILE_SCOPE("glfwInit");
			int success = glfwInit();
			SKY_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		{
			SKY_PROFILE_SCOPE("glfwCreateWindow");
			m_Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), m_Data.Title.c_str(), nullptr, nullptr);
			++s_GLFWWindowCount;
		}

		ApplyNativeTitleBarTheme(m_Window);

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data =  *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int modes) {
			const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS: {
					KeyPressedEvent event(static_cast<KeyCode>(key), 0);
					data.EventCallback(event);
					break;
				}

				case GLFW_RELEASE: {
					KeyReleasedEvent event(static_cast<KeyCode>(key));
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(static_cast<KeyCode>(key), 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, const unsigned int character) {
			const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			KeyTypedEvent event(static_cast<KeyCode>(character));
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, const int button, const int action, int modes) {
			const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			
			switch (action)
			{
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, const double xOffset, const double yOffset) {
			const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, const double xPos, const double yPos) {
			const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
			data.EventCallback(event);
		});
	} 

	void WindowsWindow::ShutDown()
	{
		SKY_PROFILE_FUNCTION();
		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void WindowsWindow::OnUpdate()
	{
		SKY_PROFILE_FUNCTION();
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(const bool enabled)
	{
		SKY_PROFILE_FUNCTION();
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}
