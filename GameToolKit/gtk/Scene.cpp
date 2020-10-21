#include "Scene.h"

namespace gtk {

	Scene::Scene() :m_Root(new Entity(_EntityIDProvider++, nullptr))
	{

	}


	Scene::~Scene()
	{
		Shutdown();
	}

	Entity* Scene::CreateEntity()
	{
		// Add entity to the map, set as active
		m_EntityMap.insert({ _EntityIDProvider, new Entity(_EntityIDProvider, m_Root) });

		// Add to roots children
		m_Root->AddChild(m_EntityMap.at(_EntityIDProvider));

		// Return id and increment
		return m_EntityMap.at(_EntityIDProvider++);
	}

	Entity* Scene::CreateEntity(Entity* const parent)
	{
		// Add entity to the map, set as active
		m_EntityMap.insert({ _EntityIDProvider, new Entity(_EntityIDProvider, parent) });

		// Add this to parent's list of children
		parent->AddChild(m_EntityMap.at(_EntityIDProvider));

		// Return id and increment
		return m_EntityMap.at(_EntityIDProvider++);
	}
	
	CompGroup Scene::CreateCompGroup()
	{
		m_ComponentMaps.push_back(new std::unordered_map<unsigned int, Component*>);

		CompGroup newCompGroup(_CompGroupIDProvider++);

		return newCompGroup;
	}

	void Scene::AddComponent(Component* const component)
	{
		// Add component to correct map with the ID
		m_ComponentMaps[component->m_GroupID]->insert({ component->m_Entity->_id, component });
	}

	void Scene::AddRenderer(Renderer* const renderer)
	{
		// Add renderer to map with the id
		m_RendererMap.insert({ renderer->m_Entity->_id, renderer });
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
		// Loop through comp map vector
		for (auto& CompMap : m_ComponentMaps)
		{
			// Loop through comp map
			for (auto& Comp : *CompMap)
			{
				// Delete each component
				delete Comp.second;
			}

			// Clear the map
			CompMap->clear();

			// Delete the map
			delete CompMap;
			
		}

		// Clear the vector
		m_ComponentMaps.clear();

		// Delete all renderers
		for (auto& renderer : m_RendererMap)
		{
			delete renderer.second;
		} 
		m_RendererMap.clear();

		// Remove all entities
		for (auto& Entity : m_EntityMap)
		{
			delete Entity.second;
		}
		m_EntityMap.clear();

		// Delete the root entity
		delete m_Root;
	}

}

