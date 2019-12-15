#include "cldpch.h"
#include "RenderCommand.h"\

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Cloud {

	RendererAPI* RenderCommand::api = new OpenGLRendererAPI;
	
}