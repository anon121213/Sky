#pragma once

#include "Sky.h"
#include "Sky/ECS/World.h"

class Sandbox2D : public Sky::Layer {
public:
	Sandbox2D();
	~Sandbox2D() override = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Sky::Timestep ts) override;
	void OnImGuiRender() override;
	void OnEvent(Sky::Event& event) override;

private:
	Sky::OrthographicCameraController m_CameraController;

	Sky::Ref<Sky::World> m_World;

	// Temp
	Sky::Ref<Sky::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_RedSquareColor = { 0.8f, 0.2f, 0.3f, 1.0f };
	glm::vec4 m_BuleSquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
