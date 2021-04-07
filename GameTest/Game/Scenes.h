#pragma once

#include "gtk/gtk.h"

#include "Components.h"
#include "Renderers.h"
#include "ObjectPools.h"
#include "Colliders.h"
#include "enums.h"
#include "Path.h"

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
		CollisionGroup colGroup = CreateCollisionGroup();

		Entity& camera = CreateEntity();
			AddCamera(camera, new PerspectiveCam(1, 100, 80));

		Entity& parent = CreateEntity();
			AddBehavior(parent, group, new BehaviorTemplate());
			AddRenderer(parent, layer, new RendTemplate());

		Entity& child = CreateEntity(parent);
			AddBehavior(child, group, new BehaviorTemplate());
			AddRenderer(child, layer, new RendTemplate());
			AddCollider(child, colGroup, new SphereCollider());

	}

	// Called after all entities are updated
	void PostUpdate() override
	{

	}
};

class TD_Level_2 : public gtk::Scene
{

public:

	Path _path;

	TD_Level_2(gtk::Game& game) : gtk::Scene(game) {}

protected:

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


		//// Models ////

		Model& monkeyModel = CreateModel(".\\TestData\\monkey.obj", "monkey");
		Model& donutModel  = CreateModel(".\\TestData\\donut.obj", "donut");
		Model& sphereModel = CreateModel(".\\TestData\\sphere.obj", "sphere");
		Model& coneModel   = CreateModel(".\\TestData\\cone.obj", "cone");
		Model& icoModel    = CreateModel(".\\TestData\\ico.obj", "ico");
		Model& bananaModel = CreateModel(".\\TestData\\banana.obj", "banana");
		Model& barrelModel = CreateModel(".\\TestData\\barrel.obj", "barrel");
		Model& ufoModel    = CreateModel(".\\TestData\\ufo.obj", "ufo");

		//// Camera ////

		Entity& tripod = CreateEntity();
			tripod.Pos(vec3(0.0f, 0.0f, -25.0f));

		Entity& camera = CreateEntity(tripod);
			camera.Rot(vec3(0.0f, 0.0f, 0.0f));
			AddCamera(camera, new PerspectiveCam(1, 1000, 70));
			AddBehavior(camera, group1, new CameraB(100.0f));

		// Music
		Entity& conductor = CreateEntity();
			AddBehavior(conductor, group1, new MusicB());


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
					AddRenderer(shooterIcon, UI2, new OBJRenderer(coneModel, vec3(0.0f, 0.0f, 1.0f)));
			
			// Laser
			Entity& laserText = CreateEntity(towerMenu);
				laserText.Pos(vec3(3.0f, -1.0f, 0.0f));
				AddRenderer(laserText, UI2, new NumUIRenderer(LASER_PRICE));

				Entity& laserIcon = CreateEntity(laserText);
					laserIcon.Pos(vec3(0.3f, 2.3f, 0.0f));
					AddRenderer(laserIcon, UI2, new OBJRenderer(icoModel, vec3(1.0f, 0.0f, 0.0f)));
			
			// Saw
			Entity& sawText = CreateEntity(towerMenu);
				sawText.Pos(vec3(7.0f, -1.0f, 0.0f));
				NumUIRenderer* sawTextRend = new NumUIRenderer(SAW_PRICE_1);
				AddRenderer(sawText, UI2, sawTextRend);

				Entity& sawIcon = CreateEntity(sawText);
					sawIcon.Pos(vec3(0.6f, 2.3f, 0.0f));
					sawIcon.Rot(vec3(-70.0f, 0.0f, 0.0f));
					sawIcon.Scale(vec3(0.7f));
					AddRenderer(sawIcon, UI2, new OBJRenderer(donutModel, vec3(0.3f, 0.3f, 1.0f)));

			// Add behavior to tower menu
			TowerMenuB* towerMenuBehavior = new TowerMenuB(shooterIcon, laserIcon, sawIcon);
			AddBehavior(towerMenu, group2, towerMenuBehavior);

#pragma endregion 

		//// PATH ////
#pragma region PathCreation

		// Start Node
		_path.Init(vec3(-28.0f, 12.0f, 0.0f));
		
