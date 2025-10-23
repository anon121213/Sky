#pragma once

#include "RenderCommand.h"

namespace Sky {
			
	class Renderer
	{
	public:
		static void BeginScene(); 
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& verexArray);
		
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};

}