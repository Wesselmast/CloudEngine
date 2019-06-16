#pragma once

#include "Cloud/Layer.h"

#include "Cloud/Events/MouseEvent.h"
#include "Cloud/Events/ApplicationEvent.h"
#include "Cloud/Events/KeyEvent.h"

namespace Cloud {
	class CLOUD_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();

		void onAttach();
		void onDetach();
		void onUpdate();
		void onEvent(Event& event);
	
		~ImGuiLayer();
	private:
		float time = 0;
	};
}