		// Add nodes
		_path.Add(RIGHT, 3);
		_path.Add(FORWARD, 2);
		_path.Add(DOWN, 2);
		_path.Add(BACK, 2);
		_path.Add(LEFT, 2);
		_path.Add(DOWN, 3);
		_path.Add(BACK, 1);
		_path.Add(RIGHT, 1);
		_path.Add(FORWARD, 1);
		_path.Add(RIGHT, 3);
		_path.Add(UP, 3);
		_path.Add(RIGHT, 3);
		_path.Add(BACK, 1);
		_path.Add(UP, 3);

		// Create entities
		_path.CreatePathinScene(*this, layer1, cursorSelectionCol);

#pragma endregion
	


		//// Towers ////
#pragma region Towers
		
		// Bullet pool used by all shooters
		ObjectPool& bulletPool = CreatePool("bulletPool", new BulletPool(100, *this, group1, layer2, bulletsCol));

		// 10 Shooters
		ObjectPool& shooterPool = CreatePool("shooterPool",
			new ShooterPool(MAX_SHOOTERS, *this, group1, layer2, towerSightCol, cursorSelectionCol, bulletPool));
		
		// 10 Lasers
		ObjectPool& laserPool = CreatePool("laserPool",
				new LaserPool(MAX_LASERS, *this,
				group1,
				layer1, layer2, 
				towerSightCol, cursorSelectionCol, bulletsCol));

		// 3 Saws
		Entity& saw = CreateEntity("saw");
			Entity& hSpinner = CreateEntity(saw);
				Entity& hBlade = CreateEntity(hSpinner);
					AddRenderer(hBlade, layer2, new OBJRenderer(donutModel, vec3(0.3f, 0.3f, 1.0f)));
					AddCollider(hBlade, bulletsCol, new SphereCollider(2.0f));
					AddBehavior(hBlade, group1, new SawBladeB());
					hBlade.Pos(vec3(3.0f, 0.0f, 0.0f));
				hSpinner.Active(false);
			
					Entity& vSpinner = CreateEntity(saw);
				Entity& vBlade = CreateEntity(vSpinner);
					AddRenderer(vBlade, layer2, new OBJRenderer(donutModel, vec3(0.3f, 0.3f, 1.0f)));
					AddCollider(vBlade, bulletsCol, new SphereCollider(2.0f));
					AddBehavior(vBlade, group1, new SawBladeB());
					vBlade.Pos(vec3(0.0f, 3.0f, 0.0f));
					vBlade.Rot(vec3(0.0f, 0.0f, 90.0f));
				vSpinner.Active(false);
			
			Entity& dSpinner = CreateEntity(saw);
				Entity& dBlade = CreateEntity(dSpinner);
					AddRenderer(dBlade, layer2, new OBJRenderer(donutModel, vec3(0.3f, 0.3f, 1.0f)));
					AddCollider(dBlade, bulletsCol, new SphereCollider(2.0f));
					AddBehavior(dBlade, group1, new SawBladeB());
					dBlade.Pos(vec3(0.0f, -0.2f, 0.0f));
					dBlade.Scale(1.5f);
				dSpinner.Active(false);

		// Give saw the spinners
		AddBehavior(saw, group1, new SawB(hSpinner, vSpinner, dSpinner));

#pragma endregion


		// Waves //

		std::vector<Wave> waves;

		Wave wave1;
		wave1.Add(12, STANDARD, 2.0f);
		waves.push_back(wave1);

		Wave wave2;
		wave2.Add(6, TINY, 1.0f);
		wave2.Add(6, STANDARD, 2.0f);
		waves.push_back(wave2);

		Wave wave3;
		wave3.Add(12, TINY, 1.0f);
		wave3.Add(8, STANDARD, 1.0f);
		wave3.Add(3, BRUTE, 3.0f);
		waves.push_back(wave3);

		Wave wave4;
		wave4.Add(6, TINY, 0.5f);
		wave4.Add(2, BRUTE, 3.0f);
		wave4.Add(1, STANDARD, 4.0f);
		wave4.Add(5, STANDARD, 2.0f);
		wave4.Add(6, TINY, 0.5f);
		waves.push_back(wave4);

