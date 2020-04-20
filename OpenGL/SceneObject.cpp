#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, Texture2D* texture)
{
	_mesh = mesh;
	_texture = texture;
}

SceneObject::SceneObject(Object* object, Texture2D* texture)
{
	_object = object;
	_texture = texture;
}

void SceneObject::Update()
{

}

void SceneObject::Draw()
{

}

SceneObject::~SceneObject()
{

}