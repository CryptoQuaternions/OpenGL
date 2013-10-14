#include "Transformable.h"


Transformable::Transformable(void)
{
	m_Scale = glm::vec3(1,1,1);
}

glm::mat4 Transformable::GetTransformationMatrix()
{
	glm::mat4 mat = glm::mat4();
	mat = glm::scale(mat, m_Scale);
	mat = glm::rotate(mat, m_Rotation.x, glm::vec3(1,0,0));
	mat = glm::rotate(mat, m_Rotation.y, glm::vec3(0,1,0));
	mat = glm::rotate(mat, m_Rotation.z, glm::vec3(0,0,1));
	mat = glm::translate(mat, m_Position);

	return mat;
}

Transformable::~Transformable(void)
{

}

void Transformable::SetRotation(glm::vec3 a_Rotation)
{
	m_Rotation = a_Rotation;
}

void Transformable::SetPosition(glm::vec3 a_Position)
{
	m_Position = a_Position;
}

void Transformable::SetScale(glm::vec3 a_Scale)
{
	m_Scale = a_Scale;
}

glm::vec3 Transformable::GetPosition()
{
	return m_Position;
}

glm::vec3 Transformable::GetScale()
{
	return m_Scale;
}

glm::vec3 Transformable::GetRotation()
{
	return m_Rotation;
}
