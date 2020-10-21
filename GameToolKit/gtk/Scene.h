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

		virtual ~Scene();

	protected:

		virtual void Init() = 0;

		Entity CreateEntity();
		CompGroup CreateCompGroup();

		void AddComponent(Component* const component);
		void AddRenderer(const Entity& entity, Renderer* const renderer);

		std::vector<std::unordered_map<unsigned int, Component*>*> m_ComponentMaps;
	
	private:

		void Update();
		void Shutdown();

		unsigned int _EntityIDProvider = 0;
		unsigned int _CompGroupIDProvider = 0;

		std::unordered_map<unsigned int, Entity*> m_EntityMap;
		std::unordered_map<unsigned int, Renderer*> m_RendererMap;

	};
}