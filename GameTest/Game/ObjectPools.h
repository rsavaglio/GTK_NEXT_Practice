#pragma once
#include "gtk/gtk.h"
#include "gtk/gtkMath.hpp"

#include "Components.h"
#include "Renderers.h"

using namespace gtk;


class SpherePool : public ObjectPool
{

public:

	SpherePool(int count, Scene& scene, gtk::UpdateGroup& group, gtk::RenderLayer& layer)
		: _group(group), _layer(layer), ObjectPool(count, scene)
	{
		GeneratePool();
	}

	void GeneratePool() override
	{
		for (int i = 0; i < _count; i++)
		{
			// Create entity and add it to pool
			Entity* entity = &_scene.CreateEntity();
			_pool.push_back(entity);
			entity->Active(false);

			// Setup here
			_scene.AddBehavior(*entity, _group, new SphereController());
			_scene.AddRenderer(*entity, _layer, new OBJRenderer(".\\TestData\\sphere.obj"));
			entity->Pos(vec3(((rand() % 20) - 10), 0.0f, 0.0f));

		}
	}

private:

	UpdateGroup& _group;
	RenderLayer& _layer;

};
