#include <Sky.h>

#include "imgui/imgui.h"

class ExampleLayer : public Sky::Layer 
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Sky::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.0f, 1.0f
		};

		std::shared_ptr<Sky::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Sky::VertexBuffer::Create(vertices, sizeof(vertices)));
		Sky::BufferLayout layout = {
			{Sky::ShaderDataType::Float3, "a_Position"},
			{Sky::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Sky::IndexBuffer> indexBuffer;
		indexBuffer.reset(Sky::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Sky::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};

		std::shared_ptr<Sky::VertexBuffer> squareVB;
		squareVB.reset(Sky::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{Sky::ShaderDataType::Float3, "a_Position"},
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Sky::IndexBuffer> squareIB;
		squareIB.reset(Sky::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;	
			}
		)";

		m_Shader.reset(new Sky::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec3 v_Color;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Sky::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate() override 
	{
		Sky::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Sky::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);

		Sky::Renderer::BeginScene(m_Camera);

		Sky::Renderer::Submit(m_BlueShader, m_SquareVA);
		Sky::Renderer::Submit(m_Shader, m_VertexArray);

		Sky::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override 
	{
	}

	void OnEvent(Sky::Event& event) override 
	{
	}

private:
	std::shared_ptr<Sky::Shader> m_Shader;
	std::shared_ptr<Sky::VertexArray> m_VertexArray;

	std::shared_ptr<Sky::Shader> m_BlueShader;
	std::shared_ptr<Sky::VertexArray> m_SquareVA;

	Sky::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 0.1;
};

class Sandbox : public Sky::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};


Sky::Application* Sky::CreateApplication()
{
	return new Sandbox();
}