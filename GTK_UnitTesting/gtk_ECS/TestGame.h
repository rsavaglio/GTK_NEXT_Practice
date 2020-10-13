#pragma once
#include "gtk/gtk.h"
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