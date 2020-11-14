#pragma once

#include "gtk/gtk.h"

#include "TestComponent.h"
#include "TestRenderer.h"

class SceneTemplate : public gtk::Scene
{

protected:

	SceneTemplate(gtk::Game& game) : gtk::Scene(game) {}

	// Called by game when scene starts
	void Init() override
	{
		using namespace gtk;

		RenderLayer layer = CreateRenderLayer();

		Entity& entity = CreateEntity();
			AddBehavior(entity, new BehaviorTemplate());
			AddRenderer(entity, layer, new ToggleMeRend());

	}

	// Called after all entities are updated
	virtual void PostUpdate() override
	{

	}
};

class TestScene : public gtk::Scene
{
public:
	TestScene(gtk::Game& game) : gtk::Scene(game) {}

protected:

	void Init() override
	{
		using namespace gtk;

		gtk::RenderLayer layer = CreateRenderLayer();


		gtk::Entity& SS = CreateEntity();
		gtk::Behavior& SSC = AddBehavior(SS, new SceneSwitcherComp(*this, "TestScene"));

		// Create Entities and add components here
		gtk::Entity& player = CreateEntity();
		AddBehavior(player, new VectorTest(true, SSC));
		AddBehavior(player, new VectorTest(false, SSC));

		// Hat is a child of player
		gtk::Entity& hat = CreateEntity(player);
		AddRenderer(hat, layer, new TestRenderer());
		AddBehavior(hat, new VectorTest(true, SSC));
		AddBehavior(hat, new VectorTest(false, SSC));

	}
	virtual void PostUpdate() override
	{

	}
};


class ToggleScene : public gtk::Scene
{
public:
	ToggleScene(gtk::Game& game) : gtk::Scene(game), m_UpdateCount(0) {}

protected:

	virtual void Init() override
	{
		using namespace gtk;

		RenderLayer layer = CreateRenderLayer();

		Entity& ToggleMeElmo = CreateEntity();

			p_tmc = new ToggleMeComp();
			Behavior& tmc = AddBehavior(ToggleMeElmo, p_tmc);

			p_tmr = new ToggleMeRend();
			Renderer& tmr = AddRenderer(ToggleMeElmo, layer, p_tmr);


		Entity& Toggler = CreateEntity();
			AddBehavior(Toggler, new TogglerComp(ToggleMeElmo, tmc, tmr));
			
	}

	void CheckValues(unsigned int updateCount, unsigned int comp, unsigned int rend)
	{
		if (m_UpdateCount == updateCount)
		{
			EXPECT_EQ(p_tmc->m_UpdateCount, comp);

			EXPECT_TRUE(p_tmr->m_DrawCount == rend || p_tmr->m_DrawCount == rend - 1);
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

	ToggleMeComp* p_tmc;
	ToggleMeRend* p_tmr;

	unsigned int m_UpdateCount;

};