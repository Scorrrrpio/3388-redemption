#include "Camera.h"


void Camera::update(float deltaX, float deltaY, float deltaR) {
	// Speed
	float camSpeed = 0.15f;
	float orbitSpeed = 0.05f;

	// Move
	theta += deltaX * orbitSpeed;
	phi -= deltaY * orbitSpeed;
	radius += deltaR * camSpeed;

	// Limit radius
	if (radius < 0.01f)
		radius = 0.01f;

	// Clamp elevation
	if (phi < 0.0001f)
		phi = 0.0001f;
	if (phi > 3.1414f)
		phi = 3.1414f;
}


glm::mat4 Camera::getViewMatrix() const {
	// Convert spherical coordinates to Cartesian
	float x = radius * std::cos(theta) * std::sin(phi);
	float y = radius * std::cos(phi);
	float z = radius * std::sin(theta) * std::sin(phi);

	// Generate view matrix
	glm::vec3 eye = glm::vec3(x, y, z);
	glm::vec3 centre = {0.0f, 0.0f, 0.0f};
	glm::vec3 up = {0.0f, 1.0f, 0.0f};

	return glm::lookAt(eye, centre, up);
}

glm::vec3 Camera::getCartesian() const {
	// Convert spherical coordinates to Cartesian
	float x = radius * std::cos(theta) * std::sin(phi);
	float y = radius * std::cos(phi);
	float z = radius * std::sin(theta) * std::sin(phi);

	// Generate view matrix
	return glm::vec3(x, y, z);
}
