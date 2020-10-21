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
		
		Scene();
		virtual ~Scene();

	protected:

		virtual void Init() = 0;

		Entity* CreateEntity();
		Entity* CreateEntity(Entity* const parent);
		CompGroup CreateCompGroup();

		void AddComponent(Component* const component);
		void AddRenderer(Renderer* const renderer);

		std::vector<std::unordered_map<unsigned int, Component*>*> m_ComponentMaps;
	
	private:

		void Update();
		void Shutdown();

		Entity* m_Root;

		unsigned int _EntityIDProvider = 0;
		unsigned int _CompGroupIDProvider = 0;

		std::unordered_map<unsigned int, Entity*> m_EntityMap;
		std::unordered_map<unsigned int, Renderer*> m_RendererMap;

		std::unordered_map<unsigned int, Component*> m_DisabledComponents;
		std::unordered_map<unsigned int, Renderer*> m_DisabledRenderers;


	};
}