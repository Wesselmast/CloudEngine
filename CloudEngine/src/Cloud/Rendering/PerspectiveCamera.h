#pragma once

#include "glm/glm.hpp"

namespace Cloud {
	class PerspectiveCamera {
	public:
		PerspectiveCamera(float fov, float aspect, float zNear, float zFar);
		inline const glm::vec3& getPosition() const {
			return position;
		}
		inline const glm::vec3& getRotation() const {
			return rotation;
		}

		void setPosition(const glm::vec3& position) {
			this->position = position;
			recalculateViewMatrix();
		}
		void setRotation(const glm::vec3& rotation) {
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
		glm::mat4 viewProjectionMatrix{};
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		glm::vec3 position;
		glm::vec3 rotation;
	};
}
