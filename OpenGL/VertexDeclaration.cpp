#include "VertexDeclaration.h"
#include <iostream>

VertexDeclaration::VertexDeclaration(void)
{
	this->m_VAO = 0;
	glGenVertexArrays(1, &this->m_VAO);
}


VertexDeclaration::~VertexDeclaration(void)
{
}

void VertexDeclaration::AddVertexAttribute(VertexAttribute * a_Attribute)
{
	m_VertexAttributes.push_back(a_Attribute);
}
void VertexDeclaration::BuildDeclaration(GLint a_ShaderProgram)
{
	glBindVertexArray( this->m_VAO );
	std::cout << glGetError() << std::endl;
	for (auto it = m_VertexAttributes.begin(); it != m_VertexAttributes.end(); it++)
	{
		GLint posAttrib = glGetAttribLocation( a_ShaderProgram, (*it)->m_Name );
			std::cout << glGetError() << std::endl;
		glVertexAttribPointer( posAttrib, (*it)->m_Size, (*it)->m_Type, (*it)->m_Normalized, (*it)->m_Stride, (*it)->m_Offset);
			std::cout << glGetError() << std::endl;
		glEnableVertexAttribArray( posAttrib );
			std::cout << glGetError() << std::endl;
	}
	
	glBindVertexArray( 0 );
}
void VertexDeclaration::Bind()
{
	glBindVertexArray( this->m_VAO );
}
void VertexDeclaration::Unbind()
{
	glBindVertexArray( 0 );
}
