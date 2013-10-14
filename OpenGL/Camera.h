#pragma once
#include "singleton.h"
#include "mesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

class Camera
{
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	glm::vec3 m_Direction;
public:
	glm::vec3 Rotation;
	glm::vec3 Position;

	void Update();
	void Draw(Mesh * a_Renderable, ShaderProgram * a_Shaderprogram);
	void SetupCamera(double a_FOV, double a_AspectRatio, double a_NearPlane, double a_FarPlane);
	Camera(void);
	~Camera(void);
};

