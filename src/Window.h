#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Window
{
	int width;
	int height;
	int dx;
	int dy;
	int lastX;
	int lastY;
	double mouseX;
	double mouseY;
	GLFWwindow* window;
	void setCursorToCenter();
	void updateCursorPosition();
	bool mouseGrabbed;
	double delta;
	double lastTime;
public:
	bool isPressed(int key);
	void initialize();
	int getWidth();
	int getHeight();
	int getDx();
	int getDy();
	int getX();
	int getY();
	float getDelta();
	float getTime();
	bool getMouseGrabbed();
	void setMouseGrabbed(bool mouseGrabbed);
	GLFWwindow* getWindow();
	void terminate();
	int shouldClose();
	void update();
	Window();
	~Window();
};