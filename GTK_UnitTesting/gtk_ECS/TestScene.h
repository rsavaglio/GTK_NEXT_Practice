#pragma once

#include "gtk/gtk.h"

#include "TestComponent.h"
#include "TestRenderer.h"

class SceneTemplate : public gtk::Scene
{

protected:

	SceneTemplate(gtk::Game* const game) : gtk::Scene(game) {}

	void Init() override
	{


	}
};


class TestScene : public gtk::Scene
{
public:
	TestScene(gtk::Game* const game) : gtk::Scene(game) {}

protected:

	virtual void Init() override
	{
		// Add Component Group
		gtk::CompGroup Adders = CreateCompGroup();
		gtk::CompGroup Subtractors = CreateCompGroup();
		gtk::CompGroup SceneSwitchers = CreateCompGroup();

		gtk::Entity* SS = CreateEntity();
			SceneSwitcherComp* const SSC = new SceneSwitcherComp(SS, SceneSwitchers, this, "TestScene");
			AddComponent(SSC);

		// Create Entities and add components here
		gtk::Entity*  player = CreateEntity();
			AddComponent(new VectorTest(player, Adders, true, SSC));
			AddComponent(new VectorTest(player, Subtractors, false, SSC));

		// Hat is a child of player
		gtk::Entity*  hat = CreateEntity(player);
			AddRenderer(new TestRenderer(hat));
			AddComponent(new VectorTest(hat, Adders, true, SSC));
			AddComponent(new VectorTest(hat, Subtractors, false, SSC));

	}
};


class ToggleScene : public gtk::Scene
{
public:
	ToggleScene(gtk::Game* const game) : gtk::Scene(game) {}

protected:

	virtual void Init() override
	{
		EXPECT_EQ(1, 1);
	}
};