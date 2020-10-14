#pragma once

#include "Component.h"

#include <vector>
#include <unordered_map>

namespace gtk {

	class Entity;
	class Component;
	class ComponentGroup;
	class Renderer;

	class Scene {

		friend class Game;

	public:

		virtual ~Scene();

		Entity CreateEntity();
		ComponentGroup CreateComponenetGroup();

		void AddComponent(const Entity& entity, const ComponentGroup& group, Component* const component);
		void AddRenderer(const Entity& entity, Renderer* const renderer);

	protected:

		virtual void Init() = 0;

		std::vector<std::unordered_map<unsigned int, Component*>*> m_ComponentMaps;
	
	private:

		void Update();
		void Shutdown();

		unsigned int _EntityIDProvider = 0;
		unsigned int _ComponentGroupIDProvider = 0;

		std::unordered_map<unsigned int, bool> m_EntityMap;
		std::unordered_map<unsigned int, Renderer*> m_RendererMap;

	};
}