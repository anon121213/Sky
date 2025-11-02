#pragma once

#include "Core.h"

#include "Window.h"
#include "Sky/Core/LayerStack.h"
#include "Sky/Events/Event.h"
#include "Sky/Events/ApplicationEvent.h"

#include "Sky/Core/Timestep.h"

#include "Sky/ImGui/ImGuiLayer.h"

namespace Sky {

	class SKY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() const { return *m_Window; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();

}