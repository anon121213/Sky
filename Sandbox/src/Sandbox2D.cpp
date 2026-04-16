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
	m_SpriteSheet = Sky::Texture2D::Create("assets/game/textures/TX Tileset Ground.png");
	m_TextureInSheet = Sky::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 7, 6 }, { 128, 128 });
}

void Sandbox2D::OnDetach()
{
	SKY_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(const Sky::Timestep ts)
{
	SKY_PROFILE_FUNCTION();
	//  Update
	m_CameraController.OnUpdate(ts);

	// Render
	Sky::Renderer2D::ResetStats();
	{
		SKY_PROFILE_SCOPE("Renderer Prep");
		m_FrameBuffer->Bind();
		Sky::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Sky::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 40.0f;

		SKY_PROFILE_SCOPE("Renderer Draw");
		Sky::Renderer2D::BeginScene(m_CameraController.GetCamera());

		// Background
		Sky::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 6.0f }, m_CheckerboardTexture, 5.0f);

		// Top row: colored quads
		Sky::Renderer2D::DrawQuad({ -1.2f,  0.5f }, { 0.7f, 0.7f }, m_RedSquareColor);
		Sky::Renderer2D::DrawQuad({  1.2f,  0.5f }, { 0.7f, 0.7f }, m_BlueSquareColor);

		// Center: rotating textured quad
		Sky::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f }, rotation, { 0.9f, 0.9f }, m_CheckerboardTexture, 3.0f);

		// Bottom row: rotated colored / sprite tile / tinted texture
		Sky::Renderer2D::DrawRotatedQuad({ -1.2f, -0.6f }, 45.0f, { 0.6f, 0.6f }, { 0.2f, 0.8f, 0.3f, 1.0f });
		Sky::Renderer2D::DrawQuad(        {  0.0f, -0.6f },        { 0.7f, 0.7f }, m_TextureInSheet);
		Sky::Renderer2D::DrawQuad(        {  1.2f, -0.6f },        { 0.7f, 0.7f }, m_CheckerboardTexture, 2.0f, { 1.0f, 0.75f, 0.2f, 1.0f });

		Sky::Renderer2D::EndScene();
		m_FrameBuffer->Unbind();
	}
}

void Sandbox2D::OnImGuiRender()
{
	SKY_PROFILE_FUNCTION();

    ImGui::Begin("Settings");

    const auto stats = Sky::Renderer2D::GetStats();
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Cells: %u", stats.DrawCalls);
    ImGui::Text("Quads: %u", stats.QuadCount);
    ImGui::Text("Vertices: %u", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %u", stats.GetTotalIndexCount());

    ImGui::ColorEdit4("Red Square Color", glm::value_ptr(m_RedSquareColor));
    ImGui::ColorEdit4("Blue Square Color", glm::value_ptr(m_BlueSquareColor));

    ImGui::End();
}

void Sandbox2D::OnEvent(Sky::Event& event)
{
	m_CameraController.OnEvent(event);
}
