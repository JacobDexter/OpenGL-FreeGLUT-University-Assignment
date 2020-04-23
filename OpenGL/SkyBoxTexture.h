#pragma once
#include <string>
#include "GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include <iostream>

using namespace std;

class SkyBoxTexture
{
public:
    SkyBoxTexture(const string& Directory, const string& PosXFilename, const string& NegXFilename, const string& PosYFilename, const string& NegYFilename, const string& PosZFilename, const string& NegZFilename);
    ~SkyBoxTexture();

    bool Load();
    void Bind(GLenum TextureUnit);

private:
    string m_fileNames[6];
    GLuint m_textureObj;
};