		Wave wave5;
		wave3.Add(1, STANDARD, 1.0f);
		wave3.Add(4, TINY, 1.0f);
		wave5.Add(1, BOSS, 3.0f);
		waves.push_back(wave5);
		
		Wave wave6;
		wave6.Add(10, TINY, 0.2f);
		wave6.Add(3, BRUTE, 0.1f);
		wave6.Add(6, STANDARD, 0.5f);
		wave6.Add(6, STANDARD, 1.0f);
		wave6.Add(3, BRUTE, 1.0f);
		waves.push_back(wave6);

		Wave wave7;
		wave7.Add(3, BRUTE, 1.0f);
		wave7.Add(3, BRUTE, 0.7f);
		wave7.Add(5, BRUTE, 1.0f);
		wave7.Add(6, BRUTE, 0.7f);
		wave7.Add(1, BOSS, 1.0f);
		waves.push_back(wave7);

		Wave wave8;
		wave8.Add(3, STANDARD, 1.0f);
		wave8.Add(20, TINY, 0.4f);
		wave8.Add(4, BRUTE, 1.0f);
		wave8.Add(7, STANDARD, 0.2f);
		wave8.Add(1, BOSS, 1.0f);
		waves.push_back(wave8);

		Wave wave9;
		wave9.Add(20, TINY, 0.1f);
		wave9.Add(6, STANDARD, 0.2f);
		wave9.Add(5, BRUTE, 0.7f);
		wave9.Add(1, BOSS, 1.0f);
		wave9.Add(10, TINY, 0.3f);
		waves.push_back(wave9);

		Wave wave10;
		wave10.Add(1, TINY, 0.1f);
		wave10.Add(1, STANDARD, 0.2f);
		wave10.Add(1, BRUTE, 0.7f);
		wave10.Add(5, BOSS, 5.0f);
		wave10.Add(1, MEGA, 3.0f);
		waves.push_back(wave10);


		// Banana
		Entity& banana = CreateEntity();
		banana.Scale(0.05f);
		banana.Pos(_path.nodes.back());
		AddBehavior(banana, group1, new RotatorB(vec3(0.0f, 50.0f, 0.0f)));
		AddRenderer(banana, layer2, new OBJRenderer(bananaModel, vec3(1.0f, 1.0f, 0.0f)));

		// Barrel at spawn
		Entity& barrel = CreateEntity();
		barrel.Scale(0.4f);
		barrel.Pos(vec3(_path.nodes.front().x, _path.nodes.front().y - 2, _path.nodes.front().z));
		AddRenderer(barrel, layer2, new OBJRenderer(barrelModel, vec3(0.6f, 0.4f, 0.2f)));


		// Giant evil monkey when you lose
		Entity& giantMonkey = CreateEntity();
		giantMonkey.Pos(vec3(0.0f, 0.0f, 10000.0f));
		giantMonkey.Rot(vec3(0.0f, 180.0f, 0.0f));
		AddRenderer(giantMonkey, layer2, new OBJRenderer(monkeyModel, vec3(1.0f, 0.0f, 0.0f)));
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
				CreatePool("monkeyPool",new MonkeyPool(cursor, monkeySpawner, 50, *this, group1, layer1, towerSightCol, bulletsCol, _path.nodes));
			BarrelOfMonkeysB* barrelB = 
				new BarrelOfMonkeysB(conductor, loseText, winText, banana, giantMonkey, barrel, cursor, *waveUIRend, waves, monkeyPool);
			AddBehavior(monkeySpawner, group1, barrelB);

		// Cursor
		AddRenderer(cursor, layer2, new OBJRenderer(ufoModel));
		AddCollider(cursor, cursorSelectionCol, new SphereCollider());
		AddBehavior(cursor, group1, new CursorB(*barrelB, *towerMenuBehavior, shooterPool, laserPool, saw,
			*moneyRend, *sawTextRend, *hpUIRend, 35.0f));

	}

	// Called after all entities and collision are updated
	void PostUpdate() override
	{
		
	}
};

class TD_Level_1 : public gtk::Scene
{

public:

	Path _path;

