#pragma once

#include "gtk/gtk.h"

#include "Components.h"
#include "Renderers.h"
#include "ObjectPools.h"

#include <queue>

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


		UpdateGroup group1 = CreateUpdateGroup();
		RenderLayer layer1 = CreateRenderLayer();
		RenderLayer layer2 = CreateRenderLayer();
	
		Entity& cube = CreateEntity();
			cube.Pos(vec3(0.0f, 0.0f, 0.0f));
			AddBehavior(cube, group1, new CubeMover(1.0f));
			AddRenderer(cube, layer1, new CubeRenderer());
			AddRenderer(cube, layer2, new DirRenderer());

		Entity& camera = CreateEntity(cube);
			AddCamera(camera, new PerspectiveCam(1, 1000, 80));
			camera.Pos(vec3(0.0f, 0.0f, -5.0f));
			camera.Rot(vec3(0.0f, 0.0f, 0.0f));


		Entity& donut = CreateEntity();
			donut.Scale(10.0f);
			AddRenderer(donut, layer1, new OBJRenderer(".\\TestData\\donut.obj"));


			/*
		Entity& childCube = CreateEntity(donut);
			childCube.Pos(vec3(1.5f, 1.5f, 1.0f));
			childCube.Scale(vec3(0.5f, 0.5f, 0.5f));
			//AddBehavior(childCube, controllers, new RotaterComp(gtk::vec3(0, 1.0f, 0)));
			AddRenderer(childCube, rendLayer, new CubeRenderer());

		Entity& childCube2 = CreateEntity(donut);
			childCube2.Pos(vec3(-1.5f, 1.5f, -1.0f));
			childCube2.Scale(vec3(0.5f, 0.5f, 0.5f));
			//AddBehavior(childCube2, controllers, new RotaterComp(gtk::vec3(0, 1.0f, 0)));
			AddRenderer(childCube2, rendLayer, new CubeRenderer());

		Entity& babyCube = CreateEntity(childCube);
			babyCube.Pos(vec3(1.5f, 1.5f, 1.5f));
			babyCube.Scale(vec3(0.5f, 0.5f, 0.5f));
			AddRenderer(babyCube, rendLayer, new CubeRenderer());

		Entity& tripod = CreateEntity("tripod");
			tripod.Pos(vec3(30.0f, 0.0f, 500.0f));
			tripod.Rot(vec3(0.0f, 0.0f, 0.0f));
			tripod.Scale(vec3(50.0f));
			AddBehavior(tripod, controllers, new RotaterComp(vec3(0.0f, 1.0f, 0)));
			AddRenderer(tripod, rendLayer, new CubeRenderer());
		
		Entity& test = CreateEntity("test", tripod);
			test.Pos(vec3(0.0f, 10.0f, 0.0f));
			AddRenderer(test, rendLayer, new CubeRenderer());

		Entity& test2 = CreateEntity("test2", test);
			test2.Pos(vec3(0.0f, 0.0f, -10.0f));

			*/



			/*
		// Player sprite
		Entity& player = CreateEntity();
			player.Pos(vec3(0.0f, 0.0f, 400.0f));
			AddBehavior(player, controllers, new RotaterComp(vec3(0.0f, 0.0f, 1.0f)));
			AddRenderer(player, layer2, new SpriteRenderer(".\\TestData\\Test.bmp", 8, 4));

			
		Entity& player2 = CreateEntity(player);
			player2.Pos(vec3(0.0f, 40.0f, 0.0f));
			player2.Scale(0.5f);
			AddBehavior(player2, controllers, new RotaterComp(vec3(0.0f, 0.0f, 1.0f)));
			AddRenderer(player2, rendLayer, new SpriteRenderer(".\\TestData\\Test.bmp", 8, 4));

			
		Entity& player3 = CreateEntity(player2);
			player3.Pos(vec3(100.0f, 0.0f, 0.0f));
			AddBehavior(player3, controllers, new RotaterComp(vec3(0.0f, 0.0f, 1.0f)));
			AddRenderer(player3, rendLayer, new SpriteRenderer(".\\TestData\\Test.bmp", 8, 4));

		// Text 
		Entity& text = CreateEntity(player3);
			text.Pos(vec3(0.0f, 0.0f, 0.0f));
			AddRenderer(text, layer2, new TextRenderer("NEXT 2021!", vec3(1.0f, 1.0f, 1.0f)));

			*/
	}

	// Called after all entities are updated but before renderer
	void PostUpdate() override
	{

	}
};


class PinballScene : public gtk::Scene
{

public:

	PinballScene(gtk::Game& game) : gtk::Scene(game) {}

protected:

	// Called by game when scene starts
	void Setup() override
	{
		using namespace gtk;

		UpdateGroup group = CreateUpdateGroup();
		RenderLayer layer = CreateRenderLayer();

		Entity& camera = CreateEntity();
			AddCamera(camera, new PerspectiveCam(1, 100, 80));
			camera.Pos(vec3(0.0f, 0.0f, -10.0f));


		ObjectPool& spherePool = CreatePool("spherePool", new SpherePool(10, *this, group, layer));

		Entity& sphereManager = CreateEntity();
			AddBehavior(sphereManager, group, new SphereManager(1.0f, spherePool));

	}

	// Called after all entities are updated
	void PostUpdate() override
	{
		
	}
};