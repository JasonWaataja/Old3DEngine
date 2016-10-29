#include "Model.h"


Model::Model(unsigned int amountOfVertices)
{
	this->amountOfVertices = amountOfVertices;
	vertexData = new float[amountOfVertices * 3];
	texCoordData = new float[amountOfVertices * 2];
	normalData = new float[amountOfVertices * 3];
	indexData = new unsigned int[amountOfVertices];
}


Model::~Model()
{
	delete[] vertexData;
	delete[] texCoordData;
	delete[] normalData;
	delete[] indexData;
}

unsigned int Model::getAmountOfVertices()
{
	return amountOfVertices;
}
void Model::setAmountOfVertices(unsigned int amountOfVertices)
{
	this->amountOfVertices = amountOfVertices;
}

GLuint Model::getVao()
{
	return vao;
}

void Model::setVertexDataPointer(float* vertexData)
{
	this->vertexData = vertexData;
}
void Model::copyVertexData(float* vertexData, unsigned int amountOfVertices)
{
	delete[] this->vertexData;
	this->vertexData = new float[amountOfVertices * 3];
	for (int i = 0; i < amountOfVertices; i++)
	{
		this->vertexData[i * 3] = vertexData[i * 3];
		this->vertexData[i * 3 + 1] = vertexData[i * 3 + 1];
		this->vertexData[i * 3 + 2] = vertexData[i * 3 + 2];
	}
}
void Model::setTexCoordDataPointer(float* texCoordData)
{
	this->texCoordData = texCoordData;
}
void Model::copyTexCoordData(float* texCoordData, unsigned int amountOfVertices)
{
	delete[] this->texCoordData;
	this->texCoordData = new float[amountOfVertices * 2];
	for (int i = 0; i < amountOfVertices; i++)
	{
		this->texCoordData[i * 2] = texCoordData[i * 2];
		this->texCoordData[i * 2 + 1] = texCoordData[i * 2 + 1];
		this->texCoordData[i * 2 + 2] = texCoordData[i * 2 + 2];
	}
}
void Model::setNormalDataPointer(float* normalData)
{
	this->normalData = normalData;
}
void Model::copyNormalData(float* normalData, unsigned int amountOfVertices)
{
	delete[] this->normalData;
	this->normalData = new float[amountOfVertices * 3];
	for (int i = 0; i < amountOfVertices; i++)
	{
		this->normalData[i * 3] = normalData[i * 3];
		this->normalData[i * 3 + 1] = normalData[i * 3 + 1];
		this->normalData[i * 3 + 2] = normalData[i * 3 + 2];
	}
}

void Model::setIndexDataPointer(unsigned int* indexData)
{
	this->indexData = indexData;
}
void Model::copyIndexData(unsigned int* indexData, unsigned int amountOfVertices)
{
	delete[] this->indexData;
	this->indexData = new unsigned int[amountOfVertices];
	for (int i = 0; i < amountOfVertices; i++)
	{
		this->indexData[i] = indexData[i];
	}
}

void Model::setAllPointers(float* vertexData, float* texCoordData, float* normalData, unsigned int* indexData)
{
	setVertexDataPointer(vertexData);
	setTexCoordDataPointer(texCoordData);
	setNormalDataPointer(normalData);
	setIndexDataPointer(indexData);
}

void Model::copyAllData(float* vertexData, float* texCoordData, float* normalData, unsigned int* indexData, unsigned int amountOfVertices)
{
	setAmountOfVertices(amountOfVertices);
	copyVertexData(vertexData, amountOfVertices);
	copyTexCoordData(texCoordData, amountOfVertices);
	copyNormalData(normalData, amountOfVertices);
	copyIndexData(indexData, amountOfVertices);
}

float* Model::getVertexPointer()
{
	return vertexData;
}
float* Model::getTexCoordPointer()
{
	return texCoordData;
}
float* Model::getNormalPointer()
{
	return normalData;
}

void Model::updateVertexOpenGLData()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * 3 * amountOfVertices, vertexData);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Model::updateTexCoordOpenGLData()
{
	glBindBuffer(GL_ARRAY_BUFFER, texCoordVbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * 2 * amountOfVertices, texCoordData);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Model::updateNormalOpenGLData()
{
	glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * 3 * amountOfVertices, normalData);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Model::updateIndexOpenGLData()
{
	glBindBuffer(GL_ARRAY_BUFFER, indexVbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * amountOfVertices, indexData);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::updateAllOpenGLData()
{
	updateVertexOpenGLData();
	updateTexCoordOpenGLData();
	updateNormalOpenGLData();
	updateIndexOpenGLData();
}

void Model::putVertexData()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * amountOfVertices, vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Model::putTexCoordData()
{
	glBindBuffer(GL_ARRAY_BUFFER, texCoordVbo);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * amountOfVertices, texCoordData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Model::putNormalData()
{
	glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * amountOfVertices, normalData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Model::putIndexData()
{
	glBindBuffer(GL_ARRAY_BUFFER, indexVbo);
	glBufferData(GL_ARRAY_BUFFER, 4 * amountOfVertices, indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::putAllData()
{
	putVertexData();
	putTexCoordData();
	putNormalData();
	putIndexData();
}

void Model::initOpenGLData()
{
	glGenBuffers(1, &vertexVbo);
	glGenBuffers(1, &texCoordVbo);
	glGenBuffers(1, &normalVbo);
	glGenBuffers(1, &indexVbo);

	glGenVertexArrays(1, &vao);
}

void Model::setOpenGLPointers()
{
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordVbo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

void Model::setupOpenGL()
{
	initOpenGLData();
	putAllData();
	setOpenGLPointers();
}

void Model::draw()
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVbo);
	glDrawElements(GL_TRIANGLES, amountOfVertices * 3, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}