	TD_Level_1(gtk::Game& game) : gtk::Scene(game) {}

protected:

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

		//// Models ////

		Model& monkeyModel = CreateModel(".\\TestData\\monkey.obj", "monkey");
		Model& donutModel = CreateModel(".\\TestData\\donut.obj", "donut");
		Model& sphereModel = CreateModel(".\\TestData\\sphere.obj", "sphere");
		Model& coneModel = CreateModel(".\\TestData\\cone.obj", "cone");
		Model& icoModel = CreateModel(".\\TestData\\ico.obj", "ico");
		Model& bananaModel = CreateModel(".\\TestData\\banana.obj", "banana");
		Model& barrelModel = CreateModel(".\\TestData\\barrel.obj", "barrel");
		Model& ufoModel = CreateModel(".\\TestData\\ufo.obj", "ufo");


		//// Camera ////

		Entity& tripod = CreateEntity();
		tripod.Pos(vec3(0.0f, 0.0f, -25.0f));

		Entity& camera = CreateEntity(tripod);
		camera.Rot(vec3(0.0f, 0.0f, 0.0f));
		AddCamera(camera, new PerspectiveCam(1, 1000, 70));
		AddBehavior(camera, group1, new CameraB(100.0f));

		//// Music ////

		Entity& conductor = CreateEntity();
			AddBehavior(conductor, group1, new MusicB());


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
		AddRenderer(shooterIcon, UI2, new OBJRenderer(coneModel, vec3(0.0f, 0.0f, 1.0f)));

		// Laser
		Entity& laserText = CreateEntity(towerMenu);
		laserText.Pos(vec3(3.0f, -1.0f, 0.0f));
		AddRenderer(laserText, UI2, new NumUIRenderer(LASER_PRICE));

		Entity& laserIcon = CreateEntity(laserText);
		laserIcon.Pos(vec3(0.3f, 2.3f, 0.0f));
		AddRenderer(laserIcon, UI2, new OBJRenderer(icoModel, vec3(1.0f, 0.0f, 0.0f)));

		// Saw
		Entity& sawText = CreateEntity(towerMenu);
		sawText.Pos(vec3(7.0f, -1.0f, 0.0f));
		NumUIRenderer* sawTextRend = new NumUIRenderer(SAW_PRICE_1);
		AddRenderer(sawText, UI2, sawTextRend);

		Entity& sawIcon = CreateEntity(sawText);
		sawIcon.Pos(vec3(0.6f, 2.3f, 0.0f));
		sawIcon.Rot(vec3(-70.0f, 0.0f, 0.0f));
		sawIcon.Scale(vec3(0.7f));
		AddRenderer(sawIcon, UI2, new OBJRenderer(donutModel, vec3(0.3f, 0.3f, 1.0f)));

		// Add behavior to tower menu
		TowerMenuB* towerMenuBehavior = new TowerMenuB(shooterIcon, laserIcon, sawIcon);
		AddBehavior(towerMenu, group2, towerMenuBehavior);

#pragma endregion 

		//// PATH ////
#pragma region PathCreation

		// Start Node
		_path.Init(vec3(-15.0f, -6.0f, 0.0f));

		_path.Add(UP, 3);
		_path.Add(RIGHT, 5);
		_path.Add(DOWN, 3);
		_path.Add(LEFT, 3);

		_path.CreatePathinScene(*this, layer1, cursorSelectionCol);

#pragma endregion



		//// Towers ////
#pragma region Towers

		// Bullet pool used by all shooters
		ObjectPool& bulletPool = CreatePool("bulletPool", new BulletPool(100, *this, group1, layer2, bulletsCol));

		// 10 Shooters
		ObjectPool& shooterPool = CreatePool("shooterPool",
			new ShooterPool(MAX_SHOOTERS, *this, group1, layer2, towerSightCol, cursorSelectionCol, bulletPool));

		// 10 Lasers
		ObjectPool& laserPool = CreatePool("laserPool",
			new LaserPool(MAX_LASERS, *this,
				group1,
				layer1, layer2,
				towerSightCol, cursorSelectionCol, bulletsCol));

