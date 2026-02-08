#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include "glm/gtc/type_ptr.hpp"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.f)
{
}

void Sandbox2D::OnAttach()
{
	SKY_PROFILE_FUNCTION();
	m_CheckerboardTexture = Sky::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	SKY_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Sky::Timestep ts)
{
	SKY_PROFILE_FUNCTION();
	//  Update
	m_CameraController.OnUpdate(ts);

	// Render
	{
		SKY_PROFILE_SCOPE("Renderer Prep");
		Sky::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Sky::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 20.0f;

		SKY_PROFILE_SCOPE("Renderer Draw");
		Sky::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Sky::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, 45.0f, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Sky::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { m_RedSquareColor });
		Sky::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { m_BuleSquareColor });
		Sky::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		Sky::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, rotation, { 1.0f, 1.0f },  m_CheckerboardTexture, 20.0f);
		Sky::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	SKY_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Red Square Color", glm::value_ptr(m_RedSquareColor));
	ImGui::ColorEdit4("Blue Square Color", glm::value_ptr(m_BuleSquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Sky::Event& event)
{
	m_CameraController.OnEvent(event);
}
