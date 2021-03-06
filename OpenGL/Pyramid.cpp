#include "Pyramid.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

Pyramid::Pyramid(Mesh* mesh, float x, float y, float z) : SceneObject(mesh, nullptr)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
}

void Pyramid::InitMat()
{
	_material = new Material();
	_material->Ambient.x = 0.8; _material->Ambient.y = 0.05; _material->Ambient.z = 0.05;
	_material->Ambient.w = 1.0;
	_material->Diffuse.x = 0.8; _material->Diffuse.y = 0.05; _material->Diffuse.z = 0.05;
	_material->Diffuse.w = 1.0;
	_material->Specular.x = 1.0; _material->Specular.y = 1.0; _material->Specular.z = 1.0;
	_material->Specular.w = 1.0;
	_material->Shininess = 100.0f;
}

void Pyramid::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Normals != nullptr && _mesh->Indices != nullptr)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
		InitMat();
		glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x)); //draw ambient material
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x)); //draw diffuse material
		glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x)); //draw specular material
		glMaterialfv(GL_FRONT, GL_SHININESS, &(_material->Shininess)); //draw shininess material
		glPushMatrix();

		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);

		glPopMatrix();
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void Pyramid::Update()
{
	
}

Pyramid::~Pyramid()
{
	delete _material;
}