#pragma once

#include "gtk/gtk.h"

#include "Components.h"
#include "Renderers.h"

class SceneTemplate : public gtk::Scene
{

public:

	SceneTemplate(gtk::Game& game) : gtk::Scene(game) {}
	
protected:
	
	// Called by game when scene starts
	void Setup() override
	{
		using namespace gtk;

		UpdateGroup group = CreateUpdateGroup();
		RenderLayer layer = CreateRenderLayer();

		Entity& camera = CreateEntity();
			AddCamera(camera, new PerspectiveCam(1, 100, 80));

		Entity& entity = CreateEntity();
		AddBehavior(entity, group, new BehaviorTemplate());
		AddRenderer(entity, layer, new RendTemplate());

	}

	// Called after all entities are updated
	void PostUpdate() override
	{

	}
};

class PracScene : public gtk::Scene
{

public:

	PracScene(gtk::Game& game) : gtk::Scene(game) {}

protected:

	// Called by game when scene starts
	void Setup() override
	{
		using namespace gtk;

		UpdateGroup controllers = CreateUpdateGroup();
		RenderLayer rendLayer = CreateRenderLayer();

		Entity& player = CreateEntity();
			player.Pos(vec3(0.0f, 0.0f, 0.0f));
			AddBehavior(player, controllers, new PlayerController(10.0f));
			AddRenderer(player, rendLayer, new SpriteRenderer(App::CreateSprite(".\\TestData\\Test.bmp", 8, 4)));

		Entity& cube = CreateEntity();
			cube.Pos(vec3(0.0f, 0.0f, 500.0f));
			cube.Rot(vec3(0.0f, 45.0f, 0.0f));
			cube.Scale(vec3(100.0f, 100.0f, 100.0f));
			//AddBehavior(cube, controllers, new RotaterComp(vec3(1.0f, 0.0f, 0)));
			AddRenderer(cube, rendLayer, new CubeRenderer());

		Entity& childCube = CreateEntity(cube);
			childCube.Pos(vec3(1.5f, 1.5f, 1.0f));
			childCube.Scale(vec3(0.5f, 0.5f, 0.5f));
			AddBehavior(childCube, controllers, new RotaterComp(gtk::vec3(0, 1.0f, 0)));
			AddRenderer(childCube, rendLayer, new CubeRenderer());

		Entity& childCube2 = CreateEntity(cube);
			childCube2.Pos(vec3(-1.5f, 1.5f, -1.0f));
			childCube2.Scale(vec3(0.5f, 0.5f, 0.5f));
			AddBehavior(childCube2, controllers, new RotaterComp(gtk::vec3(0, 1.0f, 0)));
			AddRenderer(childCube2, rendLayer, new CubeRenderer());

		Entity& babyCube = CreateEntity(childCube);
			babyCube.Pos(vec3(1.5f, 1.5f, 1.5f));
			babyCube.Scale(vec3(0.5f, 0.5f, 0.5f));
			AddRenderer(babyCube, rendLayer, new CubeRenderer());

		Entity& tripod = CreateEntity();
			tripod.Pos(vec3(0.0f, 0.0f, 500.0f));
			tripod.Rot(vec3(0.0f, 0.0f, 0.0f));
			tripod.Scale(vec3(50.0f));
			AddBehavior(tripod, controllers, new RotaterComp(vec3(0.0f, 1.0f, 0)));
			AddRenderer(tripod, rendLayer, new CubeRenderer());
		
		Entity& test = CreateEntity(tripod);
			test.Pos(vec3(0.0f, 10.0f, 0.0f));
			AddRenderer(test, rendLayer, new CubeRenderer());

		Entity& test2 = CreateEntity(test);
			test2.Pos(vec3(0.0f, 0.0f, -10.0f));
			AddRenderer(test2, rendLayer, new CubeRenderer());

		Entity& camera = CreateEntity();
			AddCamera(camera, new PerspectiveCam(1, 1000, 80));
			camera.Pos(vec3(0.0f, 0.0f, 0.0f));
			camera.Rot(vec3(0.0f, 0.0f, 0.0f));
		
	}

	// Called after all entities are updated but before renderer
	void PostUpdate() override
	{

	}
};