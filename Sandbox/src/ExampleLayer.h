#pragma once

#include <Sky.h>

class ExampleLayer : public Sky::Layer {
public:
	ExampleLayer();	
	~ExampleLayer() override = default;

	void OnUpdate(Sky::Timestep ts) override;
	void OnImGuiRender() override;
	void OnEvent(Sky::Event& event) override;

private:
	Sky::ShaderLibrary m_ShaderLibrary;
	Sky::Ref<Sky::Shader> m_Shader;
	Sky::Ref<Sky::VertexArray> m_VertexArray;

	Sky::Ref<Sky::Shader> m_FlatColorShader;
	Sky::Ref<Sky::VertexArray> m_SquareVA;

	Sky::Ref<Sky::Texture2D> m_Texture;

	Sky::OrthographicCameraController m_CameraController;
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};