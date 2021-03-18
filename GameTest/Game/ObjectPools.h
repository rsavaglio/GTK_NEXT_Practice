#pragma once
#include "gtk/gtk.h"
#include "gtk/gtkMath.hpp"

#include "Components.h"
#include "Renderers.h"

using namespace gtk;


class BulletPool : public ObjectPool
{

public:

	BulletPool(Entity& shooter, int count, Scene& scene, gtk::UpdateGroup& group, gtk::RenderLayer& layer)
		: _shooter(shooter), _group(group), _layer(layer), ObjectPool(count, scene)
	{
		GeneratePool();
	}

	void GeneratePool() override
	{
		for (int i = 0; i < _count; i++)
		{
			// Create entity and add it to pool
			Entity* entity = &_scene.CreateEntity();
			_pool.push(entity);
			entity->Active(false);

			// Setup here
			_scene.AddBehavior(*entity, _group, new BulletB(_shooter));
			_scene.AddRenderer(*entity, _layer, new OBJRenderer(".\\TestData\\sphere.obj", vec3(0.7f, 0.3, 0.0f)));
			
		}
	}

private:

	Entity& _shooter;

	UpdateGroup& _group;
	RenderLayer& _layer;

};
