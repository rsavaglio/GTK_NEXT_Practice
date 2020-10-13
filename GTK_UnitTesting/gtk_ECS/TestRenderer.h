#pragma once

#include "gtk/gtk.h"

class TestRenderer : public gtk::Renderer
{

public:

	unsigned int _id;

	TestRenderer(const gtk::Entity& entity) : _id(entity._id)
	{

	}

	void Draw() override
	{
		// Draw stuff
	}
};