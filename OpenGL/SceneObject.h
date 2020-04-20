#pragma once

#include "Structures.h"
#include "Texture2D.h"

class SceneObject
{
protected:
	Mesh* _mesh;
	Object* _object;
	Texture2D* _texture;

public:
	SceneObject(Mesh* mesh, Texture2D* texture);
	SceneObject(Object* object, Texture2D* texture);
	virtual ~SceneObject();

	virtual void Update();
	virtual void Draw();

	float _rotationSpeed;
};