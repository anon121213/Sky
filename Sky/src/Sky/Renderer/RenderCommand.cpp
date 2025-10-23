#include "skypch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Sky {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}