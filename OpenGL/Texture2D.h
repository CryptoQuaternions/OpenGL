#pragma once
#include <gl/glew.h>
#include <gl/glfw.h>
#include <SOIL.h>

class Texture2D
{
	GLuint m_Texture;
	unsigned int m_Width, m_Height;
public:
	unsigned int GetWidth();
	unsigned int GetHeight();
	bool Load(const char * a_FilePath);
	void Bind();
	void BindAs(GLenum a_TextureID);
	void SetTextureParam(GLenum a_Target, GLenum a_Param, GLenum a_Value);
	Texture2D(void);
	~Texture2D(void);
};

