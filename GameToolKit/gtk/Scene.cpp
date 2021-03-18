#include "Scene.h"

#include "Game.h"

namespace gtk {

	Scene::Scene(Game& game)
		:m_SceneState(0), m_MainCam(nullptr),
		m_SwitchScene(false), m_NextScene(""),
		m_Game(game),
		MAX_ENTS(100), m_EntityPointerProvider(nullptr),
		m_EntityIDProvider(0), m_UpdateGroupIDProvider(0), m_RenderLayerIDProvider(0)
	{
	}

	Scene::~Scene()
	{
		Shutdown();
	}

	void Scene::Init()
	{
		m_EntityPointerProvider = new Entity[MAX_ENTS];

		Setup();

		ASSERT(m_CameraMap.size() > 0);

		// Loop through the vector of maps
		for (auto& RenderLayer : m_RendererMaps)
		{
			// Loop through render map
			for (auto& Rend : *RenderLayer)
			{
				// If the renderer has not been given a camera
				if (Rend.second->m_Camera == nullptr)
				{
					// Give it the main camera
					Rend.second->m_Camera = m_MainCam;
				}
			}
		}

		// Loop through the vector of maps
		for (auto& RenderLayer : m_DisabledRendererMaps)
		{
			// Loop through render map
			for (auto& Rend : *RenderLayer)
			{
				// If the renderer has not been given a camera
				if (Rend.second->m_Camera == nullptr)
				{
					// Give it the main camera
					Rend.second->m_Camera = m_MainCam;
				}
			}
		}

	}

	void Scene::SwitchScene(std::string key)
	{
		m_SwitchScene = true;
		m_NextScene = key;

		// Scene is switched after all comps are updated
		// Look in Scene::Update
	}

	Entity& Scene::CreateEntity()
	{
		Entity* newEnt = m_EntityPointerProvider + m_EntityIDProvider;

		newEnt->Init(m_EntityIDProvider, this, newEnt);
		newEnt->_Parent = newEnt;

		// Add entity to the map, set as active, set self as parent
		m_RootEntityMap.insert({ m_EntityIDProvider++, newEnt });

		// Return id and increment
		return *newEnt;
	}

	Entity& Scene::CreateEntity(Entity& parent)
	{
		// Add entity to the map, set as active
		Entity* newEnt = m_EntityPointerProvider + m_EntityIDProvider;

		newEnt->Init(m_EntityIDProvider++, this, newEnt);
		newEnt->_Parent = &parent;

		// Add this to parent's list of children
		parent.AddChild(newEnt);

		// Return id and increment
		return *newEnt;
	}

	Entity& Scene::CreateEntity(std::string name)
	{
		Entity* newEnt = m_EntityPointerProvider + m_EntityIDProvider;

		newEnt->Init(m_EntityIDProvider, this, newEnt);
		newEnt->_Parent = newEnt;
		newEnt->_Name = name;


		// Add entity to the map, set as active, set root as parent
		m_RootEntityMap.insert({ m_EntityIDProvider++, newEnt });

		// Return id and increment
		return *newEnt;
	}

	Entity& Scene::CreateEntity(std::string name, Entity& parent)
	{
		// Add entity to the map, set as active
		Entity* newEnt = m_EntityPointerProvider + m_EntityIDProvider;

		newEnt->Init(m_EntityIDProvider++, this, newEnt);
		newEnt->_Parent = &parent;
		newEnt->_Name = name;

		// Add this to parent's list of children
		parent.AddChild(newEnt);

		// Return id and increment
		return *newEnt;
	}

	ObjectPool& Scene::CreatePool(std::string name, ObjectPool* const pool)
	{
		m_ObjectPools.insert({ name, pool });
		return *pool;
	}

	ObjectPool& Scene::GetPool(std::string name)
	{
		ASSERT(m_ObjectPools.find(name) != m_ObjectPools.end());
		return *m_ObjectPools.at(name);
	}
	
