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
		mat4 _Transform;

		void SetPosition(const vec3& position) {}
		void SetRotation(const vec3& rotation) {}
		void SetScale(const vec3& scale) {}

	private:

		// Call CreateEntity() from a Scene
		Entity(const unsigned int& id);

		Entity* _Parent;
		std::vector<Entity*> _Children;
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
	public:

		friend class Scene;

		virtual ~Component() {}

		Component(Entity& entity, const CompGroup& compGroup) : m_Entity(entity), m_GroupID(compGroup._id), m_Active(true) {}

		virtual void Start() = 0;
		virtual void Update() = 0;

	protected:
		
		Entity& m_Entity;
		const unsigned int m_GroupID;
		bool m_Active;

	};

	class Renderer
	{
	public:

		virtual ~Renderer() {}
		virtual void Draw() = 0;

	};


}