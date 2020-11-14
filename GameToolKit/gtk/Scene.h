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

		Camera& GetMainCam();

	protected:

		// Implemented in custom scene
		virtual void Init() = 0;
		virtual void PostUpdate() = 0;

		// Scene setup functions

		RenderLayer CreateRenderLayer();

		Entity& CreateEntity(); // Sets parent as m_Root
		Entity& CreateEntity(Entity& parent);

		Behavior& AddBehavior(Entity& entity, Behavior* const behavior);

		Renderer& AddRenderer(Entity& entity, const RenderLayer& layer, Renderer* const renderer);
		Renderer& AddRenderer(Entity& entity, const RenderLayer& layer, const Camera& camera, Renderer* const renderer);

		Camera& AddCamera(Entity& entity, Camera* const camera);

		void SetMainCam(Camera& camera);


	protected:

		// Scene Object containers
		std::vector<Entity*> m_RootEntities;

		std::vector<Behavior*> m_Behaviors;

		std::vector<std::vector<Renderer*>*> m_RendererMaps;

		std::vector<Camera*> m_Cameras;
		Camera* m_MainCam;
	
	private:

		void Update(const float& deltaTime);
		void Render(const float& width, const float& height);
		void Shutdown();

		// Traverse all entities and update TRS
		void UpdateSceneGraph();

		template <class T>
		void VectorShredder(std::vector< T*>& vector);

		void EntityShredder(Entity& entity);

	private:

		// Signals a scene change
		bool m_SwitchScene;
		std::string m_NextScene;
		Game& m_Game;

		unsigned int m_EntityIDProvider;
		unsigned int m_RenderLayerIDProvider;

	};
}