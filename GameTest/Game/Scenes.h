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
			AddCollider(monkey, col1, new SphereCollider());
			AddBehavior(monkey, group2, new RotatorB(vec3(0.0f, -100.0f, 0.0f)));
			AddRenderer(monkey, layer2, new OBJRenderer(".\\TestData\\monkey.obj", vec3(0.7f, 0.7, 0.3f)));


		Entity& sphere = CreateEntity("sphere");
			sphere.Pos(vec3(0.0f, 5.0f, -40.0f));
			AddCollider(sphere, col1, new SphereCollider());
			AddRenderer(sphere, layer2, new OBJRenderer(".\\TestData\\sphere.obj", vec3(0.7f, 0.7, 0.3f)));

		Entity& tripod = CreateEntity();
			tripod.Pos(vec3(0.0f, 0.0f, -50.0f));
			tripod.Rot(vec3(0.0f, 0.0f, 0.0f));

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


		//// Groups and Layers ////
#pragma region GroupsLayers

		UpdateGroup group1 = CreateUpdateGroup();
		UpdateGroup group2 = CreateUpdateGroup();

		RenderLayer layer1 = CreateRenderLayer();
		RenderLayer layer2 = CreateRenderLayer();
		RenderLayer UI1 = CreateRenderLayer();
		RenderLayer UI2 = CreateRenderLayer();

		CollisionGroup cursorSelectionCol = CreateCollisionGroup();
		CollisionGroup towerSightCol = CreateCollisionGroup();
		CollisionGroup bulletsCol = CreateCollisionGroup();

#pragma endregion

		//// Camera ////

		Entity& tripod = CreateEntity();
			tripod.Pos(vec3(0.0f, 0.0f, -25.0f));

		Entity& camera = CreateEntity(tripod);
			camera.Rot(vec3(0.0f, 0.0f, 0.0f));
			AddCamera(camera, new PerspectiveCam(1, 1000, 70));
			AddBehavior(camera, group1, new CameraB(100.0f));


		//// UI ////
#pragma region UI_TowerSelectionMenu


		/// Backdrop
		
		Entity& uiBackdrop = CreateEntity(camera);
			uiBackdrop.Pos(vec3(0.0f, -220.0f, 100.0f));
			uiBackdrop.Scale(1.0f);
			AddRenderer(uiBackdrop, UI1, new SpriteRenderer(".\\TestData\\UI_Backdrop.bmp", 1, 1));

		Entity& uiBorder = CreateEntity(camera);
			AddRenderer(uiBorder, UI1, new LineRenderer2(vec3(0.8, 0.2f, 0.8f), vec3(-15.0f, -4.9f, 10.0f), vec3(15.0f, -4.9f, 10.0f)));

		//// Money ////
		
		Entity& uiMoney = CreateEntity(camera);
			uiMoney.Pos(vec3(2.5f, -3.5f, 5.0f));
			Entity& uiMoneyTitle = CreateEntity(uiMoney);
				AddRenderer(uiMoneyTitle, UI2, new TextRenderer("Money"));
			Entity& uiMoneyAmount = CreateEntity(uiMoney);
			NumUIRenderer* moneyRend = new NumUIRenderer(9999);
				AddRenderer(uiMoneyAmount, UI2, moneyRend);
				uiMoneyAmount.Pos(vec3(0.8f, 0.0f, 0.0f));
		
		/// Wave ///
		Entity& waveTitle = CreateEntity(camera);
			waveTitle.Pos(vec3(-5.2f, -3.3f, 5.0f));
			TextRenderer* waveTextRend = new TextRenderer("Wave");
			AddRenderer(waveTitle, UI2, waveTextRend);
		Entity& waveNumUI = CreateEntity(waveTitle);
			waveNumUI.Pos(vec3(0.6f, 0.0f, 0.0f));
			NumUIRenderer* waveUIRend = new NumUIRenderer(1);
			AddRenderer(waveNumUI, UI2, waveUIRend);

		/// HP ///
		Entity& hpText = CreateEntity(camera);
			hpText.Pos(vec3(-5.2f, -3.7f, 5.0f));
			AddRenderer(hpText, UI2, new TextRenderer("Health"));
		Entity& hpNum = CreateEntity(camera);
			hpNum.Pos(vec3(-4.5f, -3.7f, 5.0f));
			NumUIRenderer* hpUIRend = new NumUIRenderer(STARTING_HP);
			AddRenderer(hpNum, UI2, hpUIRend);


		/// Tower Selection Menu
		
		Entity& towerMenu = CreateEntity(camera);
			towerMenu.Pos(vec3(-1.0f, -3.7f, 5.0f));
			towerMenu.Rot(vec3(10.0f, 0.0f, 0.0f));
			towerMenu.Scale(0.28);

			// Shooter
			Entity& shooterText = CreateEntity(towerMenu);
				shooterText.Pos(vec3(-1.0f, -1.0f, 0.0f));
				AddRenderer(shooterText, UI2, new NumUIRenderer(SHOOTER_PRICE));

				Entity& shooterIcon = CreateEntity(shooterText);
					shooterIcon.Pos(vec3(0.3f, 2.5f, 0.0f));
					AddRenderer(shooterIcon, UI2, new OBJRenderer(".\\TestData\\cone.obj", vec3(0.0f, 0.0f, 1.0f)));
			
			// Laser
			Entity& laserText = CreateEntity(towerMenu);
				laserText.Pos(vec3(3.0f, -1.0f, 0.0f));
				AddRenderer(laserText, UI2, new NumUIRenderer(LASER_PRICE));

				Entity& laserIcon = CreateEntity(laserText);
					laserIcon.Pos(vec3(0.3f, 2.3f, 0.0f));
					AddRenderer(laserIcon, UI2, new OBJRenderer(".\\TestData\\ico.obj", vec3(1.0f, 0.0f, 0.0f)));
			
			// Saw
			Entity& sawText = CreateEntity(towerMenu);
				sawText.Pos(vec3(7.0f, -1.0f, 0.0f));
				NumUIRenderer* sawTextRend = new NumUIRenderer(10);
				AddRenderer(sawText, UI2, sawTextRend);

				Entity& sawIcon = CreateEntity(sawText);
					sawIcon.Pos(vec3(0.6f, 2.3f, 0.0f));
					sawIcon.Rot(vec3(-70.0f, 0.0f, 0.0f));
					sawIcon.Scale(vec3(0.7f));
					AddRenderer(sawIcon, UI2, new OBJRenderer(".\\TestData\\donut.obj", vec3(0.3f, 0.3f, 1.0f)));

			// Add behavior to tower menu
			TowerMenuB* towerMenuBehavior = new TowerMenuB(shooterIcon, laserIcon, sawIcon);
			AddBehavior(towerMenu, group2, towerMenuBehavior);

