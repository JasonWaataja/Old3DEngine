#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
class Camera
{
	vec3 position;
	vec3 lookDirection;
	vec3 upVector;
	float fovDegrees;
	float aspectRatio;
	float zNear;
	float zFar;
public:
	Camera(vec3 position, vec3 lookDirection, vec3 upVector, float fovDegrees, float aspectRatio, float zNear, float zFar);
	~Camera();

	void setPosition(vec3 position);
	void movePosition(vec3 transformation);
	vec3 getPosition();

	void setDirection(vec3 direction);
	void lookAt(vec3 point);
	vec3 getLookDirection();

	void setUpVector(vec3 upVector);
	vec3 getUpVector();

	void setFovDegrees(float fovDegrees);
	float getFovDegrees();

	void setAspectRatio(float aspectRatio);
	float getAspectRatio();

	void setZNear(float zNear);
	float getZNear();

	void setZFar(float zFar);
	float getZFar();

	mat4 getProjectionMatrix();
	mat4 getViewMatrix();
	mat4 getCombinedMatrix();

	void lookRight(float angleDegrees);
	void lookLeft(float angleDegrees);
	void lookUp(float angleDegrees);
	void lookDown(float angleDegrees);

	void moveForward(float distance);
	void moveBackward(float distance);
	void moveRight(float distance);
	void moveLeft(float distance);
	void moveUp(float distance);
	void moveDown(float distance);

	void rotateClockwise(float angleDegrees);
	void rotateCounterclockwise(float angleDegrees);
};

