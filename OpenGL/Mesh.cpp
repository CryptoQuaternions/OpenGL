#include "Mesh.h"


Mesh::Mesh(void)
{
	glGenBuffers( 1, &m_EBO );
	glGenBuffers( 1, &m_VBO );
	m_Vertices = 0;
	m_Elements = 0;
	m_DrawMode = GL_TRIANGLES;
}

Mesh::~Mesh(void)
{

}

GLuint Mesh::GetVBO()
{
	return m_VBO;
}

GLuint Mesh::GetEBO()
{
	return m_EBO;
}

void Mesh::SetVertices(Vertex * a_Vertices, int a_NumVertices)
{
	m_Vertices = a_Vertices;
	m_VertexCount = a_NumVertices;
}

void Mesh::SetElements(GLuint * a_Elements, int a_NumElements)
{
	m_Elements = a_Elements;
	m_ElementCount = a_NumElements;
}

void Mesh::Build()
{
	if(m_Vertices == 0)
		std::cout << "[Renderable ERROR] Vertices not set !";
	if(m_Elements == 0)
		std::cout << "[Renderable ERROR] Elements not set !";
	
	glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
	glBufferData( GL_ARRAY_BUFFER, m_VertexCount * sizeof(Vertex), m_Vertices, GL_STATIC_DRAW );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_EBO );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( m_Elements ) * m_ElementCount, m_Elements, GL_STATIC_DRAW );
}

void Mesh::Draw()
{
	glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_EBO );
	glDrawElements( m_DrawMode, m_ElementCount, GL_UNSIGNED_INT, 0 );
}

void Mesh::SetDrawMode(GLenum a_DrawMode)
{
	m_DrawMode = a_DrawMode;
}

GLenum Mesh::GetDrawMode()
{
	return m_DrawMode;
}