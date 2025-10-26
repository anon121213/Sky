#include "skypch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Sky {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:     SKY_CORE_ASSERT(false, "REndererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:   return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		SKY_CORE_ASSERT(false, "Unknown RenderAPI!")
		return nullptr;
	}

}