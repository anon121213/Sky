#include "Skypch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Sky/Core/Application.h"

#include "GLFW/glfw3.h"

namespace Sky {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}
	
	void ImGuiLayer::OnAttach() 
	{
		SKY_PROFILE_FUNCTION();
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void) io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Bold.ttf", 18.0f);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Regular.ttf", 18.0f);

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can lood identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		SetDarkThemeColors();

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach() 
	{
		SKY_PROFILE_FUNCTION();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnEvent(Event& e) 
	{
		SKY_PROFILE_FUNCTION();

		if (m_BlockEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			e.Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			e.Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}
	}

	void ImGuiLayer::Begin()
	{
		SKY_PROFILE_FUNCTION();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		SKY_PROFILE_FUNCTION();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(static_cast<float>(app.GetWindow().GetWidth()), static_cast<float>(app.GetWindow().GetHeight()));

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::SetDarkThemeColors()
	{
		auto& style = ImGui::GetStyle();
		auto& colors = style.Colors;

		style.WindowRounding = 3.0f;
		style.ChildRounding = 3.0f;
		style.FrameRounding = 3.0f;
		style.PopupRounding = 3.0f;
		style.ScrollbarRounding = 4.0f;
		style.GrabRounding = 3.0f;
		style.TabRounding = 3.0f;

		style.WindowBorderSize = 1.0f;
		style.ChildBorderSize = 1.0f;
		style.PopupBorderSize = 1.0f;
		style.FrameBorderSize = 1.0f;

		style.WindowPadding = ImVec2(10.0f, 8.0f);
		style.FramePadding = ImVec2(8.0f, 4.0f);
		style.ItemSpacing = ImVec2(8.0f, 6.0f);
		style.ItemInnerSpacing = ImVec2(6.0f, 4.0f);
		style.IndentSpacing = 18.0f;
		style.ScrollbarSize = 14.0f;
		style.GrabMinSize = 10.0f;

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			style.WindowRounding = 0.0f;

		// Base
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.08f, 0.09f, 0.11f, 1.0f };
		colors[ImGuiCol_ChildBg] = ImVec4{ 0.10f, 0.11f, 0.14f, 1.0f };
		colors[ImGuiCol_PopupBg] = ImVec4{ 0.11f, 0.12f, 0.15f, 1.0f };

		// Text
		colors[ImGuiCol_Text] = ImVec4{ 0.84f, 0.87f, 0.91f, 1.0f };
		colors[ImGuiCol_TextDisabled] = ImVec4{ 0.50f, 0.55f, 0.62f, 1.0f };

		// Borders
		colors[ImGuiCol_Border] = ImVec4{ 0.24f, 0.28f, 0.34f, 0.75f };
		colors[ImGuiCol_BorderShadow] = ImVec4{ 0.00f, 0.00f, 0.00f, 0.00f };

		// Window / title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.06f, 0.07f, 0.09f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.10f, 0.12f, 0.15f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.06f, 0.07f, 0.09f, 1.0f };
		colors[ImGuiCol_MenuBarBg] = ImVec4{ 0.09f, 0.10f, 0.12f, 1.0f };

		// Frames
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.13f, 0.15f, 0.18f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.18f, 0.21f, 0.26f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.23f, 0.28f, 0.34f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.14f, 0.17f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.20f, 0.25f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.25f, 0.31f, 0.39f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.14f, 0.17f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.21f, 0.26f, 0.33f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.26f, 0.33f, 0.41f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.10f, 0.12f, 0.15f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.18f, 0.22f, 0.28f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.15f, 0.19f, 0.24f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.08f, 0.09f, 0.11f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.12f, 0.15f, 0.19f, 1.0f };

		// Accent
		colors[ImGuiCol_CheckMark] = ImVec4{ 0.46f, 0.62f, 0.84f, 1.0f };
		colors[ImGuiCol_SliderGrab] = ImVec4{ 0.35f, 0.48f, 0.66f, 1.0f };
		colors[ImGuiCol_SliderGrabActive] = ImVec4{ 0.46f, 0.62f, 0.84f, 1.0f };

		// Separators
		colors[ImGuiCol_Separator] = ImVec4{ 0.20f, 0.23f, 0.28f, 1.0f };
		colors[ImGuiCol_SeparatorHovered] = ImVec4{ 0.31f, 0.42f, 0.56f, 1.0f };
		colors[ImGuiCol_SeparatorActive] = ImVec4{ 0.40f, 0.53f, 0.70f, 1.0f };

		// Scrollbar
		colors[ImGuiCol_ScrollbarBg] = ImVec4{ 0.07f, 0.08f, 0.10f, 1.0f };
		colors[ImGuiCol_ScrollbarGrab] = ImVec4{ 0.16f, 0.19f, 0.23f, 1.0f };
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4{ 0.22f, 0.27f, 0.33f, 1.0f };
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4{ 0.28f, 0.34f, 0.42f, 1.0f };

		// Utility
		colors[ImGuiCol_ResizeGrip] = ImVec4{ 0.20f, 0.23f, 0.28f, 0.20f };
		colors[ImGuiCol_ResizeGripHovered] = ImVec4{ 0.31f, 0.42f, 0.56f, 0.60f };
		colors[ImGuiCol_ResizeGripActive] = ImVec4{ 0.40f, 0.53f, 0.70f, 0.85f };
		colors[ImGuiCol_DockingPreview] = ImVec4{ 0.35f, 0.48f, 0.66f, 0.55f };
		colors[ImGuiCol_DockingEmptyBg] = ImVec4{ 0.07f, 0.08f, 0.10f, 1.0f };
		colors[ImGuiCol_TextSelectedBg] = ImVec4{ 0.29f, 0.39f, 0.52f, 0.35f };
		colors[ImGuiCol_NavHighlight] = ImVec4{ 0.40f, 0.53f, 0.70f, 0.75f };
		colors[ImGuiCol_TableHeaderBg] = ImVec4{ 0.11f, 0.13f, 0.16f, 1.0f };
		colors[ImGuiCol_TableBorderStrong] = ImVec4{ 0.22f, 0.25f, 0.30f, 1.0f };
		colors[ImGuiCol_TableBorderLight] = ImVec4{ 0.16f, 0.19f, 0.23f, 1.0f };
		colors[ImGuiCol_TableRowBgAlt] = ImVec4{ 0.09f, 0.10f, 0.12f, 0.35f };
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4{ 0.02f, 0.03f, 0.05f, 0.45f };
	}
}
