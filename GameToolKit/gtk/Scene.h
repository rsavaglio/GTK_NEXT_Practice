#pragma once

#include "SceneObjects.h"

#include <vector>
#include <unordered_map>

namespace gtk {

	class Game;
	class SceneObject;

	class Entity;
	class Behavior;
	class UpdateGroup;
	class Renderer;
	class RenderLayer;
	class Camera;

	class Scene {

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

		Camera& GetMainCam();

		//Entity& GetEntity(unsigned int id);

	protected:

		// Implemented in custom scene
		void Init();
		virtual void Setup() = 0;
		virtual void PostUpdate() = 0;

		// Scene setup functions

		UpdateGroup CreateUpdateGroup();
		RenderLayer CreateRenderLayer();

		Entity& CreateEntity(); // Sets parent as m_Root
		Entity& CreateEntity(Entity& parent);

		Behavior& AddBehavior(Entity& entity, const UpdateGroup& group, Behavior* const behavior);

		Renderer& AddRenderer(Entity& entity, const RenderLayer& layer, Renderer* const renderer);
		Renderer& AddRenderer(Entity& entity, const RenderLayer& layer, const Camera& camera, Renderer* const renderer);

		Camera& AddCamera(Entity& entity, Camera* const camera);

		void SetMainCam(unsigned int id);


	protected:

		// Scene Object containers
		std::unordered_map<unsigned int, Entity*> m_RootEntityMap;

		std::vector<std::unordered_map<unsigned int, Behavior*>*> m_BehaviorMaps;
		std::vector<std::unordered_map<unsigned int, Behavior*>*> m_DisabledBehaviorMaps;

		std::vector<std::unordered_map<unsigned int, Renderer*>*> m_RendererMaps;
		std::vector<std::unordered_map<unsigned int, Renderer*>*> m_DisabledRendererMaps;

		std::unordered_map<unsigned int, Camera*> m_CameraMap;
		Camera* m_MainCam;
	
	private:

		void Update(const float& deltaTime);
		void Render(const float& width, const float& height);
		void Shutdown();

		// Traverse all entities and update TRS
		void UpdateSceneGraph();

		template <class T>
		void MapVectorShredder(std::vector<std::unordered_map<unsigned int, T*>*>& vectorMap);

		template <class T>
		void MapShredder(std::unordered_map<unsigned int, T*>& map);

		void EntityShredder(Entity& entity);

	private:

		// Signals a scene change
		bool m_SwitchScene;
		std::string m_NextScene;
		Game& m_Game;

		const int MAX_ENTS;
		Entity* m_EntityPointerProvider;


		unsigned int m_EntityIDProvider;
		unsigned int m_UpdateGroupIDProvider;
		unsigned int m_RenderLayerIDProvider;

	};
}