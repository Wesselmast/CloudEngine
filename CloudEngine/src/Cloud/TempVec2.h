#pragma once

namespace Cloud {
	class vec2 {
	public:
		vec2() {}
		vec2(float x, float y) {
			this->x = x;
			this->y = y;
		}
	public:
		float x;
		float y;
	};
}