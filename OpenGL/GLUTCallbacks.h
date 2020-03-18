#pragma once

class OpenGL;

namespace GLUTCallbacks
{
	void Init(OpenGL* gl);
	void Display();
	void Timer(int preferredRefresh);
	void Input(unsigned char key, int x, int y);
}