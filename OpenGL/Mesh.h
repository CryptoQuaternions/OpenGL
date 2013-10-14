#pragma once
#include <iostream>
#include <gl/glew.h>
#include "ShaderProgram.h"
#include "Transformable.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 Color;
	glm::vec2 UV;
};

class Mesh : public Transformable
{
protected:
	GLenum m_DrawMode;
	GLuint m_VBO;
	GLuint m_EBO;
	GLuint * m_Elements;
	Vertex * m_Vertices;
	int m_VertexCount;
	int m_ElementCount;
public:
	Mesh(void);
	~Mesh(void);

	GLuint GetVBO();
	GLuint GetEBO();
	GLenum GetDrawMode();
	void SetDrawMode(GLenum a_DrawMode);
	void SetElements(GLuint * a_Elements, int a_ElementCount );
	void SetVertices(Vertex * a_Vertices, int a_VertexCount);
	virtual void Build();
	virtual void Draw();
};

