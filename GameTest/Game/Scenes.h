#pragma once

#include "gtk/gtk.h"

#include "Components.h"
#include "Renderers.h"
#include "ObjectPools.h"
#include "Colliders.h"
#include "enums.h"

#include <queue>

#define RED vec3(1.0f, 0.0f, 0.0f)
#define PINK vec3(7.0f, 0.3f, 0.6f)

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

enum sState
{
	SETUP,
	INTRO,
	GAMEPLAY,
	END1,
	END2,
	OUTRO
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
		UpdateGroup group2 = CreateUpdateGroup();

		RenderLayer layer1 = CreateRenderLayer();
		RenderLayer layer2 = CreateRenderLayer();
		RenderLayer layerUI = CreateRenderLayer();

		CollisionGroup col1 = CreateCollisionGroup();
	


		Entity& monkey = CreateEntity("monkey");
			monkey.Pos(vec3(0.0f, -8.0f, -40.0f));
			monkey.Rot(vec3(0.0f, 0.0f, 0.0f));
			ObjectPool& bullets = CreatePool("monkeyBullets", new BulletPool(monkey, 10, *this, group1, layer2));
			AddCollider(monkey, col1, new SphereCollider());
			//AddBehavior(monkey, group1, new ShooterB(30.0f, bullets));
			AddBehavior(monkey, group2, new RotatorB(vec3(0.0f, -100.0f, 0.0f)));
			AddRenderer(monkey, layer2, new OBJRenderer(".\\TestData\\monkey.obj", vec3(0.7f, 0.7, 0.3f)));


		Entity& sphere = CreateEntity("sphere");
			sphere.Pos(vec3(0.0f, 5.0f, -40.0f));
			AddCollider(sphere, col1, new SphereCollider());
			AddRenderer(sphere, layer2, new OBJRenderer(".\\TestData\\sphere.obj", vec3(0.7f, 0.7, 0.3f)));

		Entity& tripod = CreateEntity();
			tripod.Pos(vec3(0.0f, 0.0f, -50.0f));
			tripod.Rot(vec3(0.0f, 0.0f, 0.0f));
			AddBehavior(tripod, group1, new LERPatState(INTRO, 2.0f, vec3(0.0f, 0.0f, -50.0f), vec3(0.0f, 0.0f, 0.0f)));

		Entity& camera = CreateEntity(tripod);
			AddCamera(camera, new PerspectiveCam(1, 1000, 70));
			//AddBehavior(camera, group1, new CameraB(100.0f));

		Entity& uiText = CreateEntity(camera);
			uiText.Pos(vec3(0.0f, 0.0f, 50.0f));
			AddRenderer(uiText, layerUI, new TextRenderer("Score: "));

		Entity& donut = CreateEntity();
			donut.Scale(50.0f);
			donut.Pos(vec3(46.0f, 0.0f, -12.0f));
			donut.Rot(vec3(0.0f, 0.0f, 0.0f));
			AddBehavior(donut, group1, new RotatorB(vec3(0.0f, 20.0f, 0.0f)));
			AddRenderer(donut, layer1, new OBJRenderer(".\\TestData\\donut.obj", vec3(0.5f, 0.0f, 0.5f)));



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

class TD_Level_1 : public gtk::Scene
{

public:

	TD_Level_1(gtk::Game& game) : gtk::Scene(game) {}

protected:

	void CreatePath(const std::vector<vec3>& nodePos, RenderLayer layer, CollisionGroup colGroup, const vec3& color)
	{
		int i = 0;
		for (const vec3& pos : nodePos)
		{
			Entity& node = CreateEntity("PathNode" + std::to_string(i));
			AddRenderer(node, layer, new CubeRenderer(color));
			AddCollider(node, colGroup, new SphereCollider());
			node.Scale(3.0f);
			node.Pos(pos);
			i++;
		}
	}




	void AddToPath(std::vector<vec3>& nodes, Direction dir, int count)
	{
		ASSERT(nodes.size() > 0);

		switch (dir)
		{
		case LEFT :

			for (int i = 0; i < count; i++)
			{
				nodes.push_back(vec3(nodes.back()) + vec3(-6.0f, 0.0f, 0.0f));
			}

			break;

		case RIGHT:

			for (int i = 0; i < count; i++)
			{
				nodes.push_back(vec3(nodes.back()) + vec3(6.0f, 0.0f, 0.0f));
			}

			break;

		case UP:

			for (int i = 0; i < count; i++)
			{
				nodes.push_back(vec3(nodes.back()) + vec3(0.0f, 6.0f, 0.0f));
			}

			break;

		case DOWN:

			for (int i = 0; i < count; i++)
			{
				nodes.push_back(vec3(nodes.back()) + vec3(0.0f, -6.0f, 0.0f));
			}

			break;

		case FORWARD:

			for (int i = 0; i < count; i++)
			{
				nodes.push_back(vec3(nodes.back()) + vec3(0.0f, 0.0f, 6.0f));
			}

			break;

		case BACK:

			for (int i = 0; i < count; i++)
			{
				nodes.push_back(vec3(nodes.back()) + vec3(0.0f, 0.0f, -6.0f));
			}

			break;
		}


	}

	// Called by game when scene starts
	void Setup() override
	{
		using namespace gtk;

		UpdateGroup group1 = CreateUpdateGroup();
		UpdateGroup group2 = CreateUpdateGroup();

		RenderLayer layer1 = CreateRenderLayer();
		RenderLayer layer2 = CreateRenderLayer();
		RenderLayer layerUI = CreateRenderLayer();

		CollisionGroup col1 = CreateCollisionGroup();
		CollisionGroup col2 = CreateCollisionGroup();

		Entity& tripod = CreateEntity();
			tripod.Pos(vec3(0.0f, 0.0f, -10.0f));
			tripod.Rot(vec3(0.0f, 00.0f, 0.0f));

		Entity& camera = CreateEntity(tripod);
			camera.Rot(vec3(0.0f, 0.0f, 0.0f));
			AddCamera(camera, new PerspectiveCam(1, 1000, 70));
			AddBehavior(camera, group1, new CameraB(100.0f));

		Entity& cursor = CreateEntity();
			AddBehavior(cursor, group1, new CursorB(35.0f));
			AddRenderer(cursor, layer2, new OBJRenderer(".\\TestData\\sphere.obj"));
			AddCollider(cursor, col1, new SphereCollider());


		//// PATH ////

		std::vector<vec3> path;

		// Start Node
		path.push_back(vec3(-28.0f, 12.0f, 0.0f));
		
		AddToPath(path, RIGHT, 3);
		AddToPath(path, FORWARD, 3);
		AddToPath(path, DOWN, 2);
		AddToPath(path, BACK, 3);
		AddToPath(path, LEFT, 2);
		AddToPath(path, DOWN, 3);
		AddToPath(path, RIGHT, 4);
		AddToPath(path, UP, 3);
		AddToPath(path, RIGHT, 3);
		AddToPath(path, BACK, 2);
		AddToPath(path, UP, 3);

		CreatePath(path, layer1, col1, RED);
	
		//// Monkeys ////
		Entity& barrelOfMonkeys = CreateEntity();
			ObjectPool& monkeyPool = CreatePool("monkeyPool", new MonkeyPool(barrelOfMonkeys, 20, *this, group1, layer1, col2, path));
			AddBehavior(barrelOfMonkeys, group1, new BarrelOfMonkeysB(monkeyPool));

	}

	// Called after all entities are updated
	void PostUpdate() override
	{
		
	}
};