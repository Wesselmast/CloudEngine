#pragma once
#include "Cloud/Input.h" 


namespace Cloud {

	class WindowsInput : public Input {
	protected:
		virtual bool isKeyPressed(int keycode) override;
		virtual bool isMousePressed(int button) override;
		virtual vec2 getMousePos() override;
		virtual float getMouseX() override;
		virtual float getMouseY() override;
	};
}

