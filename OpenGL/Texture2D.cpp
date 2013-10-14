#include "Texture2D.h"

Texture2D::Texture2D(void)
{

}

Texture2D::~Texture2D(void)
{
	
}

bool Texture2D::Load(const char * a_FilePath)
{
	int img_width, img_height, img_channels;
	unsigned char * img_data = SOIL_load_image(a_FilePath, &img_width, &img_height, &img_channels, SOIL_LOAD_RGB);
	
	if(img_data == 0)
		return false;

	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
	
	SOIL_free_image_data(img_data);
	return true;
}

unsigned int Texture2D::GetWidth()
{
	return m_Width;
}

unsigned int Texture2D::GetHeight()
{
	return m_Height;
}

void Texture2D::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
}

void Texture2D::BindAs(GLenum a_TextureID)
{
	glActiveTexture(a_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
}

void Texture2D::SetTextureParam(GLenum a_Target, GLenum a_Param, GLenum a_Value)
{
	glTexParameteri(a_Target, a_Param, a_Value);
}