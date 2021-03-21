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
			Entity* entity = &_scene.CreateEntity("bullet");
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

private:

	std::vector<vec3> _path;

	Entity& _cursor;
	Entity& _barrel;

	UpdateGroup _group;
	RenderLayer _layer;
	CollisionGroup _colGroup;
	CollisionGroup _colGroup2;

public:

	MonkeyPool(Entity& cursor, Entity& barrel, int count, Scene& scene,
		const gtk::UpdateGroup& group, const gtk::RenderLayer& layer, const gtk::CollisionGroup colGroup, const gtk::CollisionGroup colGroup2,
		std::vector<vec3> path)
		: _path(path), _cursor(cursor), _barrel(barrel), _group(group), _layer(layer), _colGroup(colGroup), _colGroup2(colGroup2),
		ObjectPool(count, scene)
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
			_scene.AddBehavior(*entity, _group, new MonkeyB(_cursor, _path));
			_scene.AddRenderer(*entity, _layer, new OBJRenderer(".\\TestData\\monkey.obj", vec3(1.0f, 0.0f, 0.0f)));
			_scene.AddCollider(*entity, _colGroup, new SphereCollider());
			_scene.AddCollider(*entity, _colGroup2, new SphereCollider());


			entity->Pos(1000.0f);
			entity->Scale(0.0f);

			entity->Active(false);
		}
	}



};


class ShooterPool : public ObjectPool
{
private:

	UpdateGroup _group;
	RenderLayer _layer;
	CollisionGroup _towerSightCol;
	CollisionGroup _cursorSelectionCol;

	ObjectPool& _bulletPool;

public:

	ShooterPool(int count, Scene& scene, gtk::UpdateGroup& group, gtk::RenderLayer& layer, gtk::CollisionGroup sightCol, gtk::CollisionGroup cursorCol,
				ObjectPool& bulletPool)
		: _group(group), _layer(layer), _towerSightCol(sightCol), _cursorSelectionCol(cursorCol), _bulletPool(bulletPool), ObjectPool(count, scene)
	{
		GeneratePool();
	}

	virtual Entity& Create()
	{
		Entity* ent = _pool.front();
		_pool.pop();
		_pool.push(ent);

		ent->Active(true);

		return *ent;
	}

	void GeneratePool() override
	{
		for (int i = 0; i < _count; i++)
		{
			// Create entity and add it to pool
			Entity* entity = &_scene.CreateEntity("shooter");
			_pool.push(entity);

			// Setup here
			_scene.AddBehavior(*entity, _group, new ShooterB(_bulletPool));
			_scene.AddRenderer(*entity, _layer, new OBJRenderer(".\\TestData\\cone.obj", vec3(0.0f, 0.0f, 1.0f)));
			_scene.AddCollider(*entity, _towerSightCol, new SphereCollider(8.0f));
			_scene.AddCollider(*entity, _cursorSelectionCol, new SphereCollider());

			entity->Active(false);
		}

	}



};


class LaserPool : public ObjectPool
{
private:

	UpdateGroup _group;
	RenderLayer _bodyRend;
	RenderLayer _lineRend;
	CollisionGroup _towerSightCol;
	CollisionGroup _cursorSelectionCol;
	CollisionGroup _bulletCol;

public:

	LaserPool(int count, Scene& scene,
		gtk::UpdateGroup& group,
		gtk::RenderLayer& bodyRend, gtk::RenderLayer& lineRend,
		gtk::CollisionGroup sightCol, gtk::CollisionGroup cursorCol, gtk::CollisionGroup bulletCol)
		: _group(group),
		_bodyRend(bodyRend), _lineRend(lineRend),
		_towerSightCol(sightCol), _cursorSelectionCol(cursorCol), _bulletCol(bulletCol),
		ObjectPool(count, scene)
	{
		GeneratePool();
	}

	virtual Entity& Create()
	{
		Entity* ent = _pool.front();
		_pool.pop();
		_pool.push(ent);

		ent->Active(true);

		return *ent;
	}

	void GeneratePool() override
	{
		for (int i = 0; i < _count; i++)
		{
			// Create entity and add it to pool
			Entity* entity = &_scene.CreateEntity("shooter");
			_pool.push(entity);


			// Setup here
			
			LineRenderer* line = new LineRenderer(vec3(1.0f, 0.0f, 0.0f));
			_scene.AddRenderer(*entity, _lineRend, line);
			_scene.AddRenderer(*entity, _bodyRend, new OBJRenderer(".\\TestData\\ico.obj", vec3(1.0f, 0.0f, 0.0f)));
			
			RayCollider* ray = new RayCollider();
			SphereCollider* sphereCol = new SphereCollider(15.0f);
			_scene.AddCollider(*entity, _bulletCol, ray);
			_scene.AddCollider(*entity, _towerSightCol, sphereCol);
			_scene.AddCollider(*entity, _cursorSelectionCol, new SphereCollider());
			
			_scene.AddBehavior(*entity, _group, new LaserB(*line, *ray, *sphereCol));


			entity->Active(false);
		}

	}



};