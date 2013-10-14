#include "Camera.h"


Camera::Camera(void)
{
	Rotation = glm::vec3(-45.0f,0.0f, 0.0f);
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
	m_Direction = glm::vec3(0.0, 0.0, 0.0);

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
	glm::vec4 vec = glm::eulerAngleYXZ(Rotation.y, Rotation.x, Rotation.z) * glm::vec4(0.0f,1.0f,0.0f,0.0f);
	m_ViewMatrix = glm::lookAt(
		Position,
		glm::vec3(vec.x, vec.y, vec.z) + Position,
		glm::vec3(0.0, 0.0, 1.0)
	);
}
