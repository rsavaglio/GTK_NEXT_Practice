#pragma once
#include "TestScene.h"

class SceneSwitchingGame : public gtk::Game
{

public:

	void Init() override
	{
		// Add the scenes of the game here
		AddScene("TestScene", new TestScene(*this));
		AddScene("ToggleScene", new ToggleScene(*this));

	}

};


class ToggleGame : public gtk::Game
{

public:

	void Init() override
	{
		// Add the scenes of the game here
		AddScene("ToggleScene", new ToggleScene(*this));

	}
};