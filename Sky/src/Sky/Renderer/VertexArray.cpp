#include "skypch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Sky {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:     SKY_CORE_ASSERT(false, "REndererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpneGL:   return new OpenGLVertexArray();
		}

		SKY_CORE_ASSERT(false, "Unknown RenderAPI!")
		return nullptr;
	}

}