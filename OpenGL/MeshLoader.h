#pragma once

#include <windows.h>
#include "Structures.h"
#include <iostream>
#include <fstream>
#include <gl/GL.h>

namespace MeshLoader
{
	Mesh* Load(char* path);
	Mesh* LoadNoTexCoords(char* path);
};