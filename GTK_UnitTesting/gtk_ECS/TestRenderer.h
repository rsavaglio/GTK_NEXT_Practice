#pragma once

#include "gtk/Renderer.h"

class TestRenderer : public gtk::Renderer
{

public:

	TestRenderer(const Entity& entity) : Renderer(entity)
	{

	}

	void Draw() override
	{
		// Draw stuff
	}
};