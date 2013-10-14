#pragma once
#include "Mesh.h"
#include <SOIL.h>

class Terrain : public Mesh
{
	int m_TerrainSize;
	float m_TileWidth;
	float m_TileHeight;

	ShaderProgram m_ShaderProgram;
	VertexDeclaration m_VertexDeclaration;
public:
	Terrain(void);
	~Terrain(void);

	void GenerateTerrain(int a_TerrainSize, float a_TileWidth, float a_TileHeight, const char * a_MapFile);
};

