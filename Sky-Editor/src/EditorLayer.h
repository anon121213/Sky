#pragma once

#include "Sky.h"

namespace Sky
{
	class EditorLayer : public Layer 
	{
	public:
		EditorLayer();
		~EditorLayer() override = default;

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		void OnImGuiRender() override;
		void OnEvent(Event& event) override;

	private:
		OrthographicCameraController m_CameraController;

		// Temp
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;

		Ref<Texture2D> m_CheckerboardTexture;
		Ref<Texture2D> m_SpriteSheet;
		Ref<SubTexture2D> m_TextureInSheet;

		Ref<FrameBuffer> m_FrameBuffer;

		glm::vec4 m_RedSquareColor = { 0.8f, 0.2f, 0.3f, 1.0f };
		glm::vec4 m_BlueSquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	};
}