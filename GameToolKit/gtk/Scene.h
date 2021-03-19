#pragma once

#include "SceneObjects.h"

#include <vector>
#include <unordered_map>

namespace gtk {

	class Game;
	class SceneObject;
	class ObjectPool;

	class Entity;
	class Behavior;
	class UpdateGroup;
	class Renderer;
	class RenderLayer;
	class Collider;
	class CollisionGroup;
	class Camera;

	class Scene {

		// TODO: Needs to be refactored 
		// Sub systems for each component type
		// Or use a generic AddComponent function?

		

		friend class Game;

	public:

		// structors
		Scene(Game& game);
		virtual ~Scene();

		void SwitchScene(std::string key);

		// Toggles
		void ToggleEntity(Entity& entity, bool setActive);
		void ToggleBehavior(Behavior& behavior, bool setActive);
		void ToggleRenderer(Renderer& renderer, bool setActive);
		void ToggleCollider(Collider& collider, bool setActive);

		Camera& GetMainCam();

		
		// Creating Entities //
		Entity& CreateEntity();
		Entity& CreateEntity(Entity& parent);
		Entity& CreateEntity(std::string name);
		Entity& CreateEntity(std::string name, Entity& parent);
		
		ObjectPool& CreatePool(std::string name, ObjectPool* const pool);
		ObjectPool& GetPool(std::string name);

		UpdateGroup CreateUpdateGroup();
		RenderLayer CreateRenderLayer();
		CollisionGroup CreateCollisionGroup();

		Behavior& AddBehavior(Entity& entity, const UpdateGroup& group, Behavior* const behavior);
		Renderer& AddRenderer(Entity& entity, const RenderLayer& layer, Renderer* const renderer);
		Renderer& AddRenderer(Entity& entity, const RenderLayer& layer, Camera& camera, Renderer* const renderer);

		Camera& AddCamera(Entity& entity, Camera* const camera);

		Collider& AddCollider(Entity& entity, const CollisionGroup& group, Collider* const collider);

		void SetMainCam(const unsigned int& id);

		void TriggerBehaviours(const unsigned int& id, const int& code);
		void TriggerOnCollision(const unsigned int& id, Entity& other);
		void SetColourOnRenderer(const unsigned int& id, const vec3& color);


		const int& GetState();
		void SetState(const int& newState);


	protected:

		// Implemented in custom scene
		void Init();
		virtual void Setup() = 0;
		virtual void PostUpdate() = 0;

	protected:

		// Scene Object containers
		std::unordered_map<unsigned int, Entity*> m_RootEntityMap;

		std::vector<std::unordered_map<unsigned int, Behavior*>*> m_BehaviorMaps;
		std::vector<std::unordered_map<unsigned int, Renderer*>*> m_RendererMaps;

		std::vector<std::unordered_map<unsigned int, Collider*>*> m_ColliderMaps;
		std::vector<std::unordered_map<unsigned int, Collider*>*> m_DisabledColliderMaps;


		std::unordered_map<std::string, ObjectPool*> m_ObjectPools;

		std::unordered_map<unsigned int, Camera*> m_CameraMap;
		Camera* m_MainCam;
	
	private:

		void Update(const float& deltaTime);
		void Render(const float& width, const float& height);
		void Shutdown();

		void CheckCollision();

		// Traverse all entities and update TRS
		void UpdateSceneGraph();

		template <class T>
		void MapVectorShredder(std::vector<std::unordered_map<unsigned int, T*>*>& vectorMap);

		template <class T, class K>
		void MapShredder(std::unordered_map<K, T*>& map);

		void EntityShredder(Entity& entity);

	private:

		// Signals a scene change
		int m_SceneState;
		bool m_SwitchScene;
		std::string m_NextScene;
		Game& m_Game;

		const int MAX_ENTS;
		Entity* m_EntityPointerProvider;

		unsigned int m_EntityIDProvider;
		unsigned int m_UpdateGroupIDProvider;
		unsigned int m_RenderLayerIDProvider;
		unsigned int m_CollisionGroupIDProvider;


	};
}