		// 3 Saws
		Entity& saw = CreateEntity("saw");
		Entity& hSpinner = CreateEntity(saw);
		Entity& hBlade = CreateEntity(hSpinner);
		AddRenderer(hBlade, layer2, new OBJRenderer(donutModel, vec3(0.3f, 0.3f, 1.0f)));
		AddCollider(hBlade, bulletsCol, new SphereCollider(2.0f));
		AddBehavior(hBlade, group1, new SawBladeB());
		hBlade.Pos(vec3(3.0f, 0.0f, 0.0f));
		hSpinner.Active(false);

		Entity& vSpinner = CreateEntity(saw);
		Entity& vBlade = CreateEntity(vSpinner);
		AddRenderer(vBlade, layer2, new OBJRenderer(donutModel, vec3(0.3f, 0.3f, 1.0f)));
		AddCollider(vBlade, bulletsCol, new SphereCollider(2.0f));
		AddBehavior(vBlade, group1, new SawBladeB());
		vBlade.Pos(vec3(0.0f, 3.0f, 0.0f));
		vBlade.Rot(vec3(0.0f, 0.0f, 90.0f));
		vSpinner.Active(false);

		Entity& dSpinner = CreateEntity(saw);
		Entity& dBlade = CreateEntity(dSpinner);
		AddRenderer(dBlade, layer2, new OBJRenderer(donutModel, vec3(0.3f, 0.3f, 1.0f)));
		AddCollider(dBlade, bulletsCol, new SphereCollider(2.0f));
		AddBehavior(dBlade, group1, new SawBladeB());
		dBlade.Pos(vec3(0.0f, -0.2f, 0.0f));
		dBlade.Scale(1.5f);
		dSpinner.Active(false);

		// Give saw the spinners
		AddBehavior(saw, group1, new SawB(hSpinner, vSpinner, dSpinner));

#pragma endregion


		// Waves //

		std::vector<Wave> waves;

		Wave wave1;
		wave1.Add(12, STANDARD, 2.0f);
		waves.push_back(wave1);

		Wave wave2;
		wave2.Add(6, STANDARD, 2.0f);
		wave2.Add(15, TINY, 0.5f);
		waves.push_back(wave2);

		Wave wave3;
		wave2.Add(2, STANDARD, 2.0f);
		wave2.Add(3, TINY, 2.0f);
		wave3.Add(1, BRUTE, 1.0f);
		waves.push_back(wave3);

		Wave wave4;
		wave4.Add(5, STANDARD, 1.0f);
		wave4.Add(2, BRUTE, 1.0f);
		wave4.Add(3, TINY, 0.5f);
		wave4.Add(1, STANDARD, 0.1f);
		waves.push_back(wave4);

		Wave wave5;
		wave4.Add(1, TINY, 0.5f);
		wave4.Add(1, TINY, 0.5f);
		wave4.Add(1, TINY, 0.5f);
		wave5.Add(1, BOSS, 0.2f);
		waves.push_back(wave5);

		// Banana
		Entity& banana = CreateEntity();
		banana.Scale(0.05f);
		banana.Pos(_path.nodes.back());
		AddBehavior(banana, group1, new RotatorB(vec3(0.0f, 50.0f, 0.0f)));
		AddRenderer(banana, layer2, new OBJRenderer(bananaModel, vec3(1.0f, 1.0f, 0.0f)));

		// Barrel at spawn
		Entity& barrel = CreateEntity();
		barrel.Scale(0.4f);
		barrel.Pos(vec3(_path.nodes.front().x, _path.nodes.front().y - 2, _path.nodes.front().z));
		AddRenderer(barrel, layer2, new OBJRenderer(barrelModel, vec3(0.6f, 0.4f, 0.2f)));


		// Giant evil monkey when you lose
		Entity& giantMonkey = CreateEntity();
		giantMonkey.Pos(vec3(0.0f, 0.0f, 10000.0f));
		giantMonkey.Rot(vec3(0.0f, 180.0f, 0.0f));
		AddRenderer(giantMonkey, layer2, new OBJRenderer(monkeyModel, vec3(1.0f, 0.0f, 0.0f)));
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
			CreatePool("monkeyPool", new MonkeyPool(cursor, monkeySpawner, 50, *this, group1, layer1, towerSightCol, bulletsCol, _path.nodes));
		BarrelOfMonkeysB* barrelB =
			new BarrelOfMonkeysB(conductor, loseText, winText, banana, giantMonkey, barrel, cursor, *waveUIRend, waves, monkeyPool);
		AddBehavior(monkeySpawner, group1, barrelB);

