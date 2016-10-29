#include "Window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void Window::initialize()
{
	if (!glfwInit()) {
		cout << "Unable to initialize GLFW." << endl;
	}
	glfwWindowHint(GLFW_SAMPLES, 8);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	const GLFWvidmode* mode;
	mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	width = mode->width;
	height = mode->height;
	//window = glfwCreateWindow(width, height, "Hello World", glfwGetPrimaryMonitor(), 0);
	width /= 2;
	height /= 2;
	window = glfwCreateWindow(width, height, "Hello World", 0, 0);

	//window = glfwCreateWindow(1280, 720, "Hello World", 0, 0);
	if (!window)
	{
		cout << "Unable to initialize window." << endl;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		cout << "Unable to initialize GLEW." << endl;
	}
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	setCursorToCenter();
	dx = 0;
	dy = 0;
	updateCursorPosition();
	lastX = mouseX;
	lastY = mouseY;
	mouseGrabbed = true;
	lastTime = glfwGetTime();
	delta = 0;
}

Window::Window()
{
}

float Window::getDelta()
{
	return delta;
}

float Window::getTime()
{
	return glfwGetTime();
}

void Window::updateCursorPosition()
{
	glfwGetCursorPos(window, &mouseX, &mouseY);
}

void Window::setCursorToCenter()
{
	int centerX = width / 2;
	int centerY = height / 2;
	glfwSetCursorPos(window, centerX, centerY);
}

int Window::getWidth()
{
	return width;
}

int Window::getHeight()
{
	return height;
}

int Window::getX()
{
	return mouseX;
}

int Window::getY()
{
	return mouseY;
}

GLFWwindow* Window::getWindow()
{
	return window;
}

void Window::terminate()
{
	glfwTerminate();
}

int Window::shouldClose()
{
	return glfwWindowShouldClose(window);
}

bool Window::isPressed(int key)
{
	return (glfwGetKey(window, key) == GLFW_PRESS);
}

void Window::update()
{
	updateCursorPosition();
	dx = mouseX - lastX;
	dy = mouseY - lastY;
	if (mouseGrabbed)
	{
		setCursorToCenter();
		updateCursorPosition();
	}
	lastX = mouseX;
	lastY = mouseY;
	double currentTime = glfwGetTime();
	delta = currentTime - lastTime;
	lastTime = currentTime;
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool Window::getMouseGrabbed()
{
	return mouseGrabbed;
}

void Window::setMouseGrabbed(bool mouseGrabbed)
{
	this->mouseGrabbed = mouseGrabbed;
	if (mouseGrabbed)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

int Window::getDx()
{
	return dx;
}

int Window::getDy()
{
	return dy;
}

Window::~Window()
{

}