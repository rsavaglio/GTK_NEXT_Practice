#pragma once

#include "Entity.h"
#include "Component.h"
#include "Camera.h"
#include "Renderer.h"
#include "Game.h"

#include <vector>
#include <unordered_map>

struct Entity
{
	unsigned int _id;
};

struct ComponentGroup
{
	unsigned int _id;
};

namespace gtk {

	class Scene {

		friend class Game;

	public:

		// TODO
		virtual ~Scene();

		// Get pointer to game
		Game* GetGame();

		Entity CreateEntity()
		{
			// Add entity to the map, set as active
			m_EntityMap.insert({ _EntityIDProvider, true });

			// Might want to create a transform by default here

			// Return id and increment
			return _EntityIDProvider++;
		}

		ComponentGroup CreateComponenetGroup()
		{
			m_ComponentMaps.push_back(new std::unordered_map<unsigned int, gtk::Component*>);

			return _ComponentGroupIDProvider++;
		}

		void AddComponent(const ComponentGroup& group, Component* const component)
		{
			// Add component to correct map with the ID
			m_ComponentMaps[group._id]->insert({ component->_id, component });
			
		}

		void AddRenderer(Renderer* const renderer)
		{
			// Add renderer to map with the id


			// Prevent memory leak for now
			delete renderer;
		}
		

	protected:

		// To be overriden in custom scenes
		// Used by game to start scenes
		virtual void Init() = 0;

		std::vector<std::unordered_map<unsigned int, Component*>*> m_ComponentMaps;
	
	private:

		// TODO
		void Update()
		{

			// Loop through the vector of maps
			for (auto& CompMap : m_ComponentMaps)
			{
				// Loop through comp map
				for (auto& Comp : *CompMap) 
				{
					Comp.second->Update();
				}
			}

			// Update renderers
			for (auto& renderer : m_RendererMap)
			{
				renderer.second->Draw();
			}

		}

		// TODO
		void Shutdown()
		{
			// To be called by game

			// delete componenents

			// Remove all entities
			m_EntityMap.clear();


		}

		ENTITY _EntityIDProvider = 0;
		COMP_GROUP _ComponentGroupIDProvider = 0;

		Game* m_Game;

		std::unordered_map<unsigned int, bool> m_EntityMap;
		std::unordered_map<unsigned int, Renderer*> m_RendererMap;

	};
}