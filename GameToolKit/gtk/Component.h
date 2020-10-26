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

		void SetPosition(const vec3& position) {}
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
		virtual void Update() = 0;

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
		virtual void Draw() = 0;

		Renderer(Entity* const entity) : m_Entity(entity), m_Active(true) {}

	protected:
		Entity* const m_Entity;

	private:
		bool m_Active;

	};


}