#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transformable
{
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
	glm::vec3 m_Position;
public:
	void SetRotation(glm::vec3);
	void SetPosition(glm::vec3);
	void SetScale(glm::vec3);
	glm::vec3 GetRotation();
	glm::vec3 GetPosition();
	glm::vec3 GetScale();
	glm::mat4 GetTransformationMatrix();
	Transformable(void);
	~Transformable(void);
};

