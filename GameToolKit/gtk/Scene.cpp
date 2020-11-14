#include "Scene.h"

#include "Game.h"

namespace gtk {

	Scene::Scene(Game& game)
		:m_MainCam(nullptr),
		m_SwitchScene(false), m_NextScene(""),
		m_Game(game), m_Root(m_EntityIDProvider++, nullptr, *this),
		m_EntityIDProvider(0), m_CompGroupIDProvider(0), m_RenderLayerIDProvider(0)
	{

	}

	Scene::~Scene()
	{
		Shutdown();
	}

	void Scene::SwitchScene(std::string key)
	{
		m_SwitchScene = true;
		m_NextScene = key;
	}

	Entity& Scene::CreateEntity()
	{
		// Add entity to the map, set as active, set root as parent
		m_EntityMap.insert({ m_EntityIDProvider, new Entity(m_EntityIDProvider, &m_Root, *this) });

		// Add to roots children
		m_Root.AddChild(m_EntityMap.at(m_EntityIDProvider));

		// Return id and increment
		return *m_EntityMap.at(m_EntityIDProvider++);
	}

	Entity& Scene::CreateEntity(Entity& parent)
	{
		// Add entity to the map, set as active
		m_EntityMap.insert({ m_EntityIDProvider, new Entity(m_EntityIDProvider, &parent, *this) });

		// Add this to parent's list of children
		parent.AddChild(m_EntityMap.at(m_EntityIDProvider));

		// Return id and increment
		return *m_EntityMap.at(m_EntityIDProvider++);
	}
	
	CompGroup Scene::CreateCompGroup()
	{
		m_ComponentMaps.push_back(new std::unordered_map<unsigned int, Component*>);
		m_DisabledComponentMaps.push_back(new std::unordered_map<unsigned int, Component*>);

		CompGroup newCompGroup(m_CompGroupIDProvider++);

		return newCompGroup;
	}

	RenderLayer Scene::CreateRenderLayer()
	{
		m_RendererMaps.push_back(new std::unordered_map<unsigned int, Renderer*>);
		m_DisabledRendererMaps.push_back(new std::unordered_map<unsigned int, Renderer*>);

		RenderLayer newRenderLayer(m_RenderLayerIDProvider++);

		return newRenderLayer;
	}

	Component& Scene::AddComponent(Entity& entity, const CompGroup& group, Component* const component)
	{
		// Set scene object data
		component->Init(entity._id, this);

		// Set component data
		component->m_GroupID = group._id;

		// Ensure no deplicate components on same entity
		ASSERT(m_ComponentMaps[group._id]->find(entity._id) == m_ComponentMaps[group._id]->end());

		// Add component to correct map with the ID
		m_ComponentMaps[group._id]->insert({ entity._id, component });

		return *component;
	}

	Renderer& Scene::AddRenderer(Entity& entity, const RenderLayer& layer, const Camera& camera, Renderer* const renderer)
	{
		// Set scene object data
		renderer->Init(entity._id, this);

		// Set renderer data
		renderer->m_Camera = &camera;
		renderer->m_LayerID = layer._id;

		// Ensure no deplicate renderer on same entity
		ASSERT(m_RendererMaps[layer._id]->find(entity._id) == m_RendererMaps[layer._id]->end());

		// Add renderer to correct map with the ID
		m_RendererMaps[layer._id]->insert({ entity._id, renderer });

		return *renderer;
	}

	Renderer& Scene::AddRenderer(Entity& entity, const RenderLayer& layer, Renderer* const renderer)
	{
		// Set scene object data
		renderer->Init(entity._id, this);

		// Set renderer data
		renderer->m_Camera = m_MainCam;
		renderer->m_LayerID = layer._id;

		// Ensure no deplicate renderer on same entity
		ASSERT(m_RendererMaps[layer._id]->find(entity._id) == m_RendererMaps[layer._id]->end());

		// Add renderer to correct map with the ID
		m_RendererMaps[layer._id]->insert({ entity._id, renderer });

		return *renderer;
	}

	Camera& Scene::AddCamera(Entity& entity, Camera* const camera)
	{
		// Set scene object data
		camera->Init(entity._id, this);

		// If first camera
		if (m_Cameras.size() == 0)
		{
			m_MainCam = camera;
		}
		// Only one camera per entity
		else 
		{
			ASSERT(m_Cameras.find(entity._id) == m_Cameras.end());
		}

		// Add camera to map
		m_Cameras.insert({ entity._id, camera });

		return *camera;
	}

	void Scene::SetMainCam(unsigned int id) 
	{
		ASSERT(m_Cameras.find(id) != m_Cameras.end());

		m_MainCam = m_Cameras.find(id)->second;
	}

