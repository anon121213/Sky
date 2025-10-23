#pragma once

#include "Core.h"

#include "Window.h"
#include "Sky/LayerStack.h"
#include "Sky/Events/Event.h"
#include "Sky/Events/ApplicationEvent.h"

#include "Sky/ImGui/ImGuiLayer.h"

#include "Sky/Renderer/Shader.h"
#include "Sky/Renderer/Buffer.h"
#include "Sky/Renderer/VertexArray.h"

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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();

}