	UpdateGroup Scene::CreateUpdateGroup()
	{
		m_BehaviorMaps.push_back(new std::unordered_map<unsigned int, Behavior*>);
		m_DisabledBehaviorMaps.push_back(new std::unordered_map<unsigned int, Behavior*>);

		UpdateGroup newBehaviorGroup(m_UpdateGroupIDProvider++);

		return newBehaviorGroup;
	}

	RenderLayer Scene::CreateRenderLayer()
	{
		m_RendererMaps.push_back(new std::unordered_map<unsigned int, Renderer*>);
		m_DisabledRendererMaps.push_back(new std::unordered_map<unsigned int, Renderer*>);

		RenderLayer newRenderLayer(m_RenderLayerIDProvider++);

		return newRenderLayer;
	}

	Behavior& Scene::AddBehavior(Entity& entity, const UpdateGroup& group, Behavior* const behavior)
	{
		// Set scene object data
		behavior->Init(entity._id, this, &entity);

		// Set behavior data
		behavior->m_GroupID = group._id;

		if (entity.Active())
		{
			// Ensure no deplicate behaviors on same entity
			ASSERT(m_BehaviorMaps[group._id]->find(entity._id) == m_BehaviorMaps[group._id]->end());

			// Add behavior to correct map with the ID
			m_BehaviorMaps[group._id]->insert({ entity._id, behavior });
		}
		else
		{
			ASSERT(m_DisabledBehaviorMaps[group._id]->find(entity._id) == m_DisabledBehaviorMaps[group._id]->end());
			m_DisabledBehaviorMaps[group._id]->insert({ entity._id, behavior });
		}

		return *behavior;
	}

	Renderer& Scene::AddRenderer(Entity& entity, const RenderLayer& layer, Camera& camera, Renderer* const renderer)
	{
		// Set scene object data
		renderer->Init(entity._id, this, &entity);

		// Set renderer data
		renderer->m_Camera = &camera;
		renderer->m_LayerID = layer._id;


		if (entity.Active())
		{
			// Ensure no deplicate renderer on same entity
			ASSERT(m_RendererMaps[layer._id]->find(entity._id) == m_RendererMaps[layer._id]->end());
			m_RendererMaps[layer._id]->insert({ entity._id, renderer });
		}
		else
		{
			ASSERT(m_DisabledRendererMaps[layer._id]->find(entity._id) == m_DisabledRendererMaps[layer._id]->end());
			m_DisabledRendererMaps[layer._id]->insert({ entity._id, renderer });
		}

		// Add renderer to correct map with the ID
		m_RendererMaps[layer._id]->insert({ entity._id, renderer });

		return *renderer;
	}

	Renderer& Scene::AddRenderer(Entity& entity, const RenderLayer& layer, Renderer* const renderer)
	{
		// Set scene object data
		renderer->Init(entity._id, this, &entity);

		// Set renderer data, m_Camera is set in Scene::Init()
		renderer->m_LayerID = layer._id;


		if (entity.Active())
		{
			// Ensure no deplicate renderer on same entity
			ASSERT(m_RendererMaps[layer._id]->find(entity._id) == m_RendererMaps[layer._id]->end());
			m_RendererMaps[layer._id]->insert({ entity._id, renderer });
		}
		else
		{
			ASSERT(m_DisabledRendererMaps[layer._id]->find(entity._id) == m_DisabledRendererMaps[layer._id]->end());
			m_DisabledRendererMaps[layer._id]->insert({ entity._id, renderer });
		}

		// Add renderer to correct map with the ID
		return *renderer;
	}

	// TODO: Make sure this works with m_MainCam correctly
	Camera& Scene::AddCamera(Entity& entity, Camera* const camera)
	{
		// Set scene object data
		camera->Init(entity._id, this, &entity);

		// If first camera
		if (m_CameraMap.size() == 0)
		{
			m_MainCam = camera;
		}
		// Only one camera per entity
		else 
		{
			ASSERT(m_CameraMap.find(entity._id) == m_CameraMap.end());
		}

		// Add camera to map
		m_CameraMap.insert({ entity._id, camera });

		return *camera;
	}