#pragma endregion 

		//// PATH ////
#pragma region PathCreation
		std::vector<vec3> path;

		// Start Node
		path.push_back(vec3(-28.0f, 12.0f, 0.0f));
		
		AddToPath(path, RIGHT, 3);
		AddToPath(path, FORWARD, 2);
		AddToPath(path, DOWN, 2);
		AddToPath(path, BACK, 2);
		AddToPath(path, LEFT, 2);
		AddToPath(path, DOWN, 3);
		AddToPath(path, RIGHT, 4);
		AddToPath(path, UP, 3);
		AddToPath(path, RIGHT, 3);
		AddToPath(path, BACK, 1);
		AddToPath(path, UP, 3);

		CreatePath(path, layer1, cursorSelectionCol, RED);
#pragma endregion
	


		//// Towers ////
#pragma region Towers
		
		// Bullet pool used by all shooters
		ObjectPool& bulletPool = CreatePool("bulletPool", new BulletPool(100, *this, group1, layer2, bulletsCol));

		// 10 Shooters
		ObjectPool& shooterPool = CreatePool("shooterPool",
			new ShooterPool(10, *this, group1, layer2, towerSightCol, cursorSelectionCol, bulletPool));
		
		// 10 Lasers
		ObjectPool& laserPool = CreatePool("laserPool",
				new LaserPool(10, *this, 
				group1,
				layer1, layer2, 
				towerSightCol, cursorSelectionCol, bulletsCol));

		// 3 Saws
		Entity& saw = CreateEntity("saw");
			Entity& hSpinner = CreateEntity(saw);
				Entity& hBlade = CreateEntity(hSpinner);
					AddRenderer(hBlade, layer2, new OBJRenderer(".\\TestData\\donut.obj", vec3(0.3f, 0.3f, 1.0f)));
					AddCollider(hBlade, bulletsCol, new SphereCollider(2.0f));
					AddBehavior(hBlade, group1, new SawBladeB());
					hBlade.Pos(vec3(3.0f, 0.0f, 0.0f));
				hSpinner.Active(false);
			
					Entity& vSpinner = CreateEntity(saw);
				Entity& vBlade = CreateEntity(vSpinner);
					AddRenderer(vBlade, layer2, new OBJRenderer(".\\TestData\\donut.obj", vec3(0.3f, 0.3f, 1.0f)));
					AddCollider(vBlade, bulletsCol, new SphereCollider(2.0f));
					AddBehavior(vBlade, group1, new SawBladeB());
					vBlade.Pos(vec3(0.0f, 3.0f, 0.0f));
					vBlade.Rot(vec3(0.0f, 0.0f, 90.0f));
				vSpinner.Active(false);
			
			Entity& dSpinner = CreateEntity(saw);
				Entity& dBlade = CreateEntity(dSpinner);
					AddRenderer(dBlade, layer2, new OBJRenderer(".\\TestData\\donut.obj", vec3(0.3f, 0.3f, 1.0f)));
					AddCollider(dBlade, bulletsCol, new SphereCollider(2.0f));
					AddBehavior(dBlade, group1, new SawBladeB());
					dBlade.Pos(vec3(0.0f, -0.2f, 0.0f));
					dBlade.Scale(1.5f);
				dSpinner.Active(false);

		// Give saw the spinners
		AddBehavior(saw, group1, new SawB(hSpinner, vSpinner, dSpinner));