		// Cursor
		AddRenderer(cursor, layer2, new OBJRenderer(ufoModel));
		AddCollider(cursor, cursorSelectionCol, new SphereCollider());
		AddBehavior(cursor, group1, new CursorB(*barrelB, *towerMenuBehavior, shooterPool, laserPool, saw,
			*moneyRend, *sawTextRend, *hpUIRend, 35.0f));

	}

	// Called after all entities and collision are updated
	void PostUpdate() override
	{

	}
};

class MainMenu : public gtk::Scene
{

public:

	Path _path;

	MainMenu(gtk::Game& game) : gtk::Scene(game) {}

protected:


	// Called by game when scene starts
	void Setup() override
	{
		using namespace gtk;

		UpdateGroup group = CreateUpdateGroup();
		RenderLayer layer = CreateRenderLayer();
		CollisionGroup colGroup = CreateCollisionGroup();

		/// Models

		Model& monkeyModel = CreateModel(".\\TestData\\monkey.obj", "monkey");
		Model& bananaModel = CreateModel(".\\TestData\\banana.obj", "banana");
		Model& coneModel = CreateModel(".\\TestData\\cone2.obj", "cone");


		// Start Node
		_path.Init(vec3(-15.0f, -6.0f, 0.0f));

		_path.Add(UP, 3);
		_path.Add(RIGHT, 5);
		_path.Add(DOWN, 3);
		_path.Add(LEFT, 5);

		_path.CreatePathinScene(*this, layer, colGroup);


		Entity& camera = CreateEntity();
			camera.Pos(vec3(0.0f, 3.0f, -25.0f));
			AddCamera(camera, new PerspectiveCam(1, 1000, 70));

		Entity& title = CreateEntity();
			title.Pos(vec3(-3.0f, 5.5f, 0.0f));
			AddRenderer(title, layer, new TextRenderer("Monkey Tunnel", vec3(1.0f, 1.0f, 1.0f)));

		Entity& monkey = CreateEntity();
			monkey.Rot(vec3(0.0f, 180.0f, 0.0f));
			monkey.Scale(3.0f);
			AddBehavior(monkey, group, new MenuMonkeyB(0, 2.0f, 120.0f, _path.nodes));
			AddRenderer(monkey, layer, new OBJRenderer(monkeyModel, vec3(0.8f, 0.5f, 0.0f)));

		Entity& banana = CreateEntity();
			banana.Scale(0.05f);
			AddBehavior(banana, group, new MenuMonkeyB(5, 2.0f, -80.0f, _path.nodes));
			AddRenderer(banana, layer, new OBJRenderer(bananaModel, vec3(0.7f, 0.7f, 0.0f)));


		Entity& level1Text = CreateEntity();
		level1Text.Pos(vec3(-6.0f, 0.0f, 0.0f));
			AddRenderer(level1Text, layer, new TextRenderer("Easy", vec3(1.0f, 1.0f, 1.0f)));

		Entity& level2Text = CreateEntity();
			level2Text.Pos(vec3(3.0f, 0.0f, 0.0f));
			AddRenderer(level2Text, layer, new TextRenderer("Tough", vec3(1.0f, 1.0f, 1.0f)));

		Entity& selector = CreateEntity();
			selector.Rot(vec3(180.0f, 0.0f, 0.0f));
			AddBehavior(selector, group, new MenuSelectorB(level1Text, level2Text, 30.0f));
			AddRenderer(selector, layer, new OBJRenderer(coneModel, vec3(0.0f, 0.0f, 1.0f)));


			//// Music ////

		Entity& conductor = CreateEntity();
			AddBehavior(conductor, group, new MusicB(MAX_VOL));
		
		
	}

	// Called after all entities are updated
	void PostUpdate() override
	{

	}
};