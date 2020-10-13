#pragma once

#include "gtk.h"

namespace gtk {
	
	struct Entity;

	class Renderer
	{
	public:

		const unsigned int _id;

		Renderer(const Entity& entity);

		virtual ~Renderer() {}
		virtual void Draw() = 0;

	};

}