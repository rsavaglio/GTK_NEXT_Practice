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