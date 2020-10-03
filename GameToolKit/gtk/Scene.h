#pragma once

#include "Entity.h"
#include "Component.h"
#include "Camera.h"
#include "Game.h"

#include <vector>
#include <unordered_map>


namespace gtk {

	class Scene {

		friend class Game;

	public:

		// TODO
		virtual ~Scene();

		// Get pointer to game
		Game* GetGame();

		// TODO
		int CreateEntity()
		{
			// Create entity

			// Set id

			// Add entity to the map

			return 1;
		}
		

	protected:

		// To be overriden in custom scenes
		// Used by game to start scenes
		virtual void Init() = 0;
	
	private:

		// TODO
		void Update()
		{
			// To be called by game

			// Traverse Componenet Sets and call update in each component

		}

		// TODO
		void Shutdown()
		{
			// To be called by game

			// delete componenents

			// delete all entities
		}

		Camera m_Camera;

		Game* m_Game;

		std::unordered_map<unsigned int, Entity*> m_EntityList; // Either using a string or int as key
		std::vector<std::unordered_map<unsigned int, Component>> m_ComponenetMaps;

	};
}