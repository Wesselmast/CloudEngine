#pragma once
#include "cldpch.h"

#include "glm/glm.hpp"

namespace Cloud {
	class Input {
	public:
		inline static bool keyPressed(int keycode) { return instance->isKeyPressed(keycode); }
		inline static bool mousePressed(int button) { return instance->isMousePressed(button); }
		inline static glm::vec2 mousePos() { return instance->getMousePos(); }
		inline static bool mouseX() { return instance->getMouseX(); }
		inline static bool mouseY() { return instance->getMouseY(); }
	protected:
		virtual bool isKeyPressed(int keycode) = 0;
		virtual bool isMousePressed(int button) = 0;
		virtual glm::vec2 getMousePos() = 0;
		virtual float getMouseX() = 0;
		virtual float getMouseY() = 0;
	private:
		static Input* instance;
	};
}
