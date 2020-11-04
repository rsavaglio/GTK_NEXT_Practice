#pragma once

#include "gtk/gtk.h"

#include "Scenes.h"


class GameTemplate : public gtk::Game
{

public:

	void Init() override
	{
		// Add the scenes of the game here
		AddScene("SceneTemplate", new SceneTemplate(this));
	}
};

class PracGame : public gtk::Game
{

public:

	void Init() override
	{
		// Add the scenes of the game here
		AddScene("PracScene", new PracScene(this));
	}
};
