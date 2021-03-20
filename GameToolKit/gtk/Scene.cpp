#include "Scene.h"
#include "Game.h"

namespace gtk {

	Scene::Scene(Game& game)
		:m_SceneState(0), m_MainCam(nullptr),
		m_SwitchScene(false), m_NextScene(""),
		m_Game(game),
		MAX_ENTS(1000), m_EntityPointerProvider(nullptr),
		m_EntityIDProvider(0), m_UpdateGroupIDProvider(0), m_RenderLayerIDProvider(0), m_CollisionGroupIDProvider(0)
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

		//// Set up Cameras ////

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

		//// Start Calls ////

		// Call Start on enabled behaviours
		for (auto& BehMap : m_BehaviorMaps)
		{
			// Loop through behavior map
			for (auto& behavior : *BehMap)
			{
				behavior.second->Start();
			}
		}


		// Call Start on enabled renderer
		for (auto& RenMap : m_RendererMaps)
		{
			// Loop through behavior map
			for (auto& renderer : *RenMap)
			{
				renderer.second->Start();
			}
		}

		UpdateSceneGraph();

	}

	void Scene::SwitchScene(std::string key)
	{
		m_SwitchScene = true;
		m_NextScene = key;

		// Scene is switched after all comps are updated
		// Look in Scene::Update
	}


	//// TODO: Refactor create entities, too much duplication

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

	//// Object Pools

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

	
	//// Create Groups and Layers ////
	
	UpdateGroup Scene::CreateUpdateGroup()
	{
		m_BehaviorMaps.push_back(new std::unordered_map<unsigned int, Behavior*>);

		UpdateGroup newBehaviorGroup(m_UpdateGroupIDProvider++);

		return newBehaviorGroup;
	}

	RenderLayer Scene::CreateRenderLayer()
	{
		m_RendererMaps.push_back(new std::unordered_map<unsigned int, Renderer*>);

		RenderLayer newRenderLayer(m_RenderLayerIDProvider++);

		return newRenderLayer;
	}

	CollisionGroup Scene::CreateCollisionGroup()
	{
		m_ColliderMaps.push_back(new std::unordered_map<unsigned int, Collider*>);
		m_DisabledColliderMaps.push_back(new std::unordered_map<unsigned int, Collider*>);

		CollisionGroup newCollisionGroup(m_CollisionGroupIDProvider++);

		return newCollisionGroup;
	}



	//// Adding Componenets ////

	Behavior& Scene::AddBehavior(Entity& entity, const UpdateGroup& group, Behavior* const behavior)
	{
		// Set scene object data
		behavior->Init(entity._id, this, &entity);

		// Set behavior data
		behavior->m_GroupID = group._id;

		// Ensure no deplicate behaviors on same entity
		ASSERT(m_BehaviorMaps[group._id]->find(entity._id) == m_BehaviorMaps[group._id]->end());

		// Add behavior to correct map with the ID
		m_BehaviorMaps[group._id]->insert({ entity._id, behavior });

		return *behavior;
	}

	Renderer& Scene::AddRenderer(Entity& entity, const RenderLayer& layer, Camera& camera, Renderer* const renderer)
	{
		// Set scene object data
		renderer->Init(entity._id, this, &entity);

		// Set renderer data
		renderer->m_Camera = &camera;
		renderer->m_LayerID = layer._id;

		// Ensure no deplicate renderer on same entity
		ASSERT(m_RendererMaps[layer._id]->find(entity._id) == m_RendererMaps[layer._id]->end());
		m_RendererMaps[layer._id]->insert({ entity._id, renderer });

		return *renderer;
	}

	Renderer& Scene::AddRenderer(Entity& entity, const RenderLayer& layer, Renderer* const renderer)
	{
		// Set scene object data
		renderer->Init(entity._id, this, &entity);

		// Set renderer data, m_Camera is set in Scene::Init()
		renderer->m_LayerID = layer._id;

		// Ensure no deplicate renderer on same entity
		ASSERT(m_RendererMaps[layer._id]->find(entity._id) == m_RendererMaps[layer._id]->end());
		m_RendererMaps[layer._id]->insert({ entity._id, renderer });

		// Add renderer to correct map with the ID
		return *renderer;
	}


	Collider& Scene::AddCollider(Entity& entity, const CollisionGroup& group, Collider* const collider)
	{
		// Set scene object data
		collider->Init(entity._id, this, &entity);

		// Set collider data
		collider->m_GroupID = group._id;


		if (entity.Active()) // If entity is active
		{
			// Ensure no deplicate collider on same entity
			ASSERT(m_ColliderMaps[group._id]->find(entity._id) == m_ColliderMaps[group._id]->end());
			m_ColliderMaps[group._id]->insert({ entity._id, collider });
		}
		else
		{
			ASSERT(m_DisabledColliderMaps[group._id]->find(entity._id) == m_DisabledColliderMaps[group._id]->end());
			m_DisabledColliderMaps[group._id]->insert({ entity._id, collider });
		}

		// Add collider to correct map with the ID
		return *collider;
	}

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

	void gtk::Scene::SetColourOnRenderer(const unsigned int& id, const vec3& color)
	{
		// Check each map
		for (auto& CompMap : m_RendererMaps)
		{
			// If entity has a behviour in the map
			if (CompMap->find(id) != CompMap->end())
			{
				// Trigger the behaviour
				CompMap->at(id)->SetColor(color);
			}
		}
	}


	void gtk::Scene::TriggerOnCollision(const unsigned int& id, Entity& other)
	{
		// Check each map
		for (auto& CompMap : m_BehaviorMaps)
		{
			// If entity has a behviour in the map
			if (CompMap->find(id) != CompMap->end())
			{
				// Trigger the behaviour if it's active
				if(CompMap->at(id)->m_Active)
					CompMap->at(id)->OnCollision(other);
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
		// Tag behaviors and renderers
		//Move colliders between maps based on state

		// Loop though behavior maps
		for (unsigned int i = 0; i < m_BehaviorMaps.size(); i++) // Maps should be in the same order between vectors
		{
			// If entity has a behavior in this group
			if (m_BehaviorMaps[i]->find(entity._id) != m_BehaviorMaps[i]->end())
			{
				// Set it to active 
				m_BehaviorMaps[i]->at(entity._id)->m_Active = setActive;
			}

		}

		// Loop though renderer maps
		for (unsigned int i = 0; i < m_RendererMaps.size(); i++) // Maps should be in the same order between vectors
		{
			// If entity has a renderer in this layer
			if (m_RendererMaps[i]->find(entity._id) != m_RendererMaps[i]->end())
			{
				// Set it to active 
				m_RendererMaps[i]->at(entity._id)->m_Active = setActive;
			}

		}

		// Move colliders between maps 
		if (setActive)
		{
			// Return if entity is already active
			if (entity._Active) { return; }

			// Tag as active
			entity._Active = true;

			// Loop through disabled collider map vector
			for (unsigned int i = 0; i < m_DisabledColliderMaps.size(); i++) // Maps should be in the same order between vectors
			{
				// Does the entity have a collider in this layer?
				if (m_DisabledColliderMaps[i]->find(entity._id) != m_DisabledColliderMaps[i]->end())
				{
					// Collider is tagged as active
					if (m_DisabledColliderMaps[i]->at(entity._id)->m_Active)
					{
						// Move it to the active map
						m_ColliderMaps[i]->insert({ entity._id , m_DisabledColliderMaps[i]->at(entity._id) });

						// Erase from disabled map
						m_DisabledColliderMaps[i]->erase(entity._id);
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

			// Loop through active collider map vector
			for (unsigned int i = 0; i < m_ColliderMaps.size(); i++) // Maps should be in the same order between vectors
			{
				// Does the entity have a collider in this layer?
				if (m_ColliderMaps[i]->find(entity._id) != m_ColliderMaps[i]->end())
				{
					// Move it to the disabled map
					m_DisabledColliderMaps[i]->insert({ entity._id , m_ColliderMaps[i]->at(entity._id) });

					// Erase from active map
					m_ColliderMaps[i]->erase(entity._id);
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

	void gtk::Scene::ToggleRenderer(Renderer& renderer, bool setActive)
	{
		unsigned int id = renderer.ID();
		unsigned int group = renderer.m_LayerID;

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

	void gtk::Scene::ToggleCollider(Collider& collider, bool setActive)
	{
		unsigned int id = collider.ID();
		unsigned int layer = collider.m_GroupID;

		if (setActive)
		{
			// Return if already active
			if (collider.m_Active) { return; }

			// Move the collider back into the active collider map
			m_ColliderMaps[layer]->
				insert({ id, m_DisabledColliderMaps[layer]->at(id) });

			// Erase collider from disabled map
			m_DisabledColliderMaps[layer]->erase(id);

			// Tag collider as active
			collider.m_Active = true;

		}
		else
		{
			// Return if already disabled
			if (!collider.m_Active) { return; }

			// Move the collider to the disabled map
			m_DisabledColliderMaps[layer]->
				insert({ id, m_ColliderMaps[layer]->at(id) });

			// Remove the collider from collider maps
			m_ColliderMaps[layer]->erase(id);

			// Tag collider not active
			collider.m_Active = false;
		}
	}

	void gtk::Scene::Update(const float& deltaTime)
	{
			
		/// Update Behaviors ///

		for (auto& BehMap : m_BehaviorMaps)
		{
			// Loop through behavior map
			for (auto& behavior : *BehMap)
			{
				if (behavior.second->m_Active)
				{
					behavior.second->Update(deltaTime);
				}
			}
		}

		
		// Update Scene Graph
		UpdateSceneGraph();

		
		/// Collision ///
		
		// Update collision data
		for (auto& ColMap : m_ColliderMaps)
		{
			// Loop through behavior map
			for (auto& col : *ColMap)
			{
				col.second->UpdateData();
			}
		}
		CheckCollision();
		
		// Scene update accessible in derived class
		PostUpdate();

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
				if (Rend.second->m_Active)
				{
					Rend.second->Draw();
				}
			}
		}
	}

	void gtk::Scene::CheckCollision()
	{

		// For each collision group
		for (auto& ColGroup : m_ColliderMaps)
		{  
			// Check collision between all pairs
			for (auto& col1 : *ColGroup)
			{
				for (auto& col2 : *ColGroup)
				{
					if (col1 != col2) // Don't check self
					{
						if(col1.second->Check(*col2.second))
						{
							// Wow this is awful																		(but it works)
							col1.second->TriggerCollision(col2.second->GetEntity());
						}
					}
				}
			}
		}

			
	}

	void gtk::Scene::Shutdown()
	{
		// Shred map vectors
		MapVectorShredder(m_BehaviorMaps);

		MapVectorShredder(m_RendererMaps);

		MapVectorShredder(m_ColliderMaps);
		MapVectorShredder(m_DisabledColliderMaps);
		
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
		m_CollisionGroupIDProvider = 0;
		m_SceneState = 0;
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

