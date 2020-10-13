#pragma once

#include "gtk/gtk.h"

class TestRenderer : public gtk::Renderer
{

public:

	TestRenderer(const gtk::Entity& entity) : Renderer(entity)
	{

	}

	void Draw() override
	{
		// Draw stuff
	}
};