	Camera& Scene::GetMainCam()
	{
		return *m_MainCam;
	}

	Entity& Scene::GetEntity(unsigned int id)
	{
		ASSERT(m_EntityMap.find(id) != m_EntityMap.end());

		return *m_EntityMap.at(id);
	}

	void gtk::Scene::ToggleEntity(Entity& entity, bool setActive)
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
			if (entity._Active) { return; }

			// Tag as active
			entity._Active = true;

			// Loop through disabled map vector
			for (int i = 0; i < m_DisabledComponentMaps.size(); i++) // Maps should be in the same order between vectors
			{
				// Does the entity have a component in this group?
				if (m_DisabledComponentMaps[i]->find(entity._id) != m_DisabledComponentMaps[i]->end())
				{
					// Comp is tagged as active
					if (m_DisabledComponentMaps[i]->at(entity._id)->m_Active)
					{
						// Move it to the active map
						m_ComponentMaps[i]->insert({ entity._id , m_DisabledComponentMaps[i]->at(entity._id) });

						// Erase from disabled map
						m_DisabledComponentMaps[i]->erase(entity._id);
					}
				}
			}


			// Loop through disabled map vector
			for (int i = 0; i < m_DisabledRendererMaps.size(); i++) // Maps should be in the same order between vectors
			{
				// Does the entity have a renderer in this layer?
				if (m_DisabledRendererMaps[i]->find(entity._id) != m_DisabledRendererMaps[i]->end())
				{
					// Renderer is tagged as active
					if (m_DisabledRendererMaps[i]->at(entity._id)->m_Active)
					{
						// Move it to the active map
						m_RendererMaps[i]->insert({ entity._id , m_DisabledRendererMaps[i]->at(entity._id) });

						// Erase from disabled map
						m_DisabledRendererMaps[i]->erase(entity._id);
					}
				}
			}

		}
		else // Set entitiy inactive
		{
			// Return if entity is already inactive
			if (!entity._Active) { return; }

			// Tag as inactive
			entity._Active = false;

			// Loop through active comp map vector
			for (int i = 0; i < m_ComponentMaps.size(); i++) // Maps should be in the same order between vectors
			{
				// Does the entity have a comp in this group?
				if (m_ComponentMaps[i]->find(entity._id) != m_ComponentMaps[i]->end())
				{
					// Move it to the disabled map
					m_DisabledComponentMaps[i]->insert({ entity._id , m_ComponentMaps[i]->at(entity._id) });

					// Erase from active map
					m_ComponentMaps[i]->erase(entity._id);
				}
			}

			// Loop through active renderer map vector
			for (int i = 0; i < m_RendererMaps.size(); i++) // Maps should be in the same order between vectors
			{
				// Does the entity have a renderer in this layer?
				if (m_RendererMaps[i]->find(entity._id) != m_RendererMaps[i]->end())
				{
					// Move it to the disabled map
					m_DisabledRendererMaps[i]->insert({ entity._id , m_RendererMaps[i]->at(entity._id) });

					// Erase from active map
					m_RendererMaps[i]->erase(entity._id);
				}
			}

		}

		for (auto& child : entity._Children)
		{
			ToggleEntity(*child, setActive);
		}
	}

	void gtk::Scene::ToggleComponent(Component& component, bool setActive)
	{
		unsigned int id = component.ID();
		unsigned int group = component.m_GroupID;

		// Does the id/entity even exist?
		ASSERT(m_EntityMap.find(id) != m_EntityMap.end());

		// Get entity
		Entity* entity = m_EntityMap.at(id);

		// If the entity is active we move the component between maps based on requested state
		if (entity->_Active)
		{

			if (setActive)
			{
				// Return if already active
				if (component.m_Active) { return; }

				// Move the component back into the active component map
				m_ComponentMaps[group]->
					insert({ id, m_DisabledComponentMaps[group]->at(id) });

				// Erase component from disabled map
				m_DisabledComponentMaps[group]->erase(id);

				// Tag component as active
				component.m_Active = true;

			}
			else
			{
				// Return if already disabled
				if (!component.m_Active) { return; }

				// Move the component to the disabled map
				m_DisabledComponentMaps[group]->
					insert({ id, m_ComponentMaps[group]->at(id) });

				// Remove the component from component maps
				m_ComponentMaps[group]->erase(id);

				// Tag component not active
				component.m_Active = false;
			}

		}
		else // If the entity is not active, we don't move the component but tag it correctly
		{
			if (setActive)
			{
				// Tag component as active
				component.m_Active = true;

			}
			else
			{
				// Tag component not active
				component.m_Active = false;
			}
		}
	}

	void gtk::Scene::ToggleRenderer(Renderer& renderer, bool setActive)
	{
		unsigned int id = renderer.ID();
		unsigned int layer = renderer.m_LayerID;

		// Does the id/entity even exist?
		ASSERT(m_EntityMap.find(id) != m_EntityMap.end());

		// Get entity
		Entity* entity = m_EntityMap.at(id);


		// If the entity is active we move the renderer between maps based on requested state
		if (entity->_Active)
		{
			if (setActive)
			{
				// Return if already active
				if (renderer.m_Active) { return; }

				// Move the renderer back into the active renderer map
				m_RendererMaps[layer]->
					insert({ id, m_DisabledRendererMaps[layer]->at(id) });

				// Erase renderer from disabled map
				m_DisabledRendererMaps[layer]->erase(id);

				// Tag renderer as active
				renderer.m_Active = true;

			}
			else
			{
				// Return if already disabled
				if (!renderer.m_Active) { return; }

				// Move the renderer to the disabled map
				m_DisabledRendererMaps[layer]->
					insert({ id, m_RendererMaps[layer]->at(id) });

				// Remove the renderer from renderer maps
				m_RendererMaps[layer]->erase(id);

				// Tag renderer not active
				renderer.m_Active = false;
			}

		}
		else // If the entity is not active, we don't move the renderer but tag it correctly
		{
			if (setActive)
			{
				// Tag renderer as active
				renderer.m_Active = true;

			}
			else
			{
				// Tag renderer not active
				renderer.m_Active = false;
			}
		}
	}

	void gtk::Scene::Update(float deltaTime)
	{
		//ASSERT(m_Cameras.size() > 0);

		// Loop through the vector of maps
		for (auto& CompMap : m_ComponentMaps)
		{
			// Loop through comp map
			for (auto& Comp : *CompMap)
			{
				Comp.second->Update(deltaTime);
			}
		}

		// Scene update accessible in derived class
		PostUpdate();

		// Updates all pos, rot, scale
		UpdateSceneGraph();

		// This deletes all components and moves to next scene
		// So it has to happen last
		if (m_SwitchScene)
		{
			m_Game.SwitchScene(m_NextScene);
		}

	}

	void gtk::Scene::Render(float width, float height)
	{

		// Calculate view and proj
		for (auto& cam : m_Cameras)
		{
			cam.second->CalculateView();
			cam.second->CalculateProj(width, height);
		}

		// Loop through the vector of maps
		for (auto& RenderLayer : m_RendererMaps)
		{
			// Loop through render map
			for (auto& Rend : *RenderLayer)
			{
				Rend.second->Draw();
			}
		}
	}

	void gtk::Scene::Shutdown()
	{

		// Loop through comp map vector
		for (auto& CompMap : m_ComponentMaps)
		{
			// Loop through comp map
			for (auto Comp : *CompMap)
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
			for (auto Comp : *CompMap)
			{
				// Delete each component
				delete Comp.second;
			}

			// Clear the map
			CompMap->clear();

			// Delete the map
			delete CompMap;

		} m_DisabledComponentMaps.clear(); // Clear the vector

		// Loop through renderer map vector
		for (auto& RendMap : m_RendererMaps)
		{
			// Loop through render map
			for (auto Rend : *RendMap)
			{
				// Delete each renderer
				delete Rend.second;
			}

			// Clear the map
			RendMap->clear();

			// Delete the map
			delete RendMap;

		} m_RendererMaps.clear(); // Clear the vector


		// Loop through disabled render map vector
		for (auto& RendMap : m_DisabledRendererMaps)
		{
			// Loop through rend map
			for (auto Rend : *RendMap)
			{
				// Delete each component
				delete Rend.second;
			}

			// Clear the map
			RendMap->clear();

			// Delete the map
			delete RendMap;

		} m_DisabledRendererMaps.clear(); // Clear the vector

		// Remove all entities
		for (auto Entity : m_EntityMap)
		{
			delete Entity.second;
		}
		m_EntityMap.clear();

		// Set switch scene flag back for next time
		m_SwitchScene = false;
		m_NextScene = "";

		// Remove children from root
		m_Root._Children.clear();

		// Reset id providers
		m_EntityIDProvider = 0;
		m_CompGroupIDProvider = 0;
		m_RenderLayerIDProvider = 0;
	}

	void gtk::Scene::UpdateSceneGraph()
	{
		// Traverse entities and update their TRS
		for (auto& child : m_Root._Children)
		{
			child->UpdateTRS();
		}

	}

	
}