#pragma endregion

	

		//// Monkeys ////

		// Waves //

		std::vector<Wave> waves;

		Wave wave1;
		wave1.AddToWave(10, STANDARD, 0.1f);
		wave1.AddToWave(1, BOSS, 1.0f);
		waves.push_back(wave1);

		Wave wave2;
		wave2.AddToWave(3, BRUTE, 0.5f);
		wave2.AddToWave(20, TINY, 0.2f);
		waves.push_back(wave2);

		Wave wave3;
		wave3.AddToWave(1, BRUTE, 1.5f);
		waves.push_back(wave3);

		Wave wave4;
		wave4.AddToWave(3, BRUTE, 0.8f);
		wave4.AddToWave(2, BRUTE, 0.6f);
		waves.push_back(wave4);


		// Banana
		Entity& banana = CreateEntity();
		banana.Scale(0.05f);
		banana.Pos(path.back());
		AddBehavior(banana, group1, new RotatorB(vec3(0.0f, 50.0f, 0.0f)));
		AddRenderer(banana, layer2, new OBJRenderer(".\\TestData\\banana.obj", vec3(1.0f, 1.0f, 0.0f)));

		// Barrel at spawn
		Entity& barrel = CreateEntity();
		barrel.Scale(0.4f);
		barrel.Pos(vec3(path.front().x, path.front().y - 2, path.front().z));
		AddRenderer(barrel, layer2, new OBJRenderer(".\\TestData\\barrel.obj", vec3(205.0f / 255.0f, 133.0f / 255.0f, 63.0f / 255.0f)));


		// Giant evil monkey when you lose
		Entity& giantMonkey = CreateEntity();
		giantMonkey.Pos(vec3(0.0f, 0.0f, 10000.0f));
		giantMonkey.Rot(vec3(0.0f, 180.0f, 0.0f));
		AddRenderer(giantMonkey, layer2, new OBJRenderer(".\\TestData\\monkey.obj", vec3(1.0f, 0.0f, 0.0f)));
		giantMonkey.Active(false);
		
		Entity& loseText = CreateEntity(camera);
		loseText.Pos(vec3(-0.1f, 0.0f, 0.0f));
		AddRenderer(loseText, UI2, new TextRenderer("GAME OVER!", vec3(1.0f)));
		loseText.Active(false);

		Entity& winText = CreateEntity(camera);
		winText.Pos(vec3(-0.1f, 0.0f, 0.0f));
		AddRenderer(winText, UI2, new TextRenderer("YOU WIN!", vec3(1.0f)));
		winText.Active(false);
		

		// Cursor
		Entity& cursor = CreateEntity("cursor");
		
		// Monkey Spawner
		Entity& monkeySpawner = CreateEntity();
			ObjectPool& monkeyPool = 
				CreatePool("monkeyPool",new MonkeyPool(cursor, monkeySpawner, 50, *this, group1, layer1, towerSightCol, bulletsCol, path));
			BarrelOfMonkeysB* barrelB = 
				new BarrelOfMonkeysB(loseText, winText, banana, giantMonkey, barrel, cursor, *waveUIRend, waves, monkeyPool);
			AddBehavior(monkeySpawner, group1, barrelB);

		// Cursor
		AddRenderer(cursor, layer2, new OBJRenderer(".\\TestData\\ufo.obj"));
		AddCollider(cursor, cursorSelectionCol, new SphereCollider());
		AddBehavior(cursor, group1, new CursorB(*barrelB, *towerMenuBehavior, shooterPool, laserPool, saw,
			*moneyRend, *sawTextRend, *hpUIRend, 35.0f));




	}

	// Called after all entities and collision are updated
	void PostUpdate() override
	{
		
	}
};