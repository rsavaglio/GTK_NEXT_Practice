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
		// Ensure no deplicate components on same entity
		ASSERT(m_ComponentMaps[component->m_GroupID]->find(component->m_Entity->_id) == m_ComponentMaps[component->m_GroupID]->end());

		// Add component to correct map with the ID
		m_ComponentMaps[component->m_GroupID]->insert({ component->m_Entity->_id, component });
	}

	void Scene::AddRenderer(Renderer* const renderer)
	{
		// Ensure no duplicate renderers
		ASSERT(m_RendererMap.find(renderer->m_Entity->_id) == m_RendererMap.end());

		// Add renderer to map with the id
		m_RendererMap.insert({ renderer->m_Entity->_id, renderer });
	}

	void gtk::Scene::ToggleComponent(Component* const component, bool setActive)
	{
		if (setActive) // Enable Component
		{
			// If component is already active return
			if (component->m_Active) { return; }

			// Entity must be active to activate a component
			if (component->m_Entity->_Active)
			{
				// Move the component back into the component map
				m_ComponentMaps[component->m_GroupID]->insert({ component->m_Entity->_id, m_DisabledComponents.at(component->m_Entity->_id) });

				// Remove component from disabled map
				m_DisabledComponents.erase(component->m_Entity->_id);

				// Set component to active
				component->m_Active = true;
			}
		}
		else // Disable Component
		{
			// If component already disabled return
			if (!component->m_Active) { return; }

			// Move the component to the disabled map
			m_DisabledComponents.insert({ component->m_Entity->_id, m_ComponentMaps[component->m_GroupID]->at(component->m_Entity->_id) });

			// Remove the component from component maps
			m_ComponentMaps[component->m_GroupID]->erase(component->m_Entity->_id);

			component->m_Active = false;
		}
	}

	void gtk::Scene::ToggleRenderer(Renderer* const renderer, bool setActive)
	{
		if (setActive) // Enable renderer
		{
			// If renderer is already active return
			if (renderer->m_Active) { return; }

			// Entity must be active to activate a renderer
			if (renderer->m_Entity->_Active)
			{
				// Move the renderer back into the renderer map
				m_RendererMap.insert({ renderer->m_Entity->_id, m_DisabledRenderers.at(renderer->m_Entity->_id) });

				// Remove renderer from disabled map
				m_DisabledRenderers.erase(renderer->m_Entity->_id);

				// Set renderer to active
				renderer->m_Active = true;
			}
		}
		else // Disable renderer
		{

			// If renderer already disabled return
			if (!renderer->m_Active) { return; }

			// Move the renderer to the disabled map
			m_DisabledRenderers.insert({ renderer->m_Entity->_id, m_RendererMap.at(renderer->m_Entity->_id) });

			// Remove the renderer from renderer map
			m_RendererMap.erase(renderer->m_Entity->_id);

			renderer->m_Active = false;
		}
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

