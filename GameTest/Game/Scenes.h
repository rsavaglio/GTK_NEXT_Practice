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
		RenderLayer rendLayer = CreateRenderLayer();

		Entity* entity = CreateEntity();
		AddComponent(new CompTemplate(entity, compGroup));
		AddRenderer(new RendTemplate(entity, rendLayer));

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

		RenderLayer rendLayer = CreateRenderLayer();

		Entity* player = CreateEntity();
			player->SetPos(0.0f, 0.0f, 0.0f);
			AddComponent(new PlayerController(player, controllers, 10.0f));
			AddRenderer(new SpriteRenderer(player, rendLayer, App::CreateSprite(".\\TestData\\Test.bmp", 8, 4)));
		
		MakeCubeStack(vec3(0), controllers, rendLayer);


		m_Camera.SetPos(0, 0, -500.0f);

	}

	// Called after all entities are updated but before renderer
	void PostUpdate() override
	{

	}

private:

	void MakeCubeStack(gtk::vec3 position, const gtk::CompGroup& group, const gtk::RenderLayer& layer)
	{
		using namespace gtk;

		Entity* cube = CreateEntity();
			cube->SetPos(position);
			cube->SetRotY(45.0f);
			cube->SetScale(100.0f, 100.0f, 100.0f);
			AddComponent(new RotaterComp(cube, group, gtk::vec3(0.0f, 1.0f, 0)));
			AddRenderer(new CubeRenderer(cube, layer));

		Entity* childCube = CreateEntity(cube);
			childCube->SetPos(1.5f, 1.5f, 1.0f);
			childCube->SetScale(0.5f, 0.5f, 0.5f);
			AddComponent(new RotaterComp(childCube, group, gtk::vec3(0, 1.0f, 0)));
			AddRenderer(new CubeRenderer(childCube, layer));

		Entity* babyCube = CreateEntity(childCube);
			babyCube->SetPos(1.5f, 1.5f, 1.5f);
			babyCube->SetScale(0.5f, 0.5f, 0.5f);
			AddRenderer(new CubeRenderer(babyCube, layer));

	
	}
};