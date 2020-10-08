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

		unsigned int CreateEntity()
		{
			// Add entity to the map, set as active
			m_EntityMap.insert({ _idProvider, true });

			// Might want to create a transform by default here

			// Return id and increment
			return _idProvider++;
		}

		void AddComponent(Component* const component)
		{
			// Add component to correct map with the ID
			

			// Prevent memory leak for now
			delete component;
			
		}
		

	protected:

		// To be overriden in custom scenes
		// Used by game to start scenes
		virtual void Init() = 0;
	
	private:

		// TODO
		void Update()
		{
			// Do all things at once


		}

		// TODO
		void Shutdown()
		{
			// To be called by game

			// delete componenents

			// delete all entities

		}


		static unsigned int _idProvider;

		Camera m_Camera;
		Game* m_Game;

		std::unordered_map<unsigned int, bool> m_EntityMap;
		std::vector<std::unordered_map<unsigned int, Component>> m_ComponenetMaps;

	};
}