#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Structures.h"
#include "SceneObject.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class OBJObject : public SceneObject
{
private:
	//cube positions
	GLfloat _rotation = 0.0f;
	Vector3 _position;

	//material
	Material* _material;
public:
	//constructor/deconstructor
	OBJObject(Object* object, const char* mtlpath, float x, float y, float z);
	~OBJObject();

	void Draw();
	void Update();

	//Material Load
	bool LoadMat(const char* mtlpath);
};