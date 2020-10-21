#pragma once

#include "gtk/gtk.h"

#include "TestComponent.h"
#include "TestRenderer.h"

class TestScene : public gtk::Scene
{

protected:

	virtual void Init() override
	{
		// Add Component Group
		gtk::CompGroup Adders = CreateCompGroup();
		gtk::CompGroup Subtractors = CreateCompGroup();


		// Create Entities and add components here
		gtk::Entity  player = CreateEntity();
			AddRenderer (player, new TestRenderer());

			AddComponent(new VectorTest(player, Adders, true));
			AddComponent(new VectorTest(player, Subtractors, false));

		gtk::Entity  enemy = CreateEntity();
			AddComponent(new VectorTest(enemy, Adders, true));
			AddComponent(new VectorTest(enemy, Subtractors, false));

	}
};