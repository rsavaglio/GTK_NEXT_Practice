#pragma once

#include "Component.h"

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
		
		Scene(Game* const game);
		virtual ~Scene();

		void SwitchScene(std::string key);

		void ToggleEntity(Entity* const entity, bool setActive);
		void ToggleComponent(Component* const component, bool setActive);
		void ToggleRenderer(Renderer* const renderer, bool setActive);

	protected:

		virtual void Init() = 0;
		virtual void PostUpdate() = 0;

		Entity* CreateEntity(); // Sets parent as m_Root
		Entity* CreateEntity(Entity* const parent);
		CompGroup CreateCompGroup();

		Component* const AddComponent(Component* const component);
		Renderer* const AddRenderer(Renderer* const renderer);

		std::vector<std::unordered_map<unsigned int, Component*>*> m_ComponentMaps;
	
	private:

		void Update(float deltaTime);
		void Render();
		void Shutdown();

		bool m_SwitchScene;
		std::string m_NextScene;

		Game* const m_Game;
		Entity* const m_Root;

		unsigned int m_EntityIDProvider;
		unsigned int m_CompGroupIDProvider;

		std::unordered_map<unsigned int, Entity*> m_EntityMap;
		std::unordered_map<unsigned int, Renderer*> m_RendererMap;

		std::vector<std::unordered_map<unsigned int, Component*>*> m_DisabledComponentMaps;
		std::unordered_map<unsigned int, Renderer*> m_DisabledRenderers;


	};
}