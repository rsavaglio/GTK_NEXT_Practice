#pragma once

#include "gtk/gtk.h"

#include "Scenes.h"


class GameTemplate : public gtk::Game
{

public:

	void Init() override
	{
		// Add the scenes of the game here
		AddScene("SceneTemplate", new SceneTemplate(*this));
	}
};

class TowerDefenseGame : public gtk::Game
{

public:

	void Init() override
	{
		// Add the scenes of the game here
		AddScene("L2", new TD_Level_2(*this));
		AddScene("L1", new TD_Level_1(*this));
	}
};
