#pragma once

#include "Cloud/Core.h"
#include "Cloud/Events/Event.h"

namespace Cloud {
	class Layer {
	public:
		Layer(const std::string& layerName = "New Layer") : layerName(layerName) {}

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate(const float deltaTime, const float time) {}
		virtual void onImGuiRender() {}

		virtual void onEvent(Event& event) {}

		inline const std::string& getName() const { return layerName; }

		virtual ~Layer() {}
	protected:
		std::string layerName;
	};

}