#pragma once

#include "glm/glm.hpp"

namespace Cloud {
	class OrthoCamera {
	public:
		OrthoCamera(float left, float right, float bottom, float top);
		inline const glm::vec3& getPosition() const {
			return position;
		}
		inline const float& getRotation() const {
			return rotation;
		}
		
		void setPosition(const glm::vec3& position) {
			this->position = position;
			recalculateViewMatrix();
		}
		void setRotation(const float& rotation) {
			this->rotation = rotation;
			recalculateViewMatrix();
		}

		inline const glm::mat4& getProjectMatrix() const {
			return projectionMatrix;
		}
		inline const glm::mat4& getViewMatrix() const {
			return viewMatrix;
		}
		inline const glm::mat4& getViewProjectionMatrix() const {
			return viewProjectionMatrix;
		}
		
	private:
		void recalculateViewMatrix();
	private:
		glm::mat4 viewProjectionMatrix;
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		glm::vec3 position;
		float rotation;
	};
}
