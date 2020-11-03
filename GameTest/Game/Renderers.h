#pragma once

#include "gtk/gtk.h"

class RendTemplate : public gtk::Renderer
{

public:

	RendTemplate(gtk::Entity* const entity) : Renderer(entity) {}

	void Draw() override
	{
		// Draw stuff
	}

};