#pragma once

#include "Game.h"
#include "Component.h"
#include "Entity.h"
#include "Camera.h"

#include <vector>
#include <unordered_map>

namespace gtk {

	class Entity;
	class Component;
	class CompGroup;
	class Renderer;
	class RenderLayer;
	class Game;
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
		void ToggleComponent(Component& component, bool setActive);
		void ToggleRenderer(Renderer& renderer, bool setActive);

		Camera& GetMainCam();

		Entity& GetEntity(unsigned int id);

	protected:

		// Implemented in custom scene
		virtual void Init() = 0;
		virtual void PostUpdate() = 0;

		// Scene setup functions

		CompGroup CreateCompGroup();
		RenderLayer CreateRenderLayer();

		Entity& CreateEntity(); // Sets parent as m_Root
		Entity& CreateEntity(Entity& parent);

		Component& AddComponent(Entity& entity, const CompGroup& group, Component* const component);

		Renderer& AddRenderer(Entity& entity, const RenderLayer& layer, Renderer* const renderer);
		Renderer& AddRenderer(Entity& entity, const RenderLayer& layer, const Camera& camera, Renderer* const renderer);

		Camera& AddCamera(Entity& entity, Camera* const camera);

		void SetMainCam(unsigned int id);


	protected:

		// Scene Object containers
		std::unordered_map<unsigned int, Entity*> m_EntityMap;

		std::vector<std::unordered_map<unsigned int, Component*>*> m_ComponentMaps;
		std::vector<std::unordered_map<unsigned int, Component*>*> m_DisabledComponentMaps;

		std::vector<std::unordered_map<unsigned int, Renderer*>*> m_RendererMaps;
		std::vector<std::unordered_map<unsigned int, Renderer*>*> m_DisabledRendererMaps;

		std::unordered_map<unsigned int, Camera*> m_Cameras;
		Camera* m_MainCam;
	
	private:

		void Update(float deltaTime);
		void Render(float width, float height);
		void Shutdown();

		// Traverse all entities
		// Updates transforms
		void UpdateSceneGraph();

	private:

		// Signals a scene change
		bool m_SwitchScene;
		std::string m_NextScene;
		Game& m_Game;

		// Scene graph root
		Entity m_Root;

		unsigned int m_EntityIDProvider;
		unsigned int m_CompGroupIDProvider;
		unsigned int m_RenderLayerIDProvider;

	};
}