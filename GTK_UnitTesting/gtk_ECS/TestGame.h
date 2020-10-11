#pragma once
#include "gtk/Game.h"
#include "TestScene.h"

class TestGame : public gtk::Game
{

public:

	virtual void Init() override
	{
		// Add the scenes of the game here
		AddScene("TestScene", new TestScene);


	}


};