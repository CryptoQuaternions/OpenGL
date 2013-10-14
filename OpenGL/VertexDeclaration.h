#pragma once
#include <list>
#include <gl/glew.h>

struct VertexAttribute
{
	char * m_Name;
	GLint m_Size;
	GLenum m_Type;
	GLboolean m_Normalized;
	GLsizei m_Stride;
	GLvoid * m_Offset;

	VertexAttribute(char * a_Name, GLint a_Size, GLenum a_Type, GLboolean a_Normalized,	GLsizei a_Stride, GLvoid * a_Offset)
	{
		m_Name = a_Name;
		m_Size = a_Size;
		m_Type = a_Type;
		m_Normalized = a_Normalized;
		m_Stride = a_Stride;
		m_Offset = a_Offset;
	}
};

class VertexDeclaration
{
	GLuint m_VAO;
	std::list<VertexAttribute*> m_VertexAttributes;
public:
	VertexDeclaration(void);
	~VertexDeclaration(void);
	void AddVertexAttribute(VertexAttribute * a_Attribute);
	void BuildDeclaration(GLint a_ShaderProgram);
	void Bind();
	void Unbind();
};

