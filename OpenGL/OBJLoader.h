#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "Structures.h"

using namespace std;

namespace OBJLoader 
{
	void LoadOBJ(const char* path, Object* object);
	Object* Load(const char* path);
};