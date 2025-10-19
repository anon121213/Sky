#pragma once

#include "Core.h"

#include "Window.h"
#include "Sky/LayerStack.h"
#include "Sky/Events/Event.h"
#include "Sky/Events/ApplicationEvent.h"


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
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	Application* CreateApplication();

}