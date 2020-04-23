#include "OpenGL.h"

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
	glewInit();
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glutKeyboardFunc(GLUTCallbacks::Input);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, SCREENWIDTH, SCREENHEIGHT);
	gluPerspective(45, 1, 1, 1000);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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

	//Load Models
	Object* model = OBJLoader::Load("Objects/Asteroid.obj");

	//Load Shapes
	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");
	Mesh* pyramidMesh = MeshLoader::LoadNoTexCoords((char*)"pyramid.txt");

	//Load Texture
	texture = new Texture2D();
	texture->LoadRAW((char*)"stars.raw", 512, 512);

	OBJmodel = new OBJObject(model, "Materials/Asteroid.mtl", 0.0, 0.0, -60.0);

	//cube initialisation
	for (int i = 0; i < OBJECTCOUNT; i++)
	{
		objects[i] = new Cube(cubeMesh, texture, 45.0f,((rand() % 1000) / 10.0f) - 50.0f, ((rand() % 1000) / 10.0f) - 40.0f, -(rand() % 1000) / 10.0f);
	}

	camera->eye.x = 0.0f;
	camera->eye.y = 0.0f;
	camera->eye.z = 40.0f;

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
	Vector3 titlePosition = { -0.95f, 0.9f, 0.0f };
	Color titleColor = { 0.5f, 0.0f, 1.0f };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < OBJECTCOUNT; i++)
	{
		objects[i]->Draw();
	}

	DrawString(GetTimeString().c_str(), &titlePosition, &titleColor);

	OBJmodel->Draw();

	glFlush();
	glutSwapBuffers();
}

void OpenGL::Input(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 's':
			camera->eye.z += 0.5f; //zoom out
			return;
		case 'w':
			camera->eye.z -= 0.5f; //zoom in
			return;
		case 'a':
			camera->eye.x -= 0.5f; //left
			return;
		case 'd':
			camera->eye.x += 0.5f; //right
			return;
		case 'q': //slow down rotation
			for (int i = 0; i < OBJECTCOUNT; i++)
			{
				if (objects[i]->_rotationSpeed > 1.0f)
				{
					objects[i]->_rotationSpeed -= 0.5f;
				}
			}
			return;
		case 'e': //speed up rotation
			for (int i = 0; i < OBJECTCOUNT; i++)
			{
				if (objects[i]->_rotationSpeed < 15.0f)
				{
					objects[i]->_rotationSpeed += 0.5f;
				}
			}
			return;
		return;
	}
}

void OpenGL::DrawString(const char* text, Vector3* position, Color* color)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); //save matrix
	glLoadIdentity(); //wipe matrix
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_DEPTH_TEST); //ignore depth test so text renders on top
	glDisable(GL_LIGHTING); //dont apply lighting to text

	glColor3f(color->r, color->g, color->b); //set color
	glTranslatef(position->x, position->y, position->z); //set position
	glRasterPos2f(0.0f, 0.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text); //print string

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix(); //use old matrix
	glMatrixMode(GL_MODELVIEW); //go back to model view to render objects
	glPopMatrix();
}

string OpenGL::GetTimeString()
{
	//Time since glutinit
	int time = glutGet(GLUT_ELAPSED_TIME) / 1000; //get time in seconds
	int seconds = time % 60; //get seconds
	int minutes = time / 60; //get minutes

	//turn ints into stringstream
	stringstream secondsString;
	secondsString << seconds;
	stringstream minutesString;
	minutesString << minutes;

	string timeDisplay;

	if (seconds < 10)//checks if extra 0 is needed
	{
		//stringstream to string
		timeDisplay = minutesString.str() + ":0" + secondsString.str(); //Add a zero in front of seconds
	}
	else
	{
		//stringstream to string
		timeDisplay = minutesString.str() + ":" + secondsString.str();
	}

	if (time == NULL)
	{
		return "Start!";
	}

	return timeDisplay;
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

	delete OBJmodel;
}