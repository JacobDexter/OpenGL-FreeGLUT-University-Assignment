#include "OpenGL.h"
#include "MeshLoader.h"
#include <iostream>

using namespace std;

OpenGL::OpenGL(int argc, char* argv[])
{
	InitGL(argc, argv);
	InitLighting();
	InitObjects();
	glutMainLoop();
}

void OpenGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("FOGGS Assignment 2 (Jacob Dexter)");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glutKeyboardFunc(GLUTCallbacks::Input);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, SCREENWIDTH, SCREENHEIGHT);
	gluPerspective(45, 1, 1, 1000);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glMatrixMode(GL_MODELVIEW);
	glCullFace(GL_BACK);
}

void OpenGL::InitLighting()
{
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 0.1;
	_lightPosition->z = 1.0;
	_lightPosition->w = 0.0;

	_lightData = new Lighting();
	_lightData->Ambient.x = 0.2;
	_lightData->Ambient.y = 0.2;
	_lightData->Ambient.z = 0.2;
	_lightData->Ambient.w = 1.0;
	_lightData->Diffuse.x = 0.8;
	_lightData->Diffuse.y = 0.8;
	_lightData->Diffuse.z = 0.8;
	_lightData->Diffuse.w = 1.0;
	_lightData->Specular.x = 0.2;
	_lightData->Specular.y = 0.2;
	_lightData->Specular.z = 0.2;
	_lightData->Specular.w = 1.0;
}

void OpenGL::InitObjects()
{
	//camera initialisation
	camera = new Camera();

	//Load Shapes
	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");
	//Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt");

	//Load Texture
	texture = new Texture2D();
	texture->Load((char*)"Penguins.raw", 512, 512);

	//cube initialisation
	for (int i = 0; i < OBJECTCOUNT; i++)
	{
		objects[i] = new Cube(cubeMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}

	//cube initialisation
	//for (int i = 200; i < OBJECTCOUNT; i++)
	//{
	//	objects[i] = new Pyramid(pyramidMesh, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	//}

	camera->eye.x = 0.0f;
	camera->eye.y = 0.0f;
	camera->eye.z = 1.0f;

	camera->center.x = 0.0f;
	camera->center.y = 0.0f;
	camera->center.z = 0.0f;

	camera->up.x = 0.0f;
	camera->up.y = 1.0f;
	camera->up.z = 0.0f;

	rotation = 0.0f;
}

void OpenGL::Update()
{
	//lighting
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));

	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	
	for (int i = 0; i < OBJECTCOUNT; i++)
	{
		objects[i]->Update();
	}

	glutPostRedisplay();
}

void OpenGL::Display()
{
	Vector3 v = { -0.4f, 0.38f, 0.0f };
	Color c = { 1.0f, 0.0f, 0.0f };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < OBJECTCOUNT; i++)
	{
		objects[i]->Draw();
	}

	DrawString("OpenGL Project", &v, &c);

	glFlush();
	glutSwapBuffers();
}

void OpenGL::Input(unsigned char key, int x, int y)
{
	//switch (key)
	//{
	//	case 'd':
	//		rotation += 0.5f; //rotate clockwise
	//		return;
	//	case 'a':
	//		rotation -= 0.5f; //rotate anticlockwise
	//		return;
	//	case '+':
	//		camera->eye.z += 0.1f; //zoom in
	//		return;
	//	case '-':
	//		camera->eye.z -= 0.1f; //zoom out
	//		return;
	//	return;
	//}
}

void OpenGL::DrawString(const char* text, Vector3* position, Color* color)
{
	glPushMatrix();
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0.0f, 0.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
	glPopMatrix();
}

OpenGL::~OpenGL(void)
{
	delete camera;
	delete _lightPosition;
	delete _lightData;
	delete texture;
	
	for (int i = 0; i < OBJECTCOUNT; i++)
	{
		delete objects[i];
	}
}