#pragma once

#include "Cloud/Layer.h"

#include "Cloud/Events/MouseEvent.h"
#include "Cloud/Events/ApplicationEvent.h"
#include "Cloud/Events/KeyEvent.h"

namespace Cloud {
	class  ImGuiLayer : public Layer {
	public:
		ImGuiLayer();

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onImGuiRender() override;

		void begin();
		void end();
		~ImGuiLayer();
	private:
		float time = 0;
	};
}