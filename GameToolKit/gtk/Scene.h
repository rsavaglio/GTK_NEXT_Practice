#pragma once

#include "gtk.h"

#include <vector>
#include <unordered_map>

namespace gtk {

	class Component;
	class Renderer;
	struct ComponentGroup;
	struct Entity;

	class Scene {

		friend class Game;

	public:

		// TODO
		virtual ~Scene();

		Entity CreateEntity();
		ComponentGroup CreateComponenetGroup();

		void AddComponent(const ComponentGroup& group, Component* const component);
		void AddRenderer(Renderer* const renderer);

	protected:

		// To be overriden in custom scenes
		// Used by game to start scenes
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