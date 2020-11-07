#pragma once

#include "gtk/gtk.h"

#include "Components.h"
#include "Renderers.h"

class SceneTemplate : public gtk::Scene
{

public:

	SceneTemplate(gtk::Game* const game) : gtk::Scene(game) {}

	
protected:
	
	// Called by game when scene starts
	void Init() override
	{
		using namespace gtk;

		CompGroup compGroup = CreateCompGroup();

		Entity* entity = CreateEntity();
		AddComponent(new CompTemplate(entity, compGroup));
		AddRenderer(new RendTemplate(entity));

	}

	// Called after all entities are updated
	void PostUpdate() override
	{

	}
};

class PracScene : public gtk::Scene
{

public:

	PracScene(gtk::Game* const game) : gtk::Scene(game) {}


protected:

	// Called by game when scene starts
	void Init() override
	{
		using namespace gtk;

		CompGroup controllers = CreateCompGroup();

		Entity* player = CreateEntity();
			player->SetPos(1.0f, 400.0f, 0);
			AddComponent(new PlayerController(player, controllers, 10.0f));
			AddRenderer(new SpriteRenderer(player, App::CreateSprite(".\\TestData\\Test.bmp", 8, 4)));
		

		Entity* cube = CreateEntity();
			AddRenderer(new CubeRenderer(cube));

	}

	// Called after all entities are updated but before renderer
	void PostUpdate() override
	{

	}
};