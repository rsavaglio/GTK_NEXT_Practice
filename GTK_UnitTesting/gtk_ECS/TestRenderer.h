#pragma once

#include "gtk/gtk.h"

class RendTemplate : public gtk::Renderer
{

public:

	RendTemplate() {}

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

	TestRenderer() {}

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

	ToggleMeRend() : m_DrawCount(0) {}

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