#pragma once

#include "gtk/Scene.h"

#include "TestComponent.h"
#include "TestRenderer.h"

class TestScene : public gtk::Scene
{

protected:

	virtual void Init() override
	{
		// Add Component Group
		COMP_GROUP Group1 = CreateComponenetGroup();


		// Create Entities and add components here
		ENTITY player = CreateEntity();
		AddComponent(Group1, new TestComponent(player));
		AddRenderer(new TestRenderer(player));

	}
};