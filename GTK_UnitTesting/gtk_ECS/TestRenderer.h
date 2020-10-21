#pragma once

#include "gtk/gtk.h"

class TestRenderer : public gtk::Renderer
{

public:

	TestRenderer(gtk::Entity* const entity) : Renderer(entity) {}

	void Draw() override
	{
		// Draw stuff
	}

};