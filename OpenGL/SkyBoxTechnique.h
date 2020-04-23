#pragma once
#include <string>
#include "GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include <iostream>
#include "glm/glm.hpp"

class SkyBoxTechnique
{
public:
    SkyboxTechnique();

    virtual bool Init();

    void SetWVP(const Matrix4f& WVP);
    void SetTextureUnit(unsigned int TextureUnit);

private:
    GLuint m_WVPLocation;
    GLuint m_textureLocation;
};