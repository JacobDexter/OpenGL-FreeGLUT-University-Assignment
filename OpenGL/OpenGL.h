#pragma once
#include <windows.h>
#include "GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Cube.h"
#include "Pyramid.h"
#include "OBJObject.h"
#include "glm/glm.hpp"
#include <vector>
#include "OBJLoader.h"
#include "MeshLoader.h"
#include <iostream>

#define REFRESHRATE 16
#define SCREENWIDTH 800
#define SCREENHEIGHT 800

#define OBJECTCOUNT 200

using namespace std;

class OpenGL
{
public:
	OpenGL(int argc, char* argv[]);
	~OpenGL(void);
	void InitGL(int argc, char* argv[]);
	void InitLighting();
	void InitObjects();
	void Display();
	void Update();
	void Input(unsigned char key, int x, int y);
	void DrawString(const char* text, Vector3* position, Color* color);

private:
	float rotation;
	Camera* camera;
	SceneObject* objects[OBJECTCOUNT];
	SceneObject* OBJmodel;

	Texture2D* texture;
	Texture2D* texture2;

	//lighting
	Vector4* _lightPosition;
	Lighting* _lightData;
};

