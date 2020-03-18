#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "Structures.h"
#include "SceneObject.h"

class Cube : public SceneObject
{
private:
	//cube positions
	GLfloat _rotation = 0.0f;
	Vector3 _position;

	//material
	Material* _material;
public:
	Cube(Mesh* mesh, Texture2D* texture, float x, float y,float z);
	~Cube();

	void Draw();
	void Update();
	void InitMat();
};