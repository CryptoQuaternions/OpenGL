#include "Camera.h"

Camera::Camera(void)
{
	Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	Position = glm::vec3(0.0f, 0.0f, 1.0f);
}


Camera::~Camera(void)
{
}

void Camera::Draw(Mesh * a_Renderable, ShaderProgram * a_Shaderprogram)
{
	glUniformMatrix4fv(a_Shaderprogram->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr( a_Renderable->GetTransformationMatrix()));
	glUniformMatrix4fv(a_Shaderprogram->GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(m_ViewMatrix));
	glUniformMatrix4fv(a_Shaderprogram->GetUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(m_ProjectionMatrix));
	a_Renderable->Draw();
}

void Camera::SetupCamera(double a_FOV, double a_AspectRatio, double a_NearPlane, double a_FarPlane)
{
	m_ProjectionMatrix = glm::perspective(
		a_FOV,
		a_AspectRatio,
		a_NearPlane,
		a_FarPlane
	);

	m_ViewMatrix = glm::lookAt(
		glm::vec3(1.0, 0.0, 1.0),
		glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 0.0, 1.0)
	);
}

void Camera::Update()
{
	if(Rotation.x > 180)
		Rotation.x = -180;
	if(Rotation.y > 180)
		Rotation.y = -180;

	//Create rotation matrix
	glm::mat4 rot;
	rot = glm::rotate(rot, Rotation.y, glm::vec3(0.0, 0.0, 1.0));
	rot = glm::rotate(rot, Rotation.x, glm::vec3(1.0, 0.0, 0.0));
	//Calculate the direction
	glm::vec4 result = rot * glm::vec4(0.0, 1.0, 0.0, 0.0);
	m_Direction = glm::vec3(result.x, result.y, result.z);

	//Create lookat matrix
    m_ViewMatrix = glm::lookAt(
        Position,
		Position + m_Direction,
        glm::vec3(0.0, 0.0, 1.0)
    );
}

glm::vec3 Camera::GetForward()
{
	return m_Direction;
}

glm::vec3 Camera::GetLeft()
{
	return glm::cross(m_Direction, glm::vec3(0.0, 0.0, 1.0));
}