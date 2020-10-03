#include "Scene.h"

namespace gtk {
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

