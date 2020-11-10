#pragma once

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

	class Scene {

		friend class Game;

	public:
		
		// structors
		Scene(Game* const game);
		virtual ~Scene();

		void SwitchScene(std::string key);

		// Toggles
		void ToggleEntity(Entity* const entity, bool setActive);
		void ToggleComponent(Component* const component, bool setActive);
		void ToggleRenderer(Renderer* const renderer, bool setActive);

	public: 

		Camera m_Camera;

	protected:

		// Implemented in custom scene
		virtual void Init() = 0;
		virtual void PostUpdate() = 0;

		// Scene setup functions

		CompGroup CreateCompGroup();
		// TODO: CreateRenderLayer();

		Entity* CreateEntity(); // Sets parent as m_Root
		Entity* CreateEntity(Entity* const parent);

		Component* const AddComponent(Component* const component);
		Renderer* const AddRenderer(Renderer* const renderer);
		

	protected:

		// Scene Object containers
		std::unordered_map<unsigned int, Entity*> m_EntityMap;
		
		std::vector<std::unordered_map<unsigned int, Component*>*> m_ComponentMaps;
		std::unordered_map<unsigned int, Renderer*> m_RendererMap;

		std::vector<std::unordered_map<unsigned int, Component*>*> m_DisabledComponentMaps;
		std::unordered_map<unsigned int, Renderer*> m_DisabledRenderers;
	
	private:

		void Update(float deltaTime);
		void Render();
		void Shutdown();

		// Traverse all entities
		// Updates transforms
		void UpdateSceneGraph();

	private:

		// Signals a scene change
		bool m_SwitchScene;
		std::string m_NextScene;
		Game* const m_Game;

		// Scene graph root
		Entity* const m_Root;
		

		unsigned int m_EntityIDProvider;
		unsigned int m_CompGroupIDProvider;

	};
}