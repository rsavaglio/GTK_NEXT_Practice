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
		gtk::Entity*  player = CreateEntity();
			AddComponent(new VectorTest(player, Adders, true));
			//AddComponent(new VectorTest(player, Adders, true)); // Testing duplicates
			AddComponent(new VectorTest(player, Subtractors, false));

		// Hat is a child of player
		gtk::Entity*  hat = CreateEntity(player);
			AddRenderer(new TestRenderer(hat));
			//AddRenderer(new TestRenderer(hat)); // Testing duplicates
			AddComponent(new VectorTest(hat, Adders, true));
			AddComponent(new VectorTest(hat, Subtractors, false));

	}
};