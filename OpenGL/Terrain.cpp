#include "Terrain.h"


Terrain::Terrain(void)
{
	m_DrawMode = GL_TRIANGLES;
}


Terrain::~Terrain(void)
{
}

void Terrain::GenerateTerrain(int a_TerrainSize, float a_TileWidth, float a_TileHeight, const char * a_MapFile)
{
	int img_width, img_height, img_channels;
	unsigned char * img_data = SOIL_load_image(a_MapFile, &img_width, &img_height, &img_channels, SOIL_LOAD_RGB);

	m_TerrainSize = a_TerrainSize;
	m_TileWidth = a_TileWidth;
	m_TileHeight = a_TileHeight;

	int TerrainSizeSquared = a_TerrainSize * a_TerrainSize;
	int TerrainSizeMinOneSquared = (a_TerrainSize - 1) * (a_TerrainSize - 1);

	m_VertexCount = TerrainSizeSquared;
	m_Vertices = new Vertex[m_VertexCount];

	m_ElementCount = TerrainSizeMinOneSquared * 6;
	m_Elements = new GLuint[m_ElementCount];

	//Create Grid
	for(int y = 0; y < a_TerrainSize; y++)
	{
		for(int x = 0; x < a_TerrainSize; x++)
		{
			float heigth = img_data[(y * img_width + x) * 3];
			m_Vertices[y * a_TerrainSize + x].Position.x = x * a_TileWidth;
			m_Vertices[y * a_TerrainSize + x].Position.y = y * a_TileHeight;
			m_Vertices[y * a_TerrainSize + x].Position.z = heigth * 2;
			m_Vertices[y * a_TerrainSize + x].Color.r = 1.0f;
			m_Vertices[y * a_TerrainSize + x].Color.g = 1.0f;
			m_Vertices[y * a_TerrainSize + x].Color.b = 1.0f;
			m_Vertices[y * a_TerrainSize + x].UV.x = ((float)x) / 32.0f;
			m_Vertices[y * a_TerrainSize + x].UV.y = ((float)y) / 32.0f;
		}											   
	}

	//Setup Elements
	int cnt = 0;
	for(int y = 0; y < m_TerrainSize - 1; y++)
	{
		for(int x = 0; x < m_TerrainSize - 1; x++)
		{
			int tl = x + y * a_TerrainSize;
			int tr = (x + 1) + y * a_TerrainSize;
			int ll = x + (y + 1) * a_TerrainSize;
			int lr = (x + 1) + (y + 1) * a_TerrainSize;

			m_Elements[cnt + 0] = tl;
			m_Elements[cnt + 1] = tr;
			m_Elements[cnt + 2] = ll;
			m_Elements[cnt + 3] = tr;
			m_Elements[cnt + 4] = lr;
			m_Elements[cnt + 5] = ll;

			cnt += 6;
		}
	}

	for(int i = 0; i < m_ElementCount; i+=3)
	{
		Vertex v1 = m_Vertices[m_Elements[i]];
		Vertex v2 = m_Vertices[m_Elements[i + 1]];
		Vertex v3 = m_Vertices[m_Elements[i + 2]];

		glm::vec3 side1 = v2.Position - v1.Position;
		glm::vec3 side2 = v1.Position - v3.Position;
		glm::vec3 normal = glm::cross(side1, side2);
		
		glm::normalize(normal);

		m_Vertices[m_Elements[i]].Normal += normal;
		m_Vertices[m_Elements[i + 1]].Normal += normal;
		m_Vertices[m_Elements[i + 2]].Normal += normal;
	}

	for(int i = 0; i < m_VertexCount; i++)
		m_Vertices[i].Normal = glm::normalize(m_Vertices[i].Normal);
}
