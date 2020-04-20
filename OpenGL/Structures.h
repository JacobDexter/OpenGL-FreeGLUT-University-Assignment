#pragma once

#include "GL/freeglut.h"
#include <vector>
#include "glm/glm.hpp"

struct Vector3
{
	float x, y, z, w;
};

struct Vector4
{
	float x, y, z, w;
};

struct Camera
{
	Vector3 eye;
	Vector3 center;
	Vector3 up;
};

struct Color
{
	GLfloat r, g, b;
};

//Mesh
struct Vertex
{
	GLfloat x, y, z;
};

struct TexCoord
{
	GLfloat u, v;
};

struct Mesh
{
	Vertex* Vertices;
	Vector3* Normals;
	GLushort* Indices;
	TexCoord* TexCoords;
	int VertexCount, NormalCount, IndexCount, TexCoordCount;
};

//Object
struct Object
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
};

//Visual
struct Lighting
{
	Vector4 Ambient, Diffuse, Specular;
};

struct Material
{
	Vector4 Ambient, Diffuse, Specular;
	GLfloat Shininess;
};