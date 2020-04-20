#include "Cube.h"

using namespace std;

Cube::Cube(Mesh* mesh, Texture2D* texture, GLfloat rotation, float x, float y, float z) : SceneObject(mesh, texture)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;

	_rotation = rotation;
	_rotationSpeed = 5.0f;
}

void Cube::InitMat()
{
	_material = new Material();
	_material->Ambient.x = 1.0; _material->Ambient.y = 1.00; _material->Ambient.z = 1.00;
	_material->Ambient.w = 1.0;
	_material->Diffuse.x = 0.64; _material->Diffuse.y = 0.64; _material->Diffuse.z = 0.64;
	_material->Diffuse.w = 1.0;
	_material->Specular.x = 0.5; _material->Specular.y = 0.5; _material->Specular.z = 0.5;
	_material->Specular.w = 1.0;
	_material->Shininess = 100.0f;
}

void Cube::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Normals != nullptr && _mesh->Indices != nullptr && _mesh->TexCoords != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);
		InitMat();
		glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
		glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
		glMaterialfv(GL_FRONT, GL_SHININESS, &(_material->Shininess));
		glPushMatrix();

		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);

		glPopMatrix();
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

void Cube::Update()
{
	_rotation += _rotationSpeed;
}

Cube::~Cube()
{
	delete _material;
}