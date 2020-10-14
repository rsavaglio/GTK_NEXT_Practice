#pragma once

#include "gtk.h"

namespace gtk {


	class Entity
	{
		friend class Scene;

	public:
		unsigned int _id;

	private:

		// Call CreateEntity() from a Scene
		Entity(const unsigned int& id);
	};

	class ComponentGroup
	{
		friend class Scene;

	public:
		unsigned int _id;

	private:

		// Call CreateComponentGroup() from a Scene
		ComponentGroup(const unsigned int& id);
	};

	class Component
	{
	public:

		virtual ~Component() {}

		virtual void Start() = 0;
		virtual void Update() = 0;

	};


	class Renderer
	{
	public:

		virtual ~Renderer() {}
		virtual void Draw() = 0;

	};

}