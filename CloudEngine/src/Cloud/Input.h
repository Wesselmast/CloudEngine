#pragma once

#include "cldpch.h"

#include "TempVec2.h"

namespace Cloud {

	class CLOUD_API Input {

	public:
		inline static bool keyPressed(int keycode) { return instance->isKeyPressed(keycode); }
		inline static bool mousePressed(int button) { return instance->isMousePressed(button); }
		inline static vec2 mousePos() { return instance->getMousePos(); }
		inline static bool mouseX() { return instance->getMouseX(); }
		inline static bool mouseY() { return instance->getMouseY(); }

	protected:
		virtual bool isKeyPressed(int keycode) = 0;
		virtual bool isMousePressed(int button) = 0;
		virtual vec2 getMousePos() = 0;
		virtual float getMouseX() = 0;
		virtual float getMouseY() = 0;
	private:
		static Input* instance;
	};
}
