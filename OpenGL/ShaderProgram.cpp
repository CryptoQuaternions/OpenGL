#include "ShaderProgram.h"


ShaderProgram::ShaderProgram(void)
{
	m_ShaderProgram = glCreateProgram();
}


ShaderProgram::~ShaderProgram(void)
{
}

void ShaderProgram::Link(void)
{
	for(unsigned int i = 0; i < m_Shaders.size(); i++)
		glAttachShader(m_ShaderProgram, m_Shaders[i]->GetShader());
	glLinkProgram( m_ShaderProgram );
}

void ShaderProgram::Unbind(void)
{
	this->m_VertexDeclaration->Unbind();
	glUseProgram(0);
}

void ShaderProgram::Bind(void)
{
	this->m_VertexDeclaration->Bind();
	glUseProgram( m_ShaderProgram );
}

void ShaderProgram::BindFragDataLocation( GLuint a_Index, const GLchar * a_Name )
{
	glBindFragDataLocation(m_ShaderProgram, a_Index, a_Name);
}

GLuint ShaderProgram::GetUniformLocation( const GLchar * a_Name )
{
	return glGetUniformLocation(m_ShaderProgram, a_Name);
}

GLuint ShaderProgram::GetAttribLocation( const GLchar * a_Name )
{
	return glGetAttribLocation(m_ShaderProgram, a_Name);
}

void ShaderProgram::AddShader(Shader * shader)
{
	m_Shaders.push_back(shader);
}

void ShaderProgram::SetVertexDeclaration(VertexDeclaration * a_VertexDeclaration)
{
	m_VertexDeclaration = a_VertexDeclaration;
	m_VertexDeclaration->BuildDeclaration(m_ShaderProgram);
}