	void Scene::SetMainCam(const unsigned int& id) 
	{
		ASSERT(m_CameraMap.find(id) != m_CameraMap.end());

		m_MainCam = m_CameraMap.find(id)->second;
	}

	void gtk::Scene::TriggerBehaviours(const unsigned int& id, const int& code)
	{
		// Check each map
		for (auto& CompMap : m_BehaviorMaps)
		{
			// If entity has a behviour in the map
			if (CompMap->find(id) != CompMap->end())
			{
				// Trigger the behaviour
				CompMap->at(id)->Trigger(code);
			}
		}
	}

	const int& gtk::Scene::GetState()
	{
		return m_SceneState;
	}

	void gtk::Scene::SetState(const int& newState)
	{
		m_SceneState = newState;
	}

	Camera& Scene::GetMainCam()
	{
		return *m_MainCam;
	}

	void gtk::Scene::ToggleEntity(Entity& entity, bool setActive)
	{
		// Update is only called on components and renderers in the active maps.
		// Disabled components and renderers are moved to disabled maps, where they are not updated.
		// This avoids having to check each if component is active each time they are updated. 

		// Disabling an entity essentially just disables all of its components.
		// However, components' active tags are preserved.

		// When setting an entity to active, only components tagged as active get moved
		// to the active maps.

		if (setActive)
		{
			// Return if entity is already active
			if (entity._Active) { return; }

			// Tag as active
			entity._Active = true;

			// Loop through disabled map vector
			for (unsigned int i = 0; i < m_DisabledBehaviorMaps.size(); i++) // Maps should be in the same order between vectors
			{
				// Does the entity have a behavior in this group?
				if (m_DisabledBehaviorMaps[i]->find(entity._id) != m_DisabledBehaviorMaps[i]->end())
				{
					// Behavior is tagged as active
					if (m_DisabledBehaviorMaps[i]->at(entity._id)->m_Active)
					{
						// Move it to the active map
						m_BehaviorMaps[i]->insert({ entity._id , m_DisabledBehaviorMaps[i]->at(entity._id) });

						// Erase from disabled map
						m_DisabledBehaviorMaps[i]->erase(entity._id);
					}
				}
			}


			// Loop through disabled map vector
			for (unsigned int i = 0; i < m_DisabledRendererMaps.size(); i++) // Maps should be in the same order between vectors
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
		else // Set entity inactive
		{
			// Return if entity is already inactive
			if (!entity._Active) { return; }

			// Tag as inactive
			entity._Active = false;

			// Loop through active behavior map vector
			for (unsigned int i = 0; i < m_BehaviorMaps.size(); i++) // Maps should be in the same order between vectors
			{
				// Does the entity have a behavior in this group?
				if (m_BehaviorMaps[i]->find(entity._id) != m_BehaviorMaps[i]->end())
				{
					// Move it to the disabled map
					m_DisabledBehaviorMaps[i]->insert({ entity._id , m_BehaviorMaps[i]->at(entity._id) });

					// Erase from active map
					m_BehaviorMaps[i]->erase(entity._id);
				}
			}

			// Loop through active renderer map vector
			for (unsigned int i = 0; i < m_RendererMaps.size(); i++) // Maps should be in the same order between vectors
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

		// Repeat on children
		for (auto& child : entity._Children)
		{
			ToggleEntity(*child, setActive);
		}
	}

	void gtk::Scene::ToggleBehavior(Behavior& behavior, bool setActive)
	{
		unsigned int id = behavior.ID();
		unsigned int group = behavior.m_GroupID;

		// Get entity
		Entity& entity = behavior.GetEntity();

		// If the entity is active we move the behavior between maps based on requested state
		if (entity._Active)
		{

			if (setActive)
			{
				// Return if already active
				if (behavior.m_Active) { return; }

				// Move the behavior back into the active behavior map
				m_BehaviorMaps[group]->
					insert({ id, m_DisabledBehaviorMaps[group]->at(id) });

				// Erase behavior from disabled map
				m_DisabledBehaviorMaps[group]->erase(id);

				// Tag behavior as active
				behavior.m_Active = true;

			}
			else
			{
				// Return if already disabled
				if (!behavior.m_Active) { return; }

				// Move the behavior to the disabled map
				m_DisabledBehaviorMaps[group]->
					insert({ id, m_BehaviorMaps[group]->at(id) });

				// Remove the behavior from behavior maps
				m_BehaviorMaps[group]->erase(id);

				// Tag behavior not active
				behavior.m_Active = false;
			}

		}
		else // If the entity is not active, we don't move the behavior but tag it correctly
		{
			if (setActive)
			{
				// Tag behavior as active
				behavior.m_Active = true;

			}
			else
			{
				// Tag behavior not active
				behavior.m_Active = false;
			}
		}
	}

	void gtk::Scene::ToggleRenderer(Renderer& renderer, bool setActive)
	{
		unsigned int id = renderer.ID();
		unsigned int layer = renderer.m_LayerID;

		// Get entity
		Entity& entity = renderer.GetEntity();


		// If the entity is active we move the renderer between maps based on requested state
		if (entity._Active)
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

	void gtk::Scene::Update(const float& deltaTime)
	{

		// Loop through the vector of maps
		for (auto& BehMap : m_BehaviorMaps)
		{
			// Loop through behavior map
			for (auto& behavior : *BehMap)
			{
				behavior.second->Update(deltaTime);
			}
		}

		// Scene update accessible in derived class
		PostUpdate();

		// Updates all pos, rot, scale
		UpdateSceneGraph();

		// This deletes all behaviors and moves to next scene
		// So it has to happen last
		if (m_SwitchScene)
		{
			m_Game.SwitchScene(m_NextScene);
		}

	}

	void gtk::Scene::Render(const float& width, const float& height)
	{
		// Calculate view and proj
		for (auto& cam : m_CameraMap)
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
		// Shred map vectors
		MapVectorShredder(m_BehaviorMaps);
		MapVectorShredder(m_DisabledBehaviorMaps);

		MapVectorShredder(m_RendererMaps);
		MapVectorShredder(m_DisabledRendererMaps);
		
		// Shred maps
		MapShredder(m_CameraMap);
		MapShredder(m_ObjectPools);

		// Clear Entity Scene Graph
		delete[] m_EntityPointerProvider;
		m_RootEntityMap.clear();

		// Set switch scene flag back for next time
		m_SwitchScene = false;
		m_NextScene = "";

		// Reset id providers
		m_EntityIDProvider = 0;
		m_UpdateGroupIDProvider = 0;
		m_RenderLayerIDProvider = 0;
	}

	void gtk::Scene::UpdateSceneGraph()
	{
		// Traverse entities and update their TRS
		for (auto& child : m_RootEntityMap)
		{
			child.second->UpdateRootTRS();
		}

	}

	template <class T>
	void Scene::MapVectorShredder(std::vector<std::unordered_map<unsigned int, T*>*>& mapVector)
	{
		// Loop through map vector
		for (auto& CompMap : mapVector)
		{
			// Loop through map
			for (auto comp : *CompMap)
			{
				// Delete each component
				delete comp.second;
			}

			// Clear the map
			CompMap->clear();

			// Delete the map
			delete CompMap;

		}
		
		mapVector.clear(); // Clear the vector
	}

	template <class T, class K>
	void Scene::MapShredder(std::unordered_map<K, T*>& map)
	{
		// Loop through map
		for (auto obj : map)
		{
			// Delete each object
			delete obj.second;
		}
		map.clear();
	}

	void Scene::EntityShredder(Entity& entity)
	{
		for (auto& child : entity._Children)
		{
			EntityShredder(*child);

		}
	}

	
}

