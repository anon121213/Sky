#pragma once

#include "Sky.h"

class Sandbox2D : public Sky::Layer {
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Sky::Timestep ts) override;
	void OnImGuiRender() override;
	void OnEvent(Sky::Event& event) override;

private:
	Sky::OrthographicCameraController m_CameraController;

	// Temp
	Sky::Ref<Sky::VertexArray> m_SquareVA;
	Sky::Ref<Sky::Shader> m_FlatColorShader;

	Sky::Ref<Sky::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};