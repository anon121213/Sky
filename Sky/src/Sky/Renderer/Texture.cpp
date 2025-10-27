#include "skypch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Sky {

	Ref<Texture2D> Texture2D::Create(const std::string& path) 
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:     SKY_CORE_ASSERT(false, "REndererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLTexture2D>(path);
		}

		SKY_CORE_ASSERT(false, "Unknown RenderAPI!")
			return nullptr;
	}

}