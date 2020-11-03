#pragma once

#include "gtk/gtk.h"

#include "TestComponent.h"
#include "TestRenderer.h"

class SceneTemplate : public gtk::Scene
{

protected:

	SceneTemplate(gtk::Game* const game) : gtk::Scene(game) {}

	// Called by game when scene starts
	void Init() override
	{
		using namespace gtk;

		CompGroup compGroup = CreateCompGroup();

		Entity* entity = CreateEntity();
			AddComponent(new CompTemplate(entity, compGroup));
			AddRenderer(new ToggleMeRend(entity));

	}

	// Called after all entities are updated
	virtual void PostUpdate() override
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

	virtual void PostUpdate() override
	{

	}
};


class ToggleScene : public gtk::Scene
{
public:
	ToggleScene(gtk::Game* const game) : gtk::Scene(game), m_UpdateCount(0) {}

protected:

	virtual void Init() override
	{
		using namespace gtk;

		CompGroup g_Tog = CreateCompGroup();
		CompGroup g_TogMe = CreateCompGroup();


		Entity* ToggleMeElmo = CreateEntity();
			tmc = new ToggleMeComp(ToggleMeElmo, g_TogMe);
			AddComponent(tmc);

			tmr = new ToggleMeRend(ToggleMeElmo);
			AddRenderer(tmr);


		Entity* Toggler = CreateEntity();
			AddComponent(new TogglerComp(Toggler, g_Tog, this, ToggleMeElmo, tmc, tmr));
	}

	void CheckValues(unsigned int updateCount, unsigned int comp, unsigned int rend)
	{
		if (m_UpdateCount == updateCount)
		{
			EXPECT_EQ(tmc->m_UpdateCount, comp);

			EXPECT_TRUE(tmr->m_DrawCount == rend || tmr->m_DrawCount == rend - 1);
		}
	}

	virtual void PostUpdate() override
	{

		m_UpdateCount++;

		CheckValues(10, 10, 10);
		// Comp off
		CheckValues(20, 10, 20);
		// Comp on
		// Rend off
		CheckValues(30, 20, 20);
		// Rend on
		CheckValues(40, 30, 30);
		// Ent off
		CheckValues(50, 30, 30);
		// Ent on
		CheckValues(60, 40, 40);
		// Ent off, comp off
		CheckValues(70, 40, 40);
		// Ent on, comp should stay off
		CheckValues(80, 40, 50);
		// Comp on
		CheckValues(90, 50, 60);
		// Comp off, ent off (reverse order)
		CheckValues(100, 50, 60);
		// Ent on
		CheckValues(110, 50, 70);
		// Comp on
		CheckValues(120, 60, 80);
		// Ent off, rend off
		CheckValues(130, 60, 80);
		// Ent on, rend should stay off
		CheckValues(140, 70, 80);
		// Rend on
		CheckValues(150, 80, 90);
		// Rend off, ent off (reverse order)
		CheckValues(160, 80, 90);
		// Ent on
		CheckValues(170, 90, 90);
		// Rend on
		CheckValues(180, 100, 100);

	}

private:
	unsigned int m_UpdateCount;
	
	ToggleMeComp* tmc;
	ToggleMeRend* tmr;

};