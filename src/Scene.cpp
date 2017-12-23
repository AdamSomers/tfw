#include <iostream>

#include "Scene.h"

using namespace tfw;

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::render()
{
    cout << "rendering frame " << frameCount++ << endl;
}
