#include <Sky.h>

#include "imgui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"

#include "glm/gtc/type_ptr.hpp"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLTexture.h"

class ExampleLayer : public Sky::Layer 
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_SquareColor(0.8f, 0.2f, 0.3f, 1.0f)
	{
		m_VertexArray.reset(Sky::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.0f, 1.0f
		};

		Sky::Ref<Sky::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Sky::VertexBuffer::Create(vertices, sizeof(vertices)));
		Sky::BufferLayout layout = {
			{Sky::ShaderDataType::Float3, "a_Position"},
			{Sky::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Sky::Ref<Sky::IndexBuffer> indexBuffer;
		indexBuffer.reset(Sky::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Sky::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};

		Sky::Ref<Sky::VertexBuffer> squareVB;
		squareVB.reset(Sky::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Sky::ShaderDataType::Float3, "a_Position" },
			{ Sky::ShaderDataType::Float2, "a_TexCoord" },
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Sky::Ref<Sky::IndexBuffer> squareIB;
		squareIB.reset(Sky::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
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

		m_Shader.reset(Sky::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec4 u_Color;

			void main()
			{
				color = u_Color;
			}
		)";

		m_FlatColorShader.reset(Sky::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

		std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;			

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader.reset(Sky::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

		m_Texture = Sky::Texture2D::Create("assets/textures/Checkerboard.png");

		std::dynamic_pointer_cast<Sky::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Sky::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Sky::Timestep ts) override
	{
		if (Sky::Input::IsKeyPressed(SKY_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Sky::Input::IsKeyPressed(SKY_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Sky::Input::IsKeyPressed(SKY_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Sky::Input::IsKeyPressed(SKY_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Sky::Input::IsKeyPressed(SKY_KEY_A))
			m_CameraRotation += m_CameraMoveSpeed * ts;
		else if (Sky::Input::IsKeyPressed(SKY_KEY_D))
			m_CameraRotation -= m_CameraMoveSpeed * ts;

		Sky::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Sky::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Sky::Renderer::BeginScene(m_Camera);
		
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Sky::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Sky::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++) 
			{
				glm::vec3 pos(x * 0.11f, y * 0.16f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Sky::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		Sky::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

		// Triangle
		// Sky::Renderer::Submit(m_Shader, m_VertexArray);

		Sky::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

		static char texturePath[256] = "assets/textures/Checkerboard.jpg";

		ImGui::InputText("Texture Path", texturePath, IM_ARRAYSIZE(texturePath));
		if (ImGui::Button("Load Texture"))
		{
			m_Texture = Sky::Texture2D::Create(texturePath);
		}


		ImGui::End();
	}


	void OnEvent(Sky::Event& event) override 
	{
	}

private:
	Sky::Ref<Sky::Shader> m_Shader;
	Sky::Ref<Sky::VertexArray> m_VertexArray;

	Sky::Ref<Sky::Shader> m_FlatColorShader, m_TextureShader;
	Sky::Ref<Sky::VertexArray> m_SquareVA;

	Sky::Ref<Sky::Texture2D> m_Texture;

	Sky::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	glm::vec4 m_SquareColor;

	float m_CameraRotation = 0.0f;
	float m_CameraMoveSpeed = 10.0f;

	glm::vec3 m_SquarePosition;
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