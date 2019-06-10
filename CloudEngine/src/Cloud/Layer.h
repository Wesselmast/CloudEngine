#pragma once

#include "Cloud/Core.h"
#include "Cloud/Events/Event.h"


namespace Cloud {

	class CLOUD_API Layer {
	public:
		Layer(const std::string& layerName = "New Layer") : layerName(layerName) {}

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onEvent(Event& event) {}

		inline const std::string& getName() const { return layerName; }

		virtual ~Layer() {}
	protected:
		std::string layerName;
	};

}