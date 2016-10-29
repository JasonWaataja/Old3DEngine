#pragma once
#include <GL/glew.h>
class Model
{
	float* vertexData;
	float* texCoordData;
	float* normalData;
	GLuint vertexVbo;
	GLuint texCoordVbo;
	GLuint normalVbo;

	unsigned int* indexData;
	GLuint indexVbo;
	
	GLuint vao;
	unsigned int amountOfVertices;
public:
	Model(unsigned int amountOfVertices);
	~Model();

	void initOpenGLData();
	void setOpenGLPointers();

	void setupOpenGL();

	unsigned int getAmountOfVertices();
	void setAmountOfVertices(unsigned int amountOfVertices);

	GLuint getVao();

	void setVertexDataPointer(float* vertexData);
	void copyVertexData(float* vertexData, unsigned int amountOfVertices);
	void setTexCoordDataPointer(float* texCoordData);
	void copyTexCoordData(float* texCoordData, unsigned int amountOfVertices);
	void setNormalDataPointer(float* normalData);
	void copyNormalData(float* normalData, unsigned int amountOfVertices);

	void setAllPointers(float* vertexData, float* texCoordData, float* normalData, unsigned int* indexData);
	void copyAllData(float* vertexData, float* texCoordData, float* normalData, unsigned int* indexData, unsigned int amountOfVertices);


	void setIndexDataPointer(unsigned int* indexData);
	void copyIndexData(unsigned int* indexData, unsigned int amountOfVertices);

	float* getVertexPointer();
	float* getTexCoordPointer();
	float* getNormalPointer();

	void updateVertexOpenGLData();
	void updateTexCoordOpenGLData();
	void updateNormalOpenGLData();
	void updateIndexOpenGLData();

	void updateAllOpenGLData();
	
	void putVertexData();
	void putTexCoordData();
	void putNormalData();
	void putIndexData();

	void putAllData();

	void draw();
};

