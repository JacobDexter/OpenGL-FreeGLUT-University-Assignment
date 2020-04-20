#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "Structures.h"
#include "SceneObject.h"

class Pyramid : public SceneObject
{
private:
	Vector3 _position;
	GLfloat _rotation = 0.0f;

	//material
	Material* _material;
public:
	Pyramid(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Pyramid();

	void Draw();
	void Update();
	void InitMat();
};