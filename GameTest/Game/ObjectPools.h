#pragma once
#include "gtk/gtk.h"
#include "gtk/gtkMath.hpp"

#include "Components.h"
#include "Renderers.h"
#include "Colliders.h"

using namespace gtk;


class BulletPool : public ObjectPool
{
private:

	UpdateGroup _group;
	RenderLayer _layer;
	CollisionGroup _colGroup;

public:

	BulletPool(int count, Scene& scene, gtk::UpdateGroup& group, gtk::RenderLayer& layer, gtk::CollisionGroup colGroup)
		: _group(group), _layer(layer), _colGroup(colGroup), ObjectPool(count, scene)
	{
		GeneratePool();
	}

	virtual Entity& Create(const vec3& vec = vec3())
	{
		Entity* ent = _pool.front();
		_pool.pop();
		_pool.push(ent);

		ent->Active(true);
		ent->Rot(vec);

		return *ent;
	}

	void GeneratePool() override
	{
		for (int i = 0; i < _count; i++)
		{
			// Create entity and add it to pool
			Entity* entity = &_scene.CreateEntity();
			_pool.push(entity);

			// Setup here
			_scene.AddBehavior(*entity, _group, new BulletB());
			_scene.AddRenderer(*entity, _layer, new OBJRenderer(".\\TestData\\ico.obj", vec3(0.8f, 0.5, 0.3f)));
			_scene.AddCollider(*entity, _colGroup, new SphereCollider());
			entity->Scale(0.5f);
			
			entity->Active(false);
		}

	}



};


class MonkeyPool : public ObjectPool
{

public:

	MonkeyPool(Entity& barrel, int count, Scene& scene,
		const gtk::UpdateGroup& group, const gtk::RenderLayer& layer, const gtk::CollisionGroup colGroup,
		std::vector<vec3> path)
		: _barrel(barrel), _group(group), _layer(layer), _colGroup(colGroup),
		_path(path), ObjectPool(count, scene)
	{
		GeneratePool();
	}

	void GeneratePool() override
	{
		for (int i = 0; i < _count; i++)
		{
			// Create entity and add it to pool
			Entity* entity = &_scene.CreateEntity("monkey");
			_pool.push(entity);

			// Setup here
			_scene.AddBehavior(*entity, _group, new MonkeyB(_path));
			_scene.AddRenderer(*entity, _layer, new OBJRenderer(".\\TestData\\monkey.obj", vec3(1.0f, 0.0f, 0.0f)));
			_scene.AddCollider(*entity, _colGroup, new SphereCollider());

			entity->Active(false);
		}
	}

private:

	std::vector<vec3> _path;

	Entity& _barrel;
	UpdateGroup _group;
	RenderLayer _layer;
	CollisionGroup _colGroup;


};