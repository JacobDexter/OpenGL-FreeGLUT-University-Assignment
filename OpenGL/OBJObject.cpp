#include "OBJObject.h"

OBJObject::OBJObject(Object* object, const char* mtlpath, float x, float y, float z) : SceneObject(object, nullptr)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;

	_material = new Material();
	LoadMat(mtlpath);
}

void OBJObject::Draw()
{
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, _object->vertices.size() * sizeof(glm::vec3), &_object->vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, _object->uvs.size() * sizeof(glm::vec2), &_object->uvs[0], GL_STATIC_DRAW);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
	glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
	glMaterialfv(GL_FRONT, GL_SHININESS, &(_material->Shininess));

	//Draw Tris
	glTranslatef(_position.x, _position.y, _position.z);
	glDrawArrays(GL_TRIANGLES, 0, _object->vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
}

void OBJObject::Update()
{
	
}

bool OBJObject::LoadMat(const char* mtlpath) //Load material coords from .mtl file
{
	ifstream inFile;

	inFile.open(mtlpath);

	if (!inFile.good()) {
		cerr << "Cannot open file! " << mtlpath << endl;
		return false;
	}

	while (!inFile.eof())
	{
		char lineHeader[128];

		// read the first word of the line
		inFile >> lineHeader;

		if (strcmp(lineHeader, "Ka") == 0) //Load ambient mat coords
		{
			inFile >> _material->Ambient.x >> _material->Ambient.y >> _material->Ambient.z;
		}
		else if (strcmp(lineHeader, "Kd") == 0) //Load diffuse mat coords
		{
			inFile >> _material->Diffuse.x >> _material->Diffuse.y >> _material->Diffuse.z;
		}
		else if (strcmp(lineHeader, "Ks") == 0) //Load specular mat coords
		{
			inFile >> _material->Specular.x >> _material->Specular.y >> _material->Specular.z;
		}
		else
		{
			//skip comment lines
		}
	}

	_material->Shininess = 100.0f;

	inFile.close();

	return true;
}

OBJObject::~OBJObject()
{
	
}