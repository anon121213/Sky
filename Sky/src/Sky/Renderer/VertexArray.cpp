#include "skypch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Sky {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:     SKY_CORE_ASSERT(false, "REndererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:   return CreateRef<OpenGLVertexArray>();
		}

		SKY_CORE_ASSERT(false, "Unknown RenderAPI!")
		return nullptr;
	}

}