#include "GLUTCallbacks.h"
#include "OpenGL.h"

namespace GLUTCallbacks
{
	namespace
	{
		OpenGL* openGL = nullptr;
	}

	void Init(OpenGL *gl)
	{
		openGL = gl;
	}

	void Display()
	{
		if (openGL != nullptr)
		{
			openGL->Display();
		}
	}

	void Timer(int preferredRefresh)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		openGL->Update();
		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
		glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);
	}

	void Input(unsigned char key, int x, int y)
	{
		openGL->Input(key, x, y);
	}
}