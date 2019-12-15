#include "cldpch.h"
#include "OrthoCamera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Cloud {
	OrthoCamera::OrthoCamera(float left, float right, float bottom, float top) :
		projectionMatrix(glm::ortho(left, right, bottom, top)), viewMatrix(glm::mat4(1.0f)), position(glm::vec3(0, 0, 0)), rotation(0) {
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}

	void OrthoCamera::recalculateViewMatrix() {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0), glm::radians(rotation), glm::vec3(0, 0, 1));
		viewMatrix = glm::inverse(transform);
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}
}
