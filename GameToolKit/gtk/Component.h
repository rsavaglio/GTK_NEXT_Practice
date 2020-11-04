#pragma once

#include "gtk.h"
#include "Camera.h"

#include <vector>

namespace gtk {

	class Entity
	{
		friend class Scene;

	public:
		const unsigned int _id;

		Entity* _Parent;
		
		mat4 _Transform;

		void SetPosition(const float& x, const float& y, const float& z) 
		{
			_Transform(0, 0) = x;
			_Transform(0, 1) = y;
			_Transform(0, 2) = z;
		}

		void SetPosition(const vec3& pos)
		{
			_Transform(0, 0) = pos.x;
			_Transform(0, 2) = pos.y;
			_Transform(0, 1) = pos.z;
		}

		void SetPosition(const mat4& pos)
		{
			_Transform(0, 0) = pos(0, 0);
			_Transform(0, 2) = pos(0, 1);
			_Transform(0, 1) = pos(0, 2);
		}

		void SetRotation(const vec3& rotation) {}
		void SetScale(const vec3& scale) {}

	private:

		// Call CreateEntity() from a Scene
		Entity(const unsigned int& id, Entity* const parent);

		bool _Active;

		std::vector<Entity*> _Children;

		void AddChild(Entity* const child)
		{
			_Children.push_back(child);
		}
	};



	class CompGroup
	{
		friend class Scene;

	public:
		const unsigned int _id;

	private:

		// Call CreateCompGroup() from a Scene
		CompGroup(const unsigned int& id);
	};

	class Component
	{
		friend class Scene;

	public:

		virtual ~Component() {}

		Component(Entity* const entity, const CompGroup& compGroup) : m_Entity(entity), m_GroupID(compGroup._id), m_Active(true) {}

		virtual void Start() = 0;
		virtual void Update(float deltaTime) = 0;

	protected:
		
		Entity* const m_Entity;
		const unsigned int m_GroupID;

	private:
		bool m_Active;

	};

	class Renderer
	{
		friend class Scene;

	public:

		virtual ~Renderer() {}
		virtual void Start() = 0;
		virtual void Draw() = 0;

		Renderer(Entity* const entity) : m_Entity(entity), m_Active(true) {}

	protected:
		Entity* const m_Entity;

	private:
		bool m_Active;

	};


}