#pragma once
#include <gl/glew.h>
#include <gl/glfw.h>
#include <iostream>
#include <vector>
#include "Shader.h"
#include "VertexDeclaration.h"
class ShaderProgram
{
	std::vector<Shader*> m_Shaders;
	VertexDeclaration * m_VertexDeclaration;
	GLuint m_ShaderProgram;
public:
	ShaderProgram(void);
	~ShaderProgram(void);
	void SetVertexDeclaration(VertexDeclaration * a_VertexDeclaration);
	void AddShader(Shader * shader);
	void Unbind(void);
	void Bind(void);
	void Link(void);
	void BindFragDataLocation(GLuint a_Index, const GLchar * a_Name);
	GLuint GetUniformLocation(const GLchar * a_Name);
	GLuint GetAttribLocation(const GLchar * a_Name);
};

