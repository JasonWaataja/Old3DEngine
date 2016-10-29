#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

Camera::Camera(vec3 position, vec3 lookDirection, vec3 upVector, float fovDegrees, float aspectRatio, float zNear, float zFar)
{
	setPosition(position);
	setDirection(lookDirection);
	setUpVector(upVector);
	setFovDegrees(fovDegrees);
	setAspectRatio(aspectRatio);
	setZNear(zNear);
	setZFar(zFar);
}


Camera::~Camera()
{
}

void Camera::setPosition(vec3 position)
{
	this->position = position;
}
void Camera::movePosition(vec3 transformation)
{
	setPosition(this->position + transformation);
}
vec3 Camera::getPosition()
{
	return position;
}

void Camera::setDirection(vec3 direction)
{
	this->lookDirection = direction;
}
void Camera::lookAt(vec3 point)
{
	lookDirection = normalize(point - position);
}
vec3 Camera::getLookDirection()
{
	return lookDirection;
}

void Camera::setUpVector(vec3 upVector)
{
	this->upVector = upVector;
}
vec3 Camera::getUpVector()
{
	return upVector;
}

void Camera::setFovDegrees(float fovDegrees)
{
	this->fovDegrees = fovDegrees;
}
float Camera::getFovDegrees()
{
	return fovDegrees;
}

void Camera::setAspectRatio(float aspectRatio)
{
	this->aspectRatio = aspectRatio;
}
float Camera::getAspectRatio()
{
	return aspectRatio;
}

void Camera::setZNear(float zNear)
{
	this->zNear = zNear;
}
float Camera::getZNear()
{
	return zNear;
}

void Camera::setZFar(float zFar)
{
	this->zFar = zFar;
}
float Camera::getZFar()
{
	return zFar;
}

mat4 Camera::getProjectionMatrix()
{
	mat4 projectionMatrix = glm::perspective(fovDegrees, aspectRatio, zNear, zFar);
	return projectionMatrix;
}
mat4 Camera::getViewMatrix()
{
	mat4 viewMatrix = glm::lookAt(position, position + lookDirection, upVector);
	return viewMatrix;
}
mat4 Camera::getCombinedMatrix()
{
	mat4 combinedMatrix = getProjectionMatrix() * getViewMatrix();
	return combinedMatrix;
}

void Camera::lookRight(float angleDegrees)
{
	mat4 rotator = rotate(angleDegrees, -upVector);
	vec4 newLookDirection = (rotator * vec4(lookDirection, 0));
	lookDirection = vec3(newLookDirection.x, newLookDirection.y, newLookDirection.z);
}
void Camera::lookLeft(float angleDegrees)
{
	mat4 rotator = rotate(angleDegrees, upVector);
	vec4 newLookDirection = (rotator * vec4(lookDirection, 0));
	lookDirection = vec3(newLookDirection.x, newLookDirection.y, newLookDirection.z);
}
void Camera::lookUp(float angleDegrees)
{
	vec3 rotationAxis = cross(upVector, lookDirection);
	mat4 rotator = rotate(angleDegrees, -rotationAxis);
	vec4 newLookDirection = (rotator * vec4(lookDirection, 0));
	vec4 newUpVector = (rotator * vec4(upVector, 0));
	lookDirection = vec3(newLookDirection.x, newLookDirection.y, newLookDirection.z);
	upVector = vec3(newUpVector.x, newUpVector.y, newUpVector.z);
}
void Camera::lookDown(float angleDegrees)
{
	vec3 rotationAxis = cross(upVector, lookDirection);
	mat4 rotator = rotate(-angleDegrees, -rotationAxis);
	vec4 newLookDirection = (rotator * vec4(lookDirection, 0));
	vec4 newUpVector = (rotator * vec4(upVector, 0));
	lookDirection = vec3(newLookDirection.x, newLookDirection.y, newLookDirection.z);
	upVector = vec3(newUpVector.x, newUpVector.y, newUpVector.z);
}

void Camera::moveForward(float distance)
{
	vec3 offset = distance * normalize(lookDirection);
	movePosition(offset);
}

void Camera::moveBackward(float distance)
{
	vec3 offset = distance * -normalize(lookDirection);
	movePosition(offset);
}

void Camera::moveRight(float distance)
{
	vec3 offset = distance * normalize(cross(lookDirection, upVector));
	movePosition(offset);
}

void Camera::moveLeft(float distance)
{
	vec3 offset = distance * -normalize(cross(lookDirection, upVector));
	movePosition(offset);
}

void Camera::moveUp(float distance)
{
	vec3 offset = distance * normalize(upVector);
	movePosition(offset);
}

void Camera::moveDown(float distance)
{
	vec3 offset = distance * -normalize(upVector);
	movePosition(offset);
}

void Camera::rotateClockwise(float angleDegrees)
{
	mat4 rotator = rotate(angleDegrees, lookDirection);
	vec4 newUpVector = (rotator * vec4(upVector, 0));
	upVector = vec3(newUpVector.x, newUpVector.y, newUpVector.z);
}

void Camera::rotateCounterclockwise(float angleDegrees)
{
	mat4 rotator = rotate(-angleDegrees, lookDirection);
	vec4 newUpVector = (rotator * vec4(upVector, 0));
	upVector = vec3(newUpVector.x, newUpVector.y, newUpVector.z);
}