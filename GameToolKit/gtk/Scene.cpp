#include "Scene.h"

#include "Game.h"

namespace gtk {

	Scene::Scene(Game& game)
		:m_MainCam(nullptr),
		m_SwitchScene(false), m_NextScene(""),
		m_Game(game),
		m_EntityIDProvider(0), m_RenderLayerIDProvider(0)
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

		// Scene is switched after all comps are updated
		// Look in Scene::Update
	}

	Entity& Scene::CreateEntity()
	{
		Entity* newEnt = new Entity(nullptr, *this);

		newEnt->Init(this, newEnt);

		// Add entity to the map, set as active, set root as parent
		m_RootEntities.push_back(newEnt);

		// Return id and increment
		return *newEnt;
	}

	Entity& Scene::CreateEntity(Entity& parent)
	{
		// Create a new entity
		Entity* newEnt = new Entity(&parent, *this);

		// Add it to the parent's list of children
		parent.AddChild(newEnt);

		// Return ref and increment
		return *newEnt;
	}

	RenderLayer Scene::CreateRenderLayer()
	{
		m_RendererMaps.push_back(new std::vector<Renderer*>);

		RenderLayer newRenderLayer(m_RenderLayerIDProvider++);

		return newRenderLayer;
	}

	Behavior& Scene::AddBehavior(Entity& entity, Behavior* const behavior)
	{
		// Set scene object data
		behavior->Init(this, &entity);

		// Add behavior to correct map with the ID
		m_Behaviors.push_back(behavior);

		return *behavior;
	}

	Renderer& Scene::AddRenderer(Entity& entity, const RenderLayer& layer, const Camera& camera, Renderer* const renderer)
	{
		// Set scene object data
		renderer->Init(this, &entity);

		// Set renderer data
		renderer->m_Camera = &camera;
		renderer->m_LayerID = layer._id;

		// Add renderer to correct vector with the ID
		m_RendererMaps[layer._id]->push_back(renderer);

		return *renderer;
	}

	Renderer& Scene::AddRenderer(Entity& entity, const RenderLayer& layer, Renderer* const renderer)
	{
		// Set scene object data
		renderer->Init(this, &entity);

		// Set renderer data
		renderer->m_Camera = m_MainCam;
		renderer->m_LayerID = layer._id;

		// Add renderer to correct vector with the ID
		m_RendererMaps[layer._id]->push_back(renderer);

		return *renderer;
	}

	// TODO: Make sure this works with m_MainCam correctly
	Camera& Scene::AddCamera(Entity& entity, Camera* const camera)
	{
		// Set scene object data
		camera->Init(this, &entity);

		// If first camera
		if (m_Cameras.size() == 0)
		{
			m_MainCam = camera;
		}

		// Add camera to map
		m_Cameras.push_back(camera);

		return *camera;
	}

	void Scene::SetMainCam(Camera& camera) 
	{
		m_MainCam = &camera;
	}

	Camera& Scene::GetMainCam()
	{
		return *m_MainCam;
	}


	void gtk::Scene::Update(const float& deltaTime)
	{

		// TODO: Ensure a camera exists
		//ASSERT(m_Cameras.size() > 0);

		// Loop through the behaviors
		for (auto& behavior : m_Behaviors)
		{
			if (behavior->Active())
			{
				behavior->Update(deltaTime);
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
		for (auto& cam : m_Cameras)
		{
			cam->CalculateView();
			cam->CalculateProj(width, height);
		}

		// Loop through the vector of maps
		for (auto& RenderLayer : m_RendererMaps)
		{
			// Loop through render map
			for (auto& rend : *RenderLayer)
			{
				if (rend->Active())
				{
					rend->Draw();
				}
				
			}
		}
	}

	void gtk::Scene::Shutdown()
	{
		// Delete all scene objects

		VectorShredder(m_Behaviors);


		for (auto& layer : m_RendererMaps)
		{
			VectorShredder(*layer);
		} 
		
		m_RendererMaps.clear();
	
		VectorShredder(m_Cameras);

		// Clear Entity Scene Graph
		for (auto& child : m_RootEntities)
		{
			EntityShredder(*child);
		}
		
		m_RootEntities.clear();

		// Set switch scene flag back for next time
		m_SwitchScene = false;
		m_NextScene = "";

		// Reset id providers
		m_EntityIDProvider = 0;
		m_RenderLayerIDProvider = 0;
	}

	void gtk::Scene::UpdateSceneGraph()
	{
		// Traverse entities and update their TRS
		for (auto& child : m_RootEntities)
		{
			child->UpdateRootTRS();
		}

	}

	template <class T>
	void Scene::VectorShredder(std::vector< T*>& vector)
	{
		// Loop through map
		for (auto obj : vector)
		{
			// Delete each object
			delete obj;
		}
		vector.clear();
	}

	void Scene::EntityShredder(Entity& entity)
	{
		for (auto& child : entity._Children)
		{
			EntityShredder(*child);

		}
	}

	
}

