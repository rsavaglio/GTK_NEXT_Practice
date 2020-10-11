#pragma once

#include "gtk/Renderer.h"

class TestRenderer : public gtk::Renderer
{

public:

	TestRenderer(const unsigned int& id) : Renderer(id)
	{

	}

	void Draw() override
	{
		// Draw stuff
	}
};