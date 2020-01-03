#include "cldpch.h"
#include "PerspectiveCamera.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.inl"

namespace Cloud {
	PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float zNear, float zFar) :
		projectionMatrix(glm::perspective(fov, aspect, zNear, zFar)), viewMatrix(glm::mat4(1.0f)), position(glm::vec3(0, 0, 0)), rotation(0) {
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}

	void PerspectiveCamera::recalculateViewMatrix() {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::eulerAngleYXZ(rotation.x, rotation.y, rotation.z);// glm::mat4(1.0), glm::radians(rotation), glm::vec3(0, 1, 0));
		viewMatrix = glm::inverse(transform);
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}
}
