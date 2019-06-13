#pragma once

#include "Cloud/Layer.h"

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