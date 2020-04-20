#include "OBJLoader.h"
#include <iostream>
#include <fstream>
namespace OBJLoader
{
	void OBJLoader::LoadOBJ(const char* path, Object* object)
	{
		vector <unsigned int> vertexIndices, uvIndices, normalIndices;
		vector <glm::vec3> temp_vertices;
		vector <glm::vec2> temp_uvs;
		vector <glm::vec3> temp_normals;

		ifstream inFile;
		
		inFile.open(path);

		if (!inFile.good()) {
			cerr << "Cannot open file! " << path << endl;
			return;
		}

		while (!inFile.eof())
		{
			char lineHeader[128];

			// read the first word of the line
			inFile >> lineHeader;

			if (strcmp(lineHeader, "v") == 0)
			{
				glm::vec3 vertex;
				inFile >> vertex.x >> vertex.y >> vertex.z;

				temp_vertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0)
			{
				glm::vec2 uv;
				inFile >> uv.x >> uv.y;

				temp_uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0)
			{
				glm::vec3 normal;
				inFile >> normal.x >> normal.y >> normal.z;

				temp_normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0)
			{
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

				//Values from file
				inFile >> vertexIndex[0] >> uvIndex[0] >> normalIndex[0];
				inFile >> vertexIndex[1] >> uvIndex[1] >> normalIndex[1];
				inFile >> vertexIndex[2] >> uvIndex[2] >> normalIndex[2];

				for (unsigned int x = 0; x < 3; x++)
				{
					//push values into vector
					vertexIndices.push_back(vertexIndex[x]);
					uvIndices.push_back(uvIndex[x]);
					normalIndices.push_back(normalIndex[x]);
				}
			}
			else
			{
				//skip comment lines
			}
		}

		inFile.close();

		//order values
		// For each vertex of each triangle
		for (unsigned int i = 0; i < vertexIndices.size(); i++)
		{
			unsigned int vertexIndex = vertexIndices[i];
			glm::vec3 vertex = temp_vertices[vertexIndex - 1];

			object->vertices.push_back(vertex);
		}

		// For each uv of each triangle
		for (unsigned int i = 0; i < uvIndices.size(); i++)
		{
			unsigned int uvIndex = uvIndices[i];
			glm::vec2 uv = temp_uvs[uvIndex - 1];
			object->uvs.push_back(uv);
		}

		// For each normal of each triangle
		for (unsigned int i = 0; i < normalIndices.size(); i++)
		{
			unsigned int normalIndex = normalIndices[i];
			glm::vec3 normal = temp_normals[normalIndex - 1];
			object->normals.push_back(normal);
		}

		cout << path << " loaded." << endl;
	}

	Object* OBJLoader::Load(const char* path)
	{
		Object* object = new Object();

		LoadOBJ(path, object);

		return object;
	}
};