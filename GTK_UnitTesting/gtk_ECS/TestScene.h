#pragma once

#include "gtk/Scene.h"

#include "TestComponent.h"

class TestScene : public gtk::Scene
{

protected:

	virtual void Init() override
	{

		// Create Entities and add components here

		unsigned int player = CreateEntity();

		AddComponent(new TestComponent(player));

	}
};