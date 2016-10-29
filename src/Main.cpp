#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <functional>

#include "lodepng.h"
#include "Window.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Model.h"
using namespace std;
using namespace glm;
int main(int argc, char** argv)
{
	/*Window* window = new Window();
window->initialize();
glEnable(GL_DEPTH_TEST);
glDepthMask(GL_TRUE);
glDepthFunc(GL_LEQUAL);
glDepthRange(0.0f, 1.0f);	GLuint vao, vbo;
glGenVertexArrays(1, &vao);
glGenBuffers(1, &vbo);
glBindVertexArray(vao);
float data[] = {
0, 0, -.5f,
1, 0, -.5f,
0, 1, -.5f };
glBindBuffer(GL_ARRAY_BUFFER, vbo);
glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, vbo);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
while (!window->shouldClose() && glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS)
{
glBindVertexArray(vao);
glDrawArrays(GL_TRIANGLES, 0, 3);
window->update();
}
window->terminate();*/

	Window* myWindow = new Window();
	myWindow->initialize();
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
	ShaderProgram* myProgram;
	myProgram = new ShaderProgram("OneLightTest.vert", "OneLightTest.frag");
	myProgram->addUniform("modelMatrix");
	myProgram->addUniform("viewMatrix");
	myProgram->addUniform("projectionMatrix");
	myProgram->addUniform("modelViewMatrix");
	myProgram->addUniform("normalMatrix");
	myProgram->use();
	Camera* camera;
	camera = new Camera(vec3(0, 0, 0), vec3(0, 0, 1), vec3(0, 1, 0), 90, 16.0f / 9.0f, .1f, 100.0f);
	mat4 modelMatrix;
	mat4 viewMatrix = camera->getViewMatrix();
	mat4 projectionMatrix = camera->getProjectionMatrix();
	mat4 modelViewMatrix = viewMatrix * viewMatrix;
	mat4 normalMatrix = inverse(transpose(modelViewMatrix));
	//glUniformMatrix4fv(myProgram->getUniform("matrixToUse"), 1, GL_FALSE, value_ptr(matrixToUse));
	glUniformMatrix4fv(myProgram->getUniform("modelMatrix"), 1, GL_FALSE, value_ptr(modelMatrix));
	glUniformMatrix4fv(myProgram->getUniform("viewMatrix"), 1, GL_FALSE, value_ptr(viewMatrix));
	glUniformMatrix4fv(myProgram->getUniform("projectionMatrix"), 1, GL_FALSE, value_ptr(projectionMatrix));
	glUniformMatrix4fv(myProgram->getUniform("modelViewMatrix"), 1, GL_FALSE, value_ptr(modelViewMatrix));
	glUniformMatrix4fv(myProgram->getUniform("normalMatrix"), 1, GL_FALSE, value_ptr(normalMatrix));

	myProgram->use();

	Model* model;
	model = new Model(3);
	float vd[] = {
		-1, -1, 2,
			-1, 1, 2,
			1, 1, 2};
	float td[] = {
		0, 0,
			0, 1,
			1, 1, };
	float nd[] = 
	{
		-1, 0, 0,
			0, 1, 0,
			1, 0, 0};
	unsigned int id[] = 
	{
		0, 1, 2};
	model->setVertexDataPointer(vd);
	model->setTexCoordDataPointer(td);
	model->setNormalDataPointer(nd);
	model->setIndexDataPointer(id);
	model->setupOpenGL();

	unsigned int indexData[] = {
		0, 1, 2,
		0, 3, 2,

		4, 5, 6,
		4, 7, 6,

		0, 1, 5,
		4, 5, 0,

		1, 2, 6,
		5, 6, 1,

		2, 3, 7,
		6, 7, 2,

		3, 0, 4,
		7, 4, 3
	};
	float vertexData[] =
	{
		-1, -1, 3,
		1, -1, 3,
		1, 1, 3,
		-1, 1, 3,
		-1, -1, 5,
		1, -1, 5,
		1, 1, 5,
		-1, 1, 5 };
	float texCoordData[] = {
		0, 0,
		1, 0,
		1, 1,
		0, 1,
		1, 1,
		0, 1,
		0, 0,
		1, 0 };
	float root = 1.0f / 1.73f;
	float normalData[] = {
		-root, -root, -root,
		root, -root, -root,
		root, root, -root,
		-root, root, -root,
		-root, -root, root,
		root, -root, root,
		root, root, root,
		-root, root, root,
	};
	GLuint vao;
	glGenVertexArrays(1, &vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	GLuint tbo;
	glGenBuffers(1, &tbo);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoordData), texCoordData, GL_STATIC_DRAW);
	GLuint nbo;
	glGenBuffers(1, &nbo);
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normalData), normalData, GL_STATIC_DRAW);
	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ARRAY_BUFFER, ibo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	Model* cubeModel;
	cubeModel = new Model(36);
	/*cubeModel->setVertexDataPointer(vertexData);
	cubeModel->setTexCoordDataPointer(texCoordData);
	cubeModel->setNormalDataPointer(normalData);
	cubeModel->setIndexDataPointer(indexData);*/
	cubeModel->copyAllData(vertexData, texCoordData, normalData, indexData, 36);
	cubeModel->setupOpenGL();

	
	//float elapsedTime = 0;
	//float frames = 0;

	vector<unsigned char> image;
	unsigned int width, height;
	unsigned int error = lodepng::decode(image, width, height, "crate.png");
	GLuint crateTexture;
	glGenTextures(1, &crateTexture);
	glBindTexture(GL_TEXTURE_2D, crateTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	while (!myWindow->shouldClose() && !glfwGetKey(myWindow->getWindow(), GLFW_KEY_ESCAPE))
	{
		/*elapsedTime += myWindow->getDelta();
		frames++;
		if (elapsedTime > 1)
		{
			cout << frames << endl;
			elapsedTime = 0;
			frames = 0;
		}*/
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//camera->lookUp(.1f);
		int dx = myWindow->getDx();
		int dy = myWindow->getDy();
		camera->lookRight(dx * .5f);
		camera->lookDown(dy * .5f);
		//camera->lookRight(dx * .5f);

		float delta = myWindow->getDelta();

		if (glfwGetKey(myWindow->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
		{
			camera->moveForward(delta * 3);
		}
		if (glfwGetKey(myWindow->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
		{
			camera->moveBackward(delta * 3);
		}
		if (glfwGetKey(myWindow->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
		{
			camera->moveLeft(delta * 3);
		}
		if (glfwGetKey(myWindow->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
		{
			camera->moveRight(delta * 3);
		}
		if (glfwGetKey(myWindow->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			camera->moveUp(delta * 3);
		}
		if (glfwGetKey(myWindow->getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			camera->moveDown(delta * 3);
		}
		if (glfwGetKey(myWindow->getWindow(), GLFW_KEY_Q) == GLFW_PRESS)
		{
			camera->rotateCounterclockwise(delta * 500);
		}
		if (glfwGetKey(myWindow->getWindow(), GLFW_KEY_E) == GLFW_PRESS)
		{
			camera->rotateClockwise(delta * 500);
		}

		if (myWindow->isPressed(GLFW_KEY_G))
		{
			if (myWindow->getMouseGrabbed())
			{
				myWindow->setMouseGrabbed(false);
			}
			else
			{
				myWindow->setMouseGrabbed(true);
			}
		}

		if (myWindow->isPressed(GLFW_KEY_P))
		{
			int input;
			cin >> input;
		}

		glUseProgram(myProgram->getProgram());
		/*rotator = glm::rotate(0.0f, vec3(1, 0, 0));
		//mat4 projectionMatrix = perspective(90.0f, 16.0f / 9.0f, .1f, 100.0f);
		//mat4 viewMatrix = lookAt(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0));
		//mat4 matrixToUse = projectionMatrix * viewMatrix;
		matrixToUse = camera->getCombinedMatrix() * rotator;

		glUniformMatrix4fv(myProgram->getUniform("matrixToUse"), 1, GL_FALSE, value_ptr(matrixToUse));*/

		viewMatrix = camera->getViewMatrix();
		projectionMatrix = camera->getProjectionMatrix();
		modelViewMatrix = viewMatrix * modelMatrix;
		normalMatrix = inverse(transpose(modelViewMatrix));
		glUniformMatrix4fv(myProgram->getUniform("modelMatrix"), 1, GL_FALSE, value_ptr(modelMatrix));
		glUniformMatrix4fv(myProgram->getUniform("viewMatrix"), 1, GL_FALSE, value_ptr(viewMatrix));
		glUniformMatrix4fv(myProgram->getUniform("projectionMatrix"), 1, GL_FALSE, value_ptr(projectionMatrix));
		glUniformMatrix4fv(myProgram->getUniform("modelViewMatrix"), 1, GL_FALSE, value_ptr(modelViewMatrix));
		glUniformMatrix4fv(myProgram->getUniform("normalMatrix"), 1, GL_FALSE, value_ptr(normalMatrix));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);


		/*glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);*/

		cubeModel->draw();


		model->draw();

		myWindow->update();
	}
	myWindow->terminate();
	//int i;
	//cin >> i;*/

	return 0;
}