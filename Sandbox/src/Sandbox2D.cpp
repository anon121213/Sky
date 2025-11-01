#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include "glm/gtc/type_ptr.hpp"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.f)
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Sky::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Sky::Timestep ts)
{
	//  Update
	m_CameraController.OnUpdate(ts);

	// Render
	Sky::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Sky::RenderCommand::Clear();

	Sky::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Sky::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Sky::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Sky::Renderer2D::DrawQuad({ 0.2f, 0.5f, 0.5f }, { 10.5f, 10.5f }, m_CheckerboardTexture);
	Sky::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Sky::Event& event)
{
	m_CameraController.OnEvent(event);
}
