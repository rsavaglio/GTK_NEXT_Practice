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
		gtk::ComponentGroup Adders = CreateComponenetGroup();
		gtk::ComponentGroup Subtractors = CreateComponenetGroup();


		// Create Entities and add components here
		gtk::Entity  player = CreateEntity();
			AddRenderer (player, new TestRenderer());

			AddComponent(player, Adders, new VectorTest(true));
			AddComponent(player, Subtractors, new VectorTest(false));

		gtk::Entity  enemy = CreateEntity();
			AddComponent(enemy, Adders, new VectorTest(true));
			AddComponent(enemy, Subtractors, new VectorTest(false));


	}
};