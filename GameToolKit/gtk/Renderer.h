#pragma once

namespace gtk {

	class Renderer
	{
	public:

		const unsigned int _id;

		Renderer(const Entity& entity) : _id(entity._id) {}
		virtual ~Renderer() {}

		virtual void Draw() {}

	};

}