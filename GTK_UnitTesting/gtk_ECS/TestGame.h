#pragma once

#include "TestScene.h"

class TestGame : public gtk::Game
{

public:

	void Init() override
	{
		// Add the scenes of the game here
		AddScene("TestScene", new TestScene(this));
		AddScene("ToggleScene", new ToggleScene(this));

	}

	int GetVecValues()
	{
		//m_SceneMap.at("TestScene")
	}

};