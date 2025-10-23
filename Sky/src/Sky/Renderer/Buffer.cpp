#include "skypch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Sky {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) 
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:     SKY_CORE_ASSERT(false, "REndererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::OpneGL:   return new OpenGLVertexBuffer(vertices, size);
		}

		SKY_CORE_ASSERT(false, "Unknown RenderAPI!")
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:     SKY_CORE_ASSERT(false, "REndererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::OpneGL:   return new OpenGLIndexBuffer(indices, size);
		}

		SKY_CORE_ASSERT(false, "Unknown RenderAPI!")
			return nullptr;
	}
}