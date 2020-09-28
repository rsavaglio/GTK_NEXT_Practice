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

		virtual ~Scene() 
		{
			// Delete all comps

			// Delete all entities
		}

		const Game& GetGame()
		{
			return m_Game;
		}


		int CreateEntity()
		{
			// Create entity

			// Set id

			// Add entity to the map

			return 0;
		}
	
	protected:

		virtual void SetupHierarchy()
		{
			// To be overriden

			// Used to setup entities and components
		}

	private:

		Scene(const std::string& name, const Game& game) :m_Name(name), m_Game(game) {}

		void Update()
		{
			// To be called by game

			// Traverse Componenet Sets and call update in each component

		}

		void Shutdown()
		{
			// To be called by game

			// delete componenents

			// delete all entities
		}

		Camera m_Camera;
		const std::string m_Name;
		const Game& m_Game;

		std::unordered_map<unsigned int, Entity*> m_EntityList; // Either using a string or int as key
		std::vector<std::unordered_map<unsigned int, Component>> m_ComponenetMaps;

	};
}