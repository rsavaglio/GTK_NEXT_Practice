#pragma once

#include "gtk.h"

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
		
		virtual ~Component() = 0;

		virtual void Start() = 0;
		virtual void Update() = 0;

	};


	class Renderer
	{
	public:

		virtual ~Renderer() = 0;
		virtual void Draw() = 0;

	};

}