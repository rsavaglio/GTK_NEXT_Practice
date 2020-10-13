#include "Scene.h"

namespace gtk {


	Scene::~Scene()
	{
		// Delete all entities

		// Delete all componenets

	}

	Entity Scene::CreateEntity()
	{
		// Add entity to the map, set as active
		m_EntityMap.insert({ _EntityIDProvider, true });

		// Might want to create a transform by default here

		// Return id and increment
		return _EntityIDProvider++;
	}
	
	ComponentGroup Scene::CreateComponenetGroup()
	{
		m_ComponentMaps.push_back(new std::unordered_map<unsigned int, Component*>);

		return _ComponentGroupIDProvider++;
	}

	void Scene::AddComponent(const ComponentGroup& group, Component* const component)
	{
		// Add component to correct map with the ID
		m_ComponentMaps[group._id]->insert({ component->_id, component });

	}

	void Scene::AddRenderer(Renderer* const renderer)
	{
		// Add renderer to map with the id

		// Prevent memory leak for now
		delete renderer;
	}

	void gtk::Scene::Update()
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

	void gtk::Scene::Shutdown()
	{
		// To be called by game

		// delete componenents

		// Remove all entities
		m_EntityMap.clear();
	}

}

