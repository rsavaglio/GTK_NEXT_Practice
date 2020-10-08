#include "Scene.h"

namespace gtk {

	unsigned int Scene::_idProvider = 0;

	Scene::~Scene()
	{
		// Delete all entities

		// Delete all componenets

	}

	Game* Scene::GetGame()
	{
		return m_Game;
	}

}

