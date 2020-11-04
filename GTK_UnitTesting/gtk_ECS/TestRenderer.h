#pragma once

#include "gtk/gtk.h"

class RendTemplate : public gtk::Renderer
{

public:

	RendTemplate(gtk::Entity* const entity) : Renderer(entity) {}

	void Start() override
	{
		// Called first frame
	}

	void Draw() override
	{
		// Draw stuff
	}

};


class TestRenderer : public gtk::Renderer
{

public:

	TestRenderer(gtk::Entity* const entity) : Renderer(entity) {}

	void Start() override
	{
		// Called first frame
	}

	void Draw() override
	{
		// Draw stuff
	}

};


class ToggleMeRend : public gtk::Renderer
{

public:

	ToggleMeRend(gtk::Entity* const entity) : Renderer(entity), m_DrawCount(0) {}

	void Start() override
	{
		// Called first frame
	}

	void Draw() override
	{
		m_DrawCount++;
	}

	unsigned int m_DrawCount;


};