#pragma once

namespace gtk {

	class Renderer
	{
	public:

		const unsigned int _id;

		Renderer(const int& id) : _id(id) {}
		virtual ~Renderer() {}

		virtual void Draw() {}

	};

}