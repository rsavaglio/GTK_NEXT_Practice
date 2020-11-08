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
			cube->SetPos(500.0f, 400.0f, 10.0f);
			cube->SetRotY(45.0f);
			cube->SetScale(100.0f, 100.0f, 100.0f);
			AddComponent(new RotaterComp(cube, controllers, gtk::vec3(1.0f, 1.0f, 0)));
			AddRenderer(new CubeRenderer(cube));

		Entity* childCube = CreateEntity(cube);
			childCube->SetPos(1.5f, 1.5f, 1.0f);
			childCube->SetScale(0.5f, 0.5f, 0.5f);
			AddComponent(new RotaterComp(childCube, controllers, gtk::vec3(0, 1.0f, 0)));
			AddRenderer(new CubeRenderer(childCube));

		Entity* babyCube = CreateEntity(childCube);
			babyCube->SetPos(1.5f, 1.5f, 1.5f);
			babyCube->SetScale(0.5f, 0.5f, 0.5f);
			AddRenderer(new CubeRenderer(babyCube));

	}

	// Called after all entities are updated but before renderer
	void PostUpdate() override
	{

	}
};