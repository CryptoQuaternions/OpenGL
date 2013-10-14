#pragma once
#include <gl/glew.h>
#include <gl/glfw.h>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
	bool m_ReportErrors;
	GLuint m_Shader;
public:
	Shader(void);
	Shader( char * a_Shader, GLuint a_ShaderType );
	~Shader(void);
	GLuint GetShader();
	void Load(const GLchar * a_Shader, GLuint a_ShaderType);
	void LoadFromFile(char * a_Shader, GLuint a_ShaderType);
	void ReportErrors();
	void DisableErrors();
	void CheckErrors(GLuint a_Shader);
};