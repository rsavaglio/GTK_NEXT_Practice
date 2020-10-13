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
		gtk::ComponentGroup Group1 = CreateComponenetGroup();

		// Create Entities and add components here
		gtk::Entity player = CreateEntity();
		AddComponent(Group1, new TestComponent(player)); // Maybe make entities and CompGroups
		AddRenderer(new TestRenderer(player));

	}
};