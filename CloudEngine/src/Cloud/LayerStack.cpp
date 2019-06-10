#include "cldpch.h"
#include "LayerStack.h"

namespace Cloud {

	//push layer into end of the stack, but before the overlays
	void LayerStack::pushLayer(Layer* layer) {
		layerIterator = layers.emplace(layerIterator, layer);
	}

	//push overlay into end of the stack, because they should be rendered on top of layers
	void LayerStack::pushOverlay(Layer * overlay) {
		layers.emplace_back(overlay);
	}

	void LayerStack::popLayer(Layer * layer) {
		LayerIterator iterator = std::find(layers.begin(), layers.end(), layer);
		if (iterator != layers.end()) {
			layers.erase(iterator);
			layerIterator--;
		}
	}

	void LayerStack::popOverlay(Layer * overlay) {
		LayerIterator iterator = std::find(layers.begin(), layers.end(), overlay);
		if (iterator != layers.end()) {
			layers.erase(iterator);
		}
	}

	LayerStack::~LayerStack() {
		for (Layer* layer : layers) {
			delete layer;
		}
		layers.clear();
	}
}