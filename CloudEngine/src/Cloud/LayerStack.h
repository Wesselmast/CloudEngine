#pragma once

#include "Cloud/Core.h"

#include "Layer.h"

#include <vector>

namespace Cloud {
	typedef std::vector<Layer*>::iterator LayerIterator;

	class  LayerStack {
	public:
		LayerStack() {}

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

		//popping layers/overlays does not delete their pointers, you can later push them back in
		void popLayer(Layer* layer);
		void popOverlay(Layer* overlay);

		LayerIterator begin() { return layers.begin(); }
		LayerIterator end() { return layers.end(); }
		
		~LayerStack();
	private:
		std::vector<Layer*> layers;
		unsigned int index = 0;
	};
}