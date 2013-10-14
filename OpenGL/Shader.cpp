#include "Shader.h"


Shader::Shader(void)
{
	m_ReportErrors = true;
}

Shader::Shader( char * a_Shader, GLuint a_ShaderType )
{
	m_ReportErrors = true;
	LoadFromFile(a_Shader, a_ShaderType);
}

Shader::~Shader(void)
{

}

GLuint Shader::GetShader()
{
	return m_Shader;
}

void Shader::Load(const GLchar * a_Shader, GLuint a_ShaderType)
{
	m_Shader = glCreateShader( a_ShaderType );
	glShaderSource( m_Shader, 1, &a_Shader, 0 );
	glCompileShader( m_Shader );

	if(m_ReportErrors)
		CheckErrors(m_Shader);
}


void Shader::LoadFromFile( char * a_Shader, GLuint a_ShaderType )
{
	std::string shader;
	std::ifstream file;
	file.open (a_Shader);
	if (file.is_open())
	{
		std::stringstream buffer;
		buffer << file.rdbuf();
		shader = buffer.str();
		file.close();
	}
	else
	{
		std::cout << "[SHADER] Error opening file : " << a_Shader;
	}

	Load(shader.c_str(), a_ShaderType);
}

void Shader::ReportErrors()
{
	m_ReportErrors = true;
}

void Shader::DisableErrors()
{
	m_ReportErrors = false;
}

void Shader::CheckErrors(GLuint a_Shader)
{
	char buffer[512];
	glGetShaderInfoLog( a_Shader, 512, NULL, buffer ); 
	std::cout << "[SHADER] Shader error : " << std::endl;
	std::cout << buffer << std::endl;
}