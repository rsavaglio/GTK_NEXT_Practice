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
		// Add entity to the map, set as active, set root as parent
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
		m_DisabledComponentMaps.push_back(new std::unordered_map<unsigned int, Component*>);

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

	void gtk::Scene::ToggleEntity(Entity* const entity, bool setActive)
	{
		// Disabled components and renderers are moved to disabled maps, where they are not updated.
		// Update is only called on components and renderers in the active maps.
		// This avoids having to check each if components are active each time they are updated. 

		// Disabling an entity essentially just disables all of its components and its renderer.
		// However, components' active tags are preserved.

		// So when setting an entity to active, only components tagged as active get moved
		// to the active maps.

		if (setActive)
		{
			// Return if entity is already active
			if (entity->_Active) { return; }

			// Tag as active
			entity->_Active = true;

			// Loop through disabled map vector
			for (int i = 0; i < m_DisabledComponentMaps.size(); i++) // Maps should be in the same order between vectors
			{
				// Does the entity have a component in this group?
				if (m_DisabledComponentMaps[i]->find(entity->_id) != m_DisabledComponentMaps[i]->end())
				{
					// Move it to the active map
					m_ComponentMaps[i]->insert({ entity->_id , m_DisabledComponentMaps[i]->at(entity->_id) });

					// Erase from disabled map
					m_DisabledComponentMaps[i]->erase(entity->_id);
				}
			}

			// Does entity have a renderer?
			if (m_DisabledRenderers.find(entity->_id) != m_DisabledRenderers.end())
			{
				// Move it to the active map
				m_RendererMap.insert({ entity->_id , m_DisabledRenderers.at(entity->_id) });

				// Erase from disabled map
				m_DisabledRenderers.erase(entity->_id);
			}

		}
		else
		{
			// Return if entity is already inactive
			if (!entity->_Active) { return; }

			// Tag as inactive
			entity->_Active = false;

			// Loop through active map vector
			for (int i = 0; i < m_ComponentMaps.size(); i++) // Maps should be in the same order between vectors
			{
				// Does the entity have a component in this group?
				if (m_ComponentMaps[i]->find(entity->_id) != m_ComponentMaps[i]->end())
				{
					// Move it to the disabled map
					m_DisabledComponentMaps[i]->insert({ entity->_id , m_ComponentMaps[i]->at(entity->_id) });

					// Erase from active map
					m_ComponentMaps[i]->erase(entity->_id);
				}
			}

			// Does entity have a renderer?
			if (m_RendererMap.find(entity->_id) != m_RendererMap.end())
			{
				// Move it to the disabled map
				m_DisabledRenderers.insert({ entity->_id , m_RendererMap.at(entity->_id) });

				// Erase from active map
				m_RendererMap.erase(entity->_id);
			}
		}
	}

	void gtk::Scene::ToggleComponent(Component* const component, bool setActive)
	{
		// If the entity is active we move the component between maps based on requested state
		if (component->m_Entity->_Active)
		{
			if (setActive)
			{
				// Return if already active
				if (component->m_Active) { return; }

				// Move the component back into the active component map
				m_ComponentMaps[component->m_GroupID]->
					insert({ component->m_Entity->_id, m_DisabledComponentMaps[component->m_GroupID]->at(component->m_Entity->_id) });

				// Erase component from disabled map
				m_DisabledComponentMaps[component->m_GroupID]->erase(component->m_Entity->_id);

				// Tag component as active
				component->m_Active = true;

			}
			else
			{
				// Return if already disabled
				if (!component->m_Active) { return; }

				// Move the component to the disabled map
				m_DisabledComponentMaps[component->m_GroupID]->
					insert({ component->m_Entity->_id, m_ComponentMaps[component->m_GroupID]->at(component->m_Entity->_id) });

				// Remove the component from component maps
				m_ComponentMaps[component->m_GroupID]->erase(component->m_Entity->_id);

				// Tag component not active
				component->m_Active = false;
			}

		}
		else // If the entity is not active, we don't move the component but tag it correctly
		{
			if (setActive)
			{
				// Tag component as active
				component->m_Active = true;

			}
			else
			{
				// Tag component not active
				component->m_Active = false;
			}
		}
	}

	void gtk::Scene::ToggleRenderer(Renderer* const renderer, bool setActive)
	{
		// If the entity is active we move the renderer between maps based on requested state
		if (renderer->m_Entity->_Active)
		{
			if (setActive)
			{
				// Return if already active
				if (renderer->m_Active) { return; }

				// Move the renderer back into the active component map
				m_RendererMap.insert({ renderer->m_Entity->_id, m_DisabledRenderers.at(renderer->m_Entity->_id) });

				// Erase renderer from disabled map
				m_DisabledRenderers.erase(renderer->m_Entity->_id);

				// Tag renderer as active
				renderer->m_Active = true;

			}
			else
			{
				// Return if already disabled
				if (!renderer->m_Active) { return; }

				// Move the renderer to the disabled map
				m_DisabledRenderers.insert({ renderer->m_Entity->_id, m_RendererMap.at(renderer->m_Entity->_id) });

				// Remove the renderer from component maps
				m_RendererMap.erase(renderer->m_Entity->_id);

				// Tag renderer not active
				renderer->m_Active = false;
			}

		}
		else // If the entity is not active, we don't move the renderer but tag it correctly
		{
			if (setActive)
			{
				// Tag renderer as active
				renderer->m_Active = true;

			}
			else
			{
				// Tag renderer not active
				renderer->m_Active = false;
			}
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
			
		} m_ComponentMaps.clear(); // Clear the vector


		// Loop through disabled comp map vector
		for (auto& CompMap : m_DisabledComponentMaps)
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

		} m_DisabledComponentMaps.clear(); // Clear the vector

		
		// Delete all renderers
		for (auto& renderer : m_RendererMap)
		{
			delete renderer.second;
		} 
		m_RendererMap.clear();

		// Delete all disabled renderers
		for (auto& renderer : m_DisabledRenderers)
		{
			delete renderer.second;
		} 
		m_DisabledRenderers.clear();

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

