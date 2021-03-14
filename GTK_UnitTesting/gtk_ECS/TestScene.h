#pragma once

#include "gtk/gtk.h"

#include "TestComponent.h"
#include "TestRenderer.h"

class SceneTemplate : public gtk::Scene
{

protected:

	SceneTemplate(gtk::Game& game) : gtk::Scene(game) {}

	// Called by game when scene starts
	void Setup() override
	{
		using namespace gtk;

		UpdateGroup group = CreateUpdateGroup();
		RenderLayer layer = CreateRenderLayer();

		Entity& entity = CreateEntity();
			AddBehavior(entity, group, new CompTemplate());
			AddRenderer(entity, layer, new ToggleMeRend());

		Entity& camera = CreateEntity();
			AddCamera(camera, new PerspectiveCam(1, 100, 80));

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

	void Setup() override
	{
		using namespace gtk;

		gtk::UpdateGroup Adders = CreateUpdateGroup();
		gtk::UpdateGroup Subtractors = CreateUpdateGroup();
		gtk::UpdateGroup SceneSwitchers = CreateUpdateGroup();

		gtk::RenderLayer layer = CreateRenderLayer();

		gtk::Entity& SS = CreateEntity();
		gtk::Behavior& SSC = AddBehavior(SS, SceneSwitchers, new SceneSwitcherComp(*this, "TestScene"));

		gtk::Entity& player = CreateEntity();
		AddBehavior(player, Adders, new VectorTest(true, SSC));
		AddBehavior(player, Subtractors, new VectorTest(false, SSC));

		gtk::Entity& hat = CreateEntity(player);
		AddRenderer(hat, layer, new TestRenderer());
		AddBehavior(hat, Adders, new VectorTest(true, SSC));
		AddBehavior(hat, Subtractors, new VectorTest(false, SSC));

		Entity& camera = CreateEntity();
		AddCamera(camera, new PerspectiveCam(1, 100, 80));

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

	void Setup() override
	{
		using namespace gtk;

		UpdateGroup g_Tog = CreateUpdateGroup();
		UpdateGroup g_TogMe = CreateUpdateGroup();

		RenderLayer layer = CreateRenderLayer();

		Entity& ToggleMeElmo = CreateEntity();

			p_tmc = new ToggleMeComp();
			Behavior& tmc = AddBehavior(ToggleMeElmo, g_TogMe, p_tmc);

			p_tmr = new ToggleMeRend();
			Renderer& tmr = AddRenderer(ToggleMeElmo, layer, p_tmr);


		Entity& Toggler = CreateEntity();
			AddBehavior(Toggler, g_Tog, new TogglerComp(ToggleMeElmo, tmc, tmr));


		Entity& camera = CreateEntity();
			AddCamera(camera, new PerspectiveCam(1, 100, 80));
			
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