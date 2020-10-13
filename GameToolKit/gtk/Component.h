#pragma once

#include "gtk.h"
#include "Scene.h"

namespace gtk {


	struct Entity
	{
		Entity(const unsigned int& id) : _id(id) {}

		unsigned int _id;
	};

	struct ComponentGroup
	{
		ComponentGroup(const unsigned int& id) : _id(id) {}

		unsigned int _id;
	};

	class Component
	{
	public:

		const unsigned int _id;

		Component(const Entity& entity);
		
		// Might be able to make this pure virtual
		virtual ~Component() {}

		virtual void Start() = 0;
		virtual void Update() = 0;

	};
}