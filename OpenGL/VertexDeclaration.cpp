#include "VertexDeclaration.h"


VertexDeclaration::VertexDeclaration(void)
{
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
	
	for (auto it = m_VertexAttributes.begin(); it != m_VertexAttributes.end(); it++)
	{
		GLint posAttrib = glGetAttribLocation( a_ShaderProgram, (*it)->m_Name );
		glVertexAttribPointer( posAttrib, (*it)->m_Size, (*it)->m_Type, (*it)->m_Normalized, (*it)->m_Stride, (*it)->m_Offset);
		glEnableVertexAttribArray( posAttrib );
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
