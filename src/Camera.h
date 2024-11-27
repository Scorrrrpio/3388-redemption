#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
	private:
		float radius;
		float theta;  // Orbit
		float phi;  // Elevation

	public:
		Camera(float initRadius, float initTheta, float initPhi)
			: radius(initRadius), theta(initTheta), phi(initPhi) {}
		void update(float deltaX, float deltaY, float deltaR);
		glm::mat4 getViewMatrix() const;
